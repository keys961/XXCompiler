#include <altivec.h>
#include "tree.h"
#include "codegen.h"
#include <sstream>
std::map<std::string, std::string> constStringMap;
std::map<std::string, std::string> constRealMap;
bool isMain = true;

void selectOP(SymbolBucket *bucket, int &reg, std::string &load, std::string &store, int &loc, int currentLevel = 0) {
    if (reg == -3 && bucket != NULL) {
        reg = -1;
        // loc = bucket->getOffsetReg();
        // 表明 loc是一个寄存器号，array和record的情形
        loc = bucket->getSymbol().getLocation();
        load = "load_reg";
        store = "store_reg";
        return;
    } else {
        load = "load";
        store = "store";
    }

    if (reg == -1 && bucket != NULL) {
        loc = bucket->getSymbol().getLocation();
        std::cout << "in select " << bucket->getCurrentTable() << std::endl;
        int level = bucket->getCurrentTable()->getLevel();
        if (level < currentLevel) {
            char ch[5] = {0,};
            sprintf(ch, "%d", currentLevel - level);
            load = load + "-" + ch;
            store = store + "-" + ch;
        }
    }

    std::cout << "out select" << std::endl;
}

void FuncOrProcTreeNode::printSelf() {
    if (printedNodes.find(this) != printedNodes.end()) {
        astOut << "Node ID 0x" << std::hex << addr << ":" << " FuncOrProcTreeNode" << std::endl;
        astOut << "\tname: " << name << "; isFunction: " << isFunc << std::endl;
        astOut << "\targs node: " << args << "; body node: " << body
               << "; return type node: " << return_type << std::endl;
        printedNodes.insert(this);
        args->printSelf();
        body->printSelf();
        if (return_type)
            return_type->printSelf();
    }
}

//===============代码生成===============
//todo 初始化
SymbolBucket *ProgramBodyTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
//    traceGen("pg");
    code << ".data" << std::endl;
    for (std::map<std::string, std::string>::iterator iter = constStringMap.begin();
         iter != constStringMap.end(); iter++) {
        std::string constStr = iter->first;
        std::string label = iter->second;
        CodeGenerator::emitCodeConstStr(constStr, label);
    }
    for (std::map<std::string, std::string>::iterator iter = constRealMap.begin(); iter != constRealMap.end(); iter++) {
        std::string constStr = iter->first;
        std::string label = iter->second;
        CodeGenerator::emitCodeConstReal(constStr, label);
    }
    code << ".text" << std::endl;
//    routine->genCode(environment);

    std::vector<SymbolBucket *> bucketList;
    //todo 获取bucketlist
    symbolTable->getSymbolBucketListByType(bucketList, );
    //所需的栈大小
    int totalStackSize = 0;
    for (int i = 0; i < bucketList.size(); i++) {
        SymbolBucket *b = bucketList[i];
        std::cout << b->getSymbol().getName() << "'s size is " << b->getSymbol().getSize() << std::endl;
        totalStackSize += b->getSymbol().getSize();
    }
    if (isMain) {
        CodeGenerator::genRType("+", FP, SP, 0);
    }
    if (totalStackSize > 0) {
        CodeGenerator::genIType("-", SP, SP, totalStackSize);
    }
    getConst_decl()->genCode(environment);
    body->genCode(environment);
    if (totalStackSize > 0)
        CodeGenerator::genIType("+", SP, SP, totalStackSize);
    if (!isMain) {
        CodeGenerator::genJType("jr", "");
    } else {
        CodeGenerator::genJType("j", "exit");
    }
    if (isMain) {
        isMain = false;
    }
    routine_decl->genCode(symbolTable);
    return NULL;

    CodeGenerator::addLabel("exit");
}

SymbolBucket *ListTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
//    traceGen("lg");
//    childrenGenCode(list, symbolTable, reg);
    std::cout << list.size() << std::endl;
    for (int i = 0; i < list.size(); i++) {
        list[i]->genCode(symbolTable, reg);
    }
    return 0;
}

void CallExprTreeNode::genSysFunc(SymbolTable *symbolTable, std::string name) {
    if ((*args).size() > 1 || (*args).size() == 0) {
        std::cout << getLineNum() << " writeln's argument num is incorrect " << std::endl;
    }
    int argReg;
    SymbolBucket *argBucket = (*args)[0]->genCode(symbolTable, &argReg);
    std::string type = argBucket->getSymbol().getTypeName();
    std::string loadOP, storeOP;
    int loc;
    selectOP(argBucket, argReg, loadOP, storeOP, loc, symbolTable->getLevel());
    if (type == "string") {
        if (argReg > 0) {
            CodeGenerator::genRType("+", A0, argReg, 0);
        } else if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, loc, FP, A0);
        }
        CodeGenerator::emitSysCall("printString");
    } else if (type == "integer") {
        if (argReg > 0) {
            CodeGenerator::genRType("+", A0, argReg, 0);
        } else if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, loc, FP, A0);
        } else if (argReg == -2) {
            int imme = argBucket->getSymbol().getImmediateValue();
            CodeGenerator::genIType("+", A0, 0, imme);
        }
        CodeGenerator::emitSysCall("printInteger");
    } else if (type == "real") {
        if (argReg > 0) {
            CodeGenerator::genRType("+", F12, argReg, 0, 1);
        } else if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, loc, FP, F12, 1);
        }
        CodeGenerator::emitSysCall("printReal");
    } else if (type == "char") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, loc, FP, A0);
        }
        CodeGenerator::emitSysCall("printChar");
    }
    regManager->freeReg(argReg);
    if (argBucket != NULL) delete argBucket;
}

SymbolBucket *CallExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    std::cout << "in call " << name << std::endl;
    if (name == "writeln" || name == "readln") {
        genSysFunc(symbolTable, name);
        return NULL;
    }
    environment = symbolTable;
    std::cout << name << std::endl;
    SymbolBucket *funcBucket = environment->find(name);
    std::cout << funcBucket << std::endl;
    SymbolBucket *returnBucket;
    returnBucket = new SymbolBucket(funcBucket->getSymbol(), symbolTable);
    if (funcBucket->getSymbol().getTypeName() == "func")
        returnBucket->getSymbol().setTypeName("null");
    std::vector<SymbolBucket *> argsTypeList;
    SymbolBucket *member = funcBucket->getNextBucket();
    do {
        argsTypeList.push_back(funcBucket->getNextTable()->find(member->getSymbol().getName()));
        member = member->getLastBucket()->getNextBucket();
    } while (member != funcBucket);
    // pass arguments
    int tmpDst;
    int tmp;
    for (int i = 0; i < args->size(); i++) {
        tmpDst = regManager->getTmpReg();
        SymbolBucket *argType = argsTypeList[i];
        int argReg, argLoc;
        std::string loadOP, storeOP;
        SymbolBucket *argBucket = (*args)[0]->genCode(symbolTable, &argReg);
        int isElem = argReg == -3;
        selectOP(argBucket, argReg, loadOP, storeOP, argLoc, symbolTable->getLevel());
        //将参数放到tmpDst寄存器
        CodeGenerator::emitCodeM(loadOP, argLoc, FP, tmpDst);
        //将tmpDst中的值压栈
        CodeGenerator::emitCodeM("store", argType->getSymbol().getLocation(), SP, tmpDst);
        //SP下移
        CodeGenerator::genIType("-", SP, SP, argType->getSymbol().getLocation());

        regManager->freeReg(tmpDst);
        if (argBucket != NULL) delete argBucket;
    }
    //依次压入FP（调用者的）、返回值、返回地址
    CodeGenerator::emitCodeM("store", -4, SP, FP);
    CodeGenerator::emitCodeM("store", -8, SP, V1);
    CodeGenerator::emitCodeM("store", -12, SP, RA);
    CodeGenerator::genIType("+", FP, SP, 0);
    CodeGenerator::genIType("-", SP, SP, -12);
    CodeGenerator::genJType("jal", name);
    if (isFunc) {
        tmp = regManager->getTmpReg();
        CodeGenerator::genRType("+", tmp, V1, 0);
        if (reg != NULL) *reg = tmp;
    } else {
        if (reg != NULL) *reg = -4;
    }
    CodeGenerator::genIType("+", SP, FP, 0);
    CodeGenerator::emitCodeM("load", -12, FP, RA);
    CodeGenerator::emitCodeM("load", -8, FP, V1);
    CodeGenerator::emitCodeM("load", -4, FP, FP);
    std::cout << "out call " << std::endl;
    return returnBucket;
}

SymbolBucket *VariableTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    if (!isConst) {
        std::cout << "vg : " << name << " environment : " << symbolTable << std::endl;
        environment = symbolTable;
        SymbolBucket *b = environment->find(name);
        std::cout << "b = " << b << std::endl;
        if (b == NULL) {
            std::cout << getLineNum() << ": variable " << name << " is not defined" << std::endl;
        }
        SymbolBucket *returnBucket = new SymbolBucket(*b);
        returnBucket->setCurrentTable(b->getCurrentTable());
        return returnBucket;
    } else {
//        traceGen("cg");
        VariableTreeNode *lhs = new VariableTreeNode(name);
        BinaryExprTreeNode *binaryExprTreeNode = new BinaryExprTreeNode("=", lhs, constValue);
        binaryExprTreeNode->genCode(symbolTable);
        regManager->freeAll();

    }
}

SymbolBucket *BinaryExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
//    traceGen("bg : " + op);
    environment = symbolTable;
    int regR, regL;
    int locationR = 0, locationL = 0;
    // for arrayElem and recordElem
    SymbolBucket *bucketR, *bucketL, *returnBucket;
    bucketR = roprand->genCode(environment, &regR);
    bucketL = loprand->genCode(environment, &regL);
    int isFloat = isFloatType(bucketR, regR) && isFloatType(bucketL, regL);
    if (bucketL != NULL)
        returnBucket = new SymbolBucket(*bucketL);
    else
        returnBucket = NULL;
    std::string loadOPR, storeOPR;
    std::string loadOPL, storeOPL;
    selectOP(bucketR, regR, loadOPR, storeOPR, locationR, symbolTable->getLevel());
    selectOP(bucketL, regL, loadOPL, storeOPL, locationL, symbolTable->getLevel());
    std::cout << "regL : " << regL << " regR " << regR << std::endl;
//    if (regL == -1 && regR == -1) {
    int tmpSrc_1 = regManager->getTmpReg(isFloat);
    int tmpSrc_2 = regManager->getTmpReg(isFloat);
    int tmpDst = regManager->getTmpReg(isFloat);
    if (op == "=") {
        //todo 变量大小大于4
        if (bucketR->getSymbol().getSize() > 4) {
            if (bucketL->getSymbol().getSize() == bucketR->getSymbol().getSize()) {
//                CodeGenerator::emitCodeB(loadOPR, storeOPL, bucketR->getSize(), locationL, locationR, FP, 4);
            } else {
                std::cout << getLineNum() << ": error two record has different size" << std::endl;
                exit(-1);
            }
        } else {
            CodeGenerator::emitCodeM(loadOPR, locationR, FP, tmpSrc_2, isFloat);
            CodeGenerator::emitCodeM(storeOPL, locationL, FP, tmpSrc_2, isFloat);
            if (reg != NULL) *reg = tmpSrc_2;
        }
    } else {
        CodeGenerator::emitCodeM(loadOPL, locationL, FP, tmpSrc_1, isFloat);
        CodeGenerator::emitCodeM(loadOPR, locationR, FP, tmpSrc_2, isFloat);
        CodeGenerator::genRType(op, tmpDst, tmpSrc_1, tmpSrc_2, isFloat);
        if (reg != NULL) *reg = tmpDst;
    }
    regManager->freeReg(tmpSrc_1);
    regManager->freeReg(tmpSrc_2);
//    regManager->freeReg(tmpDst);
    //todo 释放寄存器
    autoFreeReg(tmpDst, reg);
//    }
    if (bucketL != NULL) delete bucketL;
    if (bucketR != NULL) delete bucketR;
    autoFreeReg(regL, reg);
    autoFreeReg(regR, reg);
    return returnBucket;
}

TreeNode *BinaryExprTreeNode::getLoprand() const {
    return loprand;
}

TreeNode *BinaryExprTreeNode::getRoprand() const {
    return roprand;
}

SymbolBucket *WhileStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    SymbolBucket *bucketL;
    int regL, regR, locationL;
    std::string loadOPL, storeOPL;
    int loopNum = labelManager->getLoopLabel();
    labelManager->addLoopLabel();
    //设置循环开始标签为loop + 循环号，循环结束标签为break + 循环号
    std::stringstream ss;
    ss << "loop" << loopNum;
    std::string loopLabel = ss.str();
    ss.str("");
    ss << "break" << loopNum;
    std::string breakLabel = ss.str();
    //从这开始生成汇编代码
    CodeGenerator::addLabel(loopLabel);
    bucketL = condition->genCode(symbolTable, &regL);
    selectOP(bucketL, regL, loadOPL, storeOPL, locationL, symbolTable->getLevel());
    CodeGenerator::genIType("beq", regL, 0, 0, breakLabel);
    body->genCode(symbolTable, &regR);
    CodeGenerator::genJType("j", loopLabel);
    //将循环结束标签紧接在循环体后面，结束循环时只要跳到此处即可
    CodeGenerator::addLabel(breakLabel);
    delete bucketL;
    //todo free寄存器
    regManager->freeReg(regL);
    regManager->freeReg(regR);
    return NULL;
}

SymbolBucket *ForStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    //L存放初始值的bucket，R存放终值的bucket
    SymbolBucket *bucketR, *bucketL;
    int regL, regR, bodyReg, locationR;
    std::string loadOPR, storeOPR;
    std::string loadOPL, storeOPL;
    int loopNum = labelManager->getLoopLabel();
    labelManager->addLoopLabel();
    //设置循环开始标签为loop + 循环号，循环结束标签为break + 循环号
    std::stringstream ss;
    ss << "loop" << loopNum;
    std::string loopLabel = ss.str();
    ss.str("");
    ss << "break" << loopNum;
    std::string breakLabel = ss.str();

    bucketL = src->genCode(symbolTable, &regL);
    regManager->freeReg(regL);
    //获取id的symbolbucket，id就是循环初始值
    SymbolBucket *idBucket = ((BinaryExprTreeNode *) src)->getLoprand()->genCode(symbolTable);
    //循环从这里开始
    CodeGenerator::addLabel(loopLabel);
    //把id存在这个寄存器里
    int idReg = regManager->getTmpReg();
    //从内存中加载id，放到idReg表示的寄存器中
    CodeGenerator::emitCodeM("load", idBucket->getSymbol().getLocation(), FP, idReg);
    bucketR = dst->genCode(symbolTable, &regR);
    selectOP(bucketR, regR, loadOPR, storeOPR, locationR, symbolTable->getLevel());
    locationR = bucketR->getSymbol().getLocation();
    int compReg = regManager->getTmpReg();
    int dstReg = regManager->getTmpReg();
    //获取循环终值，与当前id值进行比较以决定是否跳出循环
    CodeGenerator::emitCodeM(loadOPR, locationR, FP, dstReg);
    CodeGenerator::genRType("<=", compReg, idReg, dstReg);
    CodeGenerator::genIType("beq", compReg, 0, 0, breakLabel);
    regManager->freeReg(dstReg);
    //生成循环体
    body->genCode(symbolTable, &bodyReg);

    //根据for循环的类型决定进行id++或id--
    int tmp = regManager->getTmpReg();
    CodeGenerator::emitCodeM("load", idBucket->getSymbol().getLocation(), FP, tmp);
    if (direction == "to") {
        CodeGenerator::genIType("+", tmp, tmp, 1);
    } else {
        CodeGenerator::genIType("-", tmp, tmp, 1);
    }

    CodeGenerator::emitCodeM("store", idBucket->getSymbol().getLocation(), FP, tmp);
    CodeGenerator::genJType("j", loopLabel);
    CodeGenerator::addLabel(breakLabel);
    regManager->freeReg(tmp);
    regManager->freeReg(regR);
    regManager->freeReg(bodyReg);
    regManager->freeReg(idReg);
    delete bucketL;
    delete bucketR;
    return NULL;
}

SymbolBucket *SwitchStmtTreeNode::genCode(SymbolTable *symtab, int *reg) {
    std::cout << "sg" << std::endl;
    SymbolBucket *bucketE, *bucketCase;
    int regE;
    std::string loadOPE, storeOPE;
    int locationE;
    std::cout << expr << std::endl;
    //条件
    bucketE = expr->genCode(symtab, &regE);
    selectOP(bucketE, regE, loadOPE, storeOPE, locationE, symtab->getLevel());
    if (regE == -1) {
        int tmp = regManager->getTmpReg();
        CodeGenerator::emitCodeM(loadOPE, locationE, FP, tmp);
        //case
        bucketCase = case_list->genCode(symtab, &tmp);
        regManager->freeReg(tmp);
    } else if (regE > 0) {
        bucketCase = case_list->genCode(symtab, &regE);
    }
    regManager->freeReg(regE);
    delete bucketE;
    return NULL;
}

SymbolBucket *CaseExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    SymbolBucket *bucketID;
    int idReg, regE;
    int locationID;
    std::string loadOPID, storeOPID;
    int caseNum = labelManager->getCaseLabel();
    std::stringstream ss;
    ss << "case" << caseNum;
    std::string caseLabel = ss.str();
    regE = *reg;

    bucketID = label->genCode(symbolTable, &idReg);

    selectOP(bucketID, idReg, loadOPID, storeOPID, locationID, symbolTable->getLevel());
    locationID = bucketID->getSymbol().getLocation();
    int tmp = regManager->getTmpReg();
    CodeGenerator::emitCodeM(loadOPID, locationID, FP, tmp);
    CodeGenerator::genIType("bne", tmp, regE, 0, caseLabel);
    labelManager->addCaseLabel();
    regManager->freeReg(tmp);
    regManager->freeReg(idReg);
    body->genCode(symbolTable);
    CodeGenerator::addLabel(caseLabel);
    delete bucketID;
}

SymbolBucket *IfStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    SymbolBucket *bucketC;
    int regC, regB, regE;
    int locationC;
    int ifNum = labelManager->getIfLabel();
    std::string loadOPC, storeOPC;
    bucketC = condition->genCode(symbolTable, &regC);
    selectOP(bucketC, regC, loadOPC, storeOPC, locationC, symbolTable->getLevel());
    locationC = bucketC->getSymbol().getLocation();

    std::stringstream ss;
    ss << "endif" << ifNum;
    std::string endifLabel = ss.str();
    ss.str("");
    ss << "endelse" << ifNum;
    std::string endelseLabel = ss.str();

    CodeGenerator::genIType("beq", regC, 0, 0, endifLabel);

    then_stmt->genCode(symbolTable, &regB);
    if (else_stmt != NULL) {
        CodeGenerator::genJType("j", endelseLabel);
        CodeGenerator::addLabel(endifLabel);
        else_stmt->genCode(symbolTable, &regE);
        CodeGenerator::addLabel(endelseLabel);
    } else {
        CodeGenerator::addLabel(endifLabel);
    }
    labelManager->addIfLabel();
    regManager->freeReg(regC);
    return NULL;
}

SymbolBucket *RepeatStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    //B为循环体，C为循环条件
    SymbolBucket *bucketB, *bucketC;
    int regB, regC;
    int locationC;
    std::string loadOPC, storeOPC;
    std::stringstream ss;
    ss << "do" << labelManager->getRepeatLabel();
    std::string doLabel = ss.str();
    labelManager->addRepeatLabel();
    //添加do标签，开始do-while循环
    CodeGenerator::addLabel(doLabel);
    bucketB = body->genCode(symbolTable, &regB);
    bucketC = condition->genCode(symbolTable, &regC);
    selectOP(bucketC, regC, loadOPC, storeOPC, locationC, symbolTable->getLevel());
    locationC = bucketC->getSymbol().getLocation();
    CodeGenerator::genIType("beq", regC, 0, 0, doLabel);

    regManager->freeReg(regC);
    return NULL;
}

//todo 瞎jb写，需要验证
SymbolBucket *ArrayElemTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    //获取整个数组的symbolbucket
    SymbolBucket *type = environment->find(name);
    //获取数组的元素类型
    SymbolBucket *elemType = type->getNextBucket()->getLastBucket()->getNextBucket();
    SymbolBucket *returnBucket = new SymbolBucket(elemType->getSymbol(), symbolTable);
    //数组的元素类型的大小
    int elemSize = elemType->getSymbol().getSize();
    int exprReg;
    // the stack offset of the index
    int indexLocation;
    std::string loadOP, storeOP;
    SymbolBucket *indexBucket = index->genCode(symbolTable, &exprReg);
    selectOP(indexBucket, exprReg, loadOP, storeOP, indexLocation, symbolTable->getLevel());
    indexLocation = indexBucket->getSymbol().getLocation();

    int tmpSrc_1 = regManager->getTmpReg();
    int tmpSrc_2 = regManager->getTmpReg();
    int tmpDst = regManager->getTmpReg();
    CodeGenerator::emitCodeM("load", indexLocation, FP, tmpSrc_1);
    CodeGenerator::genIType("+", tmpSrc_2, 0, elemSize);
    CodeGenerator::genRType("*", tmpDst, tmpSrc_1, tmpSrc_2);
    CodeGenerator::genIType("+", tmpDst, tmpDst, type->getSymbol().getLocation());
    if (reg != NULL) *reg = -3;
    //returnBucket->setOffsetReg(tmpDst);
    returnBucket->getSymbol().setLocation(tmpDst);
    regManager->freeReg(tmpSrc_1);
    regManager->freeReg(tmpSrc_2);

    returnBucket->getSymbol().setSize(elemSize);
    autoFreeReg(exprReg, reg);
    return returnBucket;
}

SymbolBucket *RecordElemTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    SymbolBucket *returnBucket = NULL;
    SymbolBucket *bucket = environment->find(rname);
    SymbolBucket *member = bucket->getNextBucket();
    do {
        if (member->getSymbol().getName() == ename) {
            returnBucket = new SymbolBucket(bucket->getSymbol(), symbolTable);
            returnBucket->getSymbol().setLocation(member->getSymbol().getLocation());
            returnBucket->getSymbol().setSize(member->getSymbol().getSize());
            break;
        }
        member = member->getLastBucket()->getNextBucket();
    } while (member != bucket);
    if (reg != NULL) *reg = -1;
    if (member == bucket)
        std::cout << getLineNum() << " : undefined record member :" << ename << " in " << rname << std::endl;
    return returnBucket;
}

SymbolBucket *UnaryExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    int oprandReg;
    std::string loadOP, storeOP;
    int operandLocation;
    SymbolBucket *oprandBucket = oprand->genCode(symbolTable, &oprandReg);
    SymbolBucket *returnBucket = new SymbolBucket(oprandBucket->getSymbol(), symbolTable);
    selectOP(oprandBucket, oprandReg, loadOP, storeOP, operandLocation, symbolTable->getLevel());
    operandLocation = oprandBucket->getSymbol().getLocation();
    std::cout << "in unaryExpr reg = " << oprandReg << " with op = " << op << std::endl;
    int tmpDst;
    tmpDst = regManager->getTmpReg();

    CodeGenerator::emitCodeM(loadOP, operandLocation, FP, tmpDst);
    CodeGenerator::genRType(op, tmpDst, 0, tmpDst);
    if (reg != NULL) *reg = tmpDst;

    delete oprandBucket;
    autoFreeReg(oprandReg, reg);
    return returnBucket;
}

SymbolBucket *LiteralTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    std::cout << "ng" << std::endl;
    environment = symbolTable;
    SymbolBucket *typeBucket = environment->find(type);
    SymbolBucket *returnBucket = new SymbolBucket(typeBucket->getSymbol(), symbolTable);
    returnBucket->getSymbol().setSize(getSize(type));
    if (type == "string") {
        int tmp = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constStringMap[value], tmp);
        if (reg != NULL) *reg = tmp;
    } else if (type == "integer") {
        returnBucket->getSymbol().setSize(getSize(type));
        returnBucket->getSymbol().setImmediateValue(getInt());
        if (reg != NULL) *reg = -2;
    } else if (type == "float") {
        int tmp = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constRealMap[value], tmp);
        int tmpDst = regManager->getTmpReg(1);
        CodeGenerator::emitCodeM("load", 0, tmp, tmpDst, 1);
        if (reg != NULL) *reg = tmpDst;
        regManager->freeReg(tmp);
    }
    return returnBucket;
}