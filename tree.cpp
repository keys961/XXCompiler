#include "tree.h"
#include "codegen.h"
#include <sstream>

extern std::map<std::string, std::string> constCharMap;
extern std::map<std::string, std::string> constRealMap;
bool isMain = true;

void selectOP(SymbolBucket *bucket, int &reg, std::string &load, std::string &store, int &loc, int currentLevel = 0) {
    if (reg == -3 && bucket != NULL) {
        reg = -1;
        // loc = bucket->getOffsetReg();
        // 表明 loc是一个寄存器号，array和record的情形
        loc = bucket->getSymbol()->getLocation();
        load = "load_reg";
        store = "store_reg";
        return;
    } else {
        load = "load";
        store = "store";
    }

    if (reg == -1 && bucket != NULL) {
        loc = bucket->getSymbol()->getLocation();
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

using namespace std;

//utils 函数
int getSizeByType(string type) {
    if (type == "integer") {
        return 4;
    } else if (type == "char") {
        return 4;
    } else if (type == "real") {
        return 4;
    }
    return -1;
}
//------------

void ProgramBodyTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "programbody treenode update environment" << endl;
    environment = symtab;
    if (isPrint)cout << "number of children of programbody treenode :" << children.size() << endl;
    //最后一个孩子是body块，这一块不用去更新符号表
    for (int i = 0; i < children.size() - 1; i++) {
        children[i]->updateEnvironment(symtab);
    }
}

void ListTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "list treenode update environment" << endl;
    environment = symtab;
    for (int i = 0; i < list.size(); i++) {
        list[i]->updateEnvironment(symtab);
    }
}

void VariableTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "variable treenode: " << name << " update environment" << endl;
    environment = symtab;
    SymbolBucket *b = type->genSymBucket(name, symtab);//name为变量名
    //b->setIsType(0);
    string type = b->getSymbol()->getTypeName();
    b->setCurrentTable(symtab);
    if (type.find("integer") != string::npos || type.find("real") != string::npos ||
        type.find("char") != string::npos || type.find("string") != string::npos) {
        //符号表压栈，设置该变量在符号表的位置
        b->getSymbol()->setLocation(symtab->getAndUpdateLocation(b->getSymbol()->getSize()));
    } else {
        if (type.find("record") != string::npos) {
            //将record的每个成员都加入进来
            SymbolBucket *member = b->getNextBucket();
            b->getSymbol()->setLocation(symtab->getAndUpdateLocation(0));
            do {
                member->getSymbol()->setLocation(environment->getAndUpdateLocation(member->getSymbol()->getSize()));
                member = member->getLastBucket()->getNextBucket();
            } while (member != b);
            // 为了对齐
            symtab->getAndUpdateLocation(
                    b->getSymbol()->getSize() + b->getSymbol()->getLocation() - symtab->getLocation());
        } else {
            //cout << "in vu" << b->getName() << " size is " << b->getSize() << endl;
            b->getSymbol()->setLocation(symtab->getAndUpdateLocation(b->getSymbol()->getSize()));
        }
    }
//    if (getIsVar()) {
//        b->setIsVar(1);
//    }
    symtab->insert(b);
}

void FuncOrProcTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "func/proc: " + name + "update environment" << endl;
    environment = symtab;
    // new a bucket for function
    SymbolBucket *bucket = new SymbolBucket(name, getLineNum(), isFunc ? "func" : "proc", symtab);
    bucket->getSymbol()->setSize(0);
    SymbolTable *subSymtab = new SymbolTable(name + "-subSymtab", bucket);
    subSymtab->setLevel(symtab->getLevel() + 1);
    subSymtab->setParentBucket(bucket);
    bucket->setNextTable(subSymtab);
    args->updateEnvironment(subSymtab);//函数的每个参数添加到属于函数的符号表
    // copy args into the function bucket
    vector<SymbolBucket *> v;
    subSymtab->getSymBucketList(v);
    SymbolBucket *tmpBucket = bucket;
    //subSymtab->setCurRegNum(symtab->getCurReg());
    subSymtab->setLocation(0);//初始化函数符号表的栈深度为0
    for (int i = 0; i < v.size(); i++) {
        if (isPrint)cout << "func - " << name << " : " << v[i]->getSymbol()->getName() << endl;
        v[i]->getSymbol()->setLocation(subSymtab->getAndUpdateLocation(v[i]->getSymbol()->getSize()));
//        if (!v[i]->getIsRef())
//            v[i]->setLoc(subSymtab->genLoc(v[i]->getSize()));
//        else v[i]->setLoc(subSymtab->genLoc(4));
//        v[i]->setRegNum(-1);
//        if (v[i]->getIsVar()) {
//            v[i]->setIsRef(1);
//        }
        // here we only need the first node of arguments' type
        SymbolBucket *newBucket = new SymbolBucket(v[i]);
        tmpBucket->setNextBucket(newBucket);
        tmpBucket = newBucket;
    }
    // set subsymtab for this node
    body->updateEnvironment(subSymtab);
    tab = subSymtab;
    if (isFunc) {
        if (isPrint)cout << "it is not proc!!!!!" << endl;
        SymbolBucket *returnTypeBucket = return_type->genSymBucket("returnType", symtab);
        bucket->setLastBucket(returnTypeBucket->getLastBucket());
        bucket->getLastBucket()->setNextBucket(bucket);
        tmpBucket->setNextBucket(returnTypeBucket);
        symtab->insert(bucket);
        // insert return node
        SymbolBucket *returnNameBucket = new SymbolBucket(returnTypeBucket);
        returnNameBucket->setCurrentTable(subSymtab);
        returnNameBucket->getSymbol()->setName(name);
        returnNameBucket->getSymbol()->setLocation(
                subSymtab->getAndUpdateLocation(returnNameBucket->getSymbol()->getSize()));
        // set return reg num
        //returnNameBucket->setRegNum(V1);
        subSymtab->insert(returnNameBucket);
    } else {
        bucket->setLastBucket(tmpBucket);
        tmpBucket->setNextBucket(bucket);
        symtab->insert(bucket);
    }
}

void CustomTypeTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "custom type : " + name + " update environment" << endl;
    environment = symtab;
    SymbolBucket *b = type->genSymBucket(name, symtab);
    //b->setIsType(1);
    symtab->insert(b);
}

//专门用于表示const
void BinaryExprTreeNode::updateEnvironment(SymbolTable *symtab) {
    if (isPrint)cout << "const type : " + this->loprand->getName() + " update environment" << endl;//这里的名字是const变量的名字
    environment = symtab;
    LiteralTreeNode *rop = (LiteralTreeNode *) this->roprand;
    char cu[16] = {0,};
    if (rop->getLiteralType() == "integer") {
        sprintf(cu, "%d", rop->getInt());
    } else if (rop->getLiteralType() == "char") {
        sprintf(cu, "%c", rop->getChar());
    } else if (rop->getLiteralType() == "real") {
        sprintf(cu, "%f", rop->getReal());
    }
    SymbolBucket *head = new SymbolBucket(this->loprand->getName(), getLineNum(), "const", symtab);
    //将const值用字符数组表示，强行赋值给TypeName
    SymbolBucket *end = new SymbolBucket("const-value", getLineNum(), cu, symtab);
    //标记大小
    head->getSymbol()->setSize(getSizeByType(this->roprand->getName()));
    end->getSymbol()->setSize(getSizeByType(this->roprand->getName()));
    //连接
    head->setNextBucket(end);
    end->setNextBucket(head);
    head->setLastBucket(end);
    symtab->insert(head);
}



//---------------------------------------------
//genSymBucket函数

SymbolBucket *ArrayTypeTreeNode::genSymBucket(const std::string typeName, SymbolTable *symtab) {
    if (isPrint)cout << "arraytype node " + typeName + " gen symbucket" << endl;
    SymbolBucket *array = new SymbolBucket(typeName, getLineNum(), "array", symtab);
    SymbolBucket *indexBucket = index->genSymBucket("index", symtab);//range
    SymbolBucket *elemBucket = elem->genSymBucket("arrayelem", symtab);//commontype todo
    int upper, lower, size;
    lower = atoi(indexBucket->getNextBucket()->getSymbol()->getTypeName().c_str());//index的下界
    upper = atoi(indexBucket->getLastBucket()->getSymbol()->getTypeName().c_str());//index的上界
    size = (upper - lower) * elemBucket->getSymbol()->getSize();//数组在栈中总大小
    array->getSymbol()->setSize(size);

    array->setNextBucket(indexBucket);
    indexBucket->getLastBucket()->setNextBucket(elemBucket);
    elemBucket->getLastBucket()->setNextBucket(array);
    array->setLastBucket(elemBucket->getLastBucket());
    return array;
}

SymbolBucket *RangeTypeTreeNode::genSymBucket(const string typeName, SymbolTable *symtab) {
    if (isPrint)cout << "range type node gen symbucket" << endl;
    char cu[16] = {0,};
    char cl[16] = {0,};
    int u = ((LiteralTreeNode *) upper)->getInt();//range上界
    int l = ((LiteralTreeNode *) lower)->getInt();//range下界
    sprintf(cu, "%d", u);
    sprintf(cl, "%d", l);
    SymbolBucket *head = new SymbolBucket(typeName, getLineNum(), "range", symtab);
    //将上界的值用字符数组表示，强行赋值给TypeName
    SymbolBucket *begin = new SymbolBucket("range", getLineNum(), cl, symtab);
    SymbolBucket *end = new SymbolBucket("range", getLineNum(), cu, symtab);
    //标记大小
    head->getSymbol()->setSize(getSizeByType("integer"));
    begin->getSymbol()->setSize(getSizeByType("integer"));
    end->getSymbol()->setSize(getSizeByType("integer"));
    //连接
    head->setNextBucket(begin);
    begin->setNextBucket(end);
    end->setNextBucket(head);
    head->setLastBucket(end);
    return head;
}

SymbolBucket *RecordTypeTreeNode::genSymBucket(const string typeName, SymbolTable *symtab) {
    if (isPrint)cout << "record type node : " + typeName + " gen symbucket" << endl;
    SymbolBucket *recordBucket = new SymbolBucket(typeName, getLineNum(), "record", symtab);
    recordBucket->getSymbol()->setSize(0);
    recordBucket->getSymbol()->setLocation(-1);//symtab->getAndUpdateLocation(0)
    // record每个元素都是variableTreeNode
    for (int i = 0; i < elems.size(); i++) {
        VariableTreeNode *v = (VariableTreeNode *) elems[i];
        SymbolBucket *vb = v->getTypeNode()->genSymBucket(elems[i]->getName(), symtab);
        recordBucket->getSymbol()->setSize(recordBucket->getSymbol()->getSize() + vb->getSymbol()->getSize());
        if (recordBucket->getNextBucket() == recordBucket) {
            recordBucket->setNextBucket(vb);
            vb->getLastBucket()->setNextBucket(recordBucket);
            recordBucket->setLastBucket(vb->getLastBucket());
        } else {
            SymbolBucket *tmp = recordBucket->getNextBucket();
            recordBucket->setNextBucket(vb);
            vb->getLastBucket()->setNextBucket(tmp);
        }
    }
    //record的size不是4的倍数的话则向上取整
    int size = recordBucket->getSymbol()->getSize();
    int t = size / 4;
    if (t * 4 < size) {
        size = t * 4 + 4;
        recordBucket->getSymbol()->setSize(size);
    }

    return recordBucket;
}

SymbolBucket *CustomTypeTreeNode::genSymBucket(const string typeName, SymbolTable *symtab) {
    if (isPrint)cout << "custom type node: " + name + " gen symbucket" << endl;
    //在符号表中找到已经定义的自定义类型
    SymbolBucket *typeBucket = symtab->find(name);
    SymbolBucket *b = typeBucket->deepCopyBucket();
    b->setCurrentTable(symtab);
    b->getSymbol()->setName(typeName);
    return b;
}

SymbolBucket *CommonTypeTreeNode::genSymBucket(const string typeName, SymbolTable *symtab) {
    if (isPrint)cout << "common type node gen synbucket" << endl;
    SymbolBucket *b = new SymbolBucket(typeName, getLineNum(), type, symtab);//type要是integer char double之一
    int size = getSizeByType(type);
    b->getSymbol()->setSize(size);
    return b;
}

//---------------------------------------------

////////////////////////////////////////////////////////////
// type check functions for each node					  //
////////////////////////////////////////////////////////////

string ListTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "list treenode check type" << endl;
    string res = "success";
    for (int i = 0; i < this->list.size(); i++) {
        if ((this->list[i]->typeCheck(symtab)) == "failure") {
            res = "failure";
        }
    }
    return res;
}

//===============代码生成===============
//todo 初始化
SymbolBucket *ProgramBodyTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
//    traceGen("pg");
    if (!isMain) {
        //刚进来时，SP位于RA所在的4字节内存的底部，要取到RA所在的地址头需要+4
        CodeGenerator::genIType("+", SP, SP, 4);
        CodeGenerator::emitCodeM("store", 0, SP, RA);
        CodeGenerator::genIType("-", SP, SP, 4);
        //此处同步FP、SP
        CodeGenerator::genRType("+", FP, SP, 0);
    } else {
        code << ".data 0x10000000" << std::endl;
    }
    for (std::map<std::string, std::string>::iterator iter = constCharMap.begin();
         iter != constCharMap.end(); iter++) {
        std::string constStr = iter->first;
        std::string label = iter->second;
        CodeGenerator::emitCodeConstStr(constStr, label);
    }
    for (std::map<std::string, std::string>::iterator iter = constRealMap.begin(); iter != constRealMap.end(); iter++) {
        std::string constStr = iter->first;
        std::string label = iter->second;
        CodeGenerator::emitCodeConstReal(constStr, label);
    }
    if (isMain) {
        code << ".text" << std::endl;
        code << "main:" << std::endl;
    }
//    routine->genCode(environment);

    std::vector<SymbolBucket *> bucketList;
    //todo 获取bucketlist
    symbolTable->getSymBucketList(bucketList);
    //所需的栈大小
    int totalStackSize = 0;
    for (int i = 0; i < bucketList.size(); i++) {
        SymbolBucket *b = bucketList[i];
        if (b->getSymbol()->getLocation() != -1) {
            std::cout << b->getSymbol()->getName() << "'s size is " << b->getSymbol()->getSize() << std::endl;
            totalStackSize += b->getSymbol()->getSize();
        }
    }
    if (isMain) {
        CodeGenerator::genRType("+", FP, SP, 0);
    }
    if (totalStackSize > 0) {
        CodeGenerator::genIType("-", SP, SP, totalStackSize);
    }
    getConst_decl()->genCode(environment);
    body->genCode(environment);
//    if (totalStackSize > 0){
//    }
    if (!isMain) {
        //12指的是存fp、v1、ra的内存大小，12字节
        CodeGenerator::genIType("+", SP, SP, totalStackSize + 12);
        CodeGenerator::emitCodeM("load", 4, FP, RA);
        CodeGenerator::genRType("jr", RA, 0, 0);
    } else {
        CodeGenerator::genJType("j", "exit");
    }
    if (isMain) {
        isMain = false;
    }
    routine_decl->genCode(symbolTable);
//    CodeGenerator::addLabel("exit");

    return NULL;
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
        std::cout << getLineNum() << " write's argument num is incorrect " << std::endl;
    }
    int argReg;
    SymbolBucket *argBucket = (*args)[0]->genCode(symbolTable, &argReg);
    std::string type = argBucket->getSymbol()->getTypeName();
    std::string loadOP, storeOP;
    int location;
    selectOP(argBucket, argReg, loadOP, storeOP, location, symbolTable->getLevel());
    location = argBucket->getSymbol()->getLocation();
    if (type == "integer") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, -location, FP, A0);
        } else if (argReg == -2) {
            int imme = argBucket->getSymbol()->getImmediateValue();
            CodeGenerator::genIType("+", A0, 0, imme);
        }
        CodeGenerator::emitSysCall("printInteger");
    } else if (type == "real") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, -location, FP, F12, 1);
        } else if (argReg == -2) {
            int imme = argBucket->getSymbol()->getImmediateValue();
            CodeGenerator::genIType("+", F12, 0, imme);
        }
        CodeGenerator::emitSysCall("printReal");
    } else if (type == "char") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(loadOP, -location, FP, A0);
        } else if (argReg > 0) {
            CodeGenerator::emitCodeM(loadOP, 0, argReg, A0);
        }
        CodeGenerator::emitSysCall("printChar");
    }
    regManager->freeReg(argReg);
    delete argBucket;
}

SymbolBucket *CallExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    std::cout << "in call " << name << std::endl;
    if (name == "write" || name == "read") {
        genSysFunc(symbolTable, name);
        return NULL;
    }
    environment = symbolTable;
    std::cout << name << std::endl;
    SymbolBucket *funcBucket = environment->find(name);
    std::cout << funcBucket << std::endl;
    SymbolBucket *returnBucket;
    returnBucket = new SymbolBucket(funcBucket->getSymbol(), symbolTable);
    if (funcBucket->getSymbol()->getTypeName() == "func")
        returnBucket->getSymbol()->setTypeName("null");
    std::vector<SymbolBucket *> argsTypeList;
    SymbolBucket *member = funcBucket->getNextBucket();
    do {
        argsTypeList.push_back(funcBucket->getNextTable()->find(member->getSymbol()->getName()));
        member = member->getLastBucket()->getNextBucket();
    } while (member != funcBucket);
    //依次压入FP（调用者的）、返回值、返回地址
    CodeGenerator::emitCodeM("store", -4, SP, FP);
    CodeGenerator::emitCodeM("store", -8, SP, V1);
    //此处预留4字节，用于在被调用者开头处压入返回地址
    CodeGenerator::genIType("-", SP, SP, 12);
    // pass arguments
    int tmpDst, tmp;
    for (int i = 0; i < args->size(); i++) {
        tmpDst = regManager->getTmpReg();
        SymbolBucket *argType = argsTypeList[i];
        int argReg, argLoc;
        std::string loadOP, storeOP;
        SymbolBucket *argBucket = (*args)[i]->genCode(symbolTable, &argReg);
        int isElem = argReg == -3;
        selectOP(argBucket, argReg, loadOP, storeOP, argLoc, symbolTable->getLevel());
        //-2表明参数是字面量，则直接从该bucket的symbol的立即值中取值
        if (argReg == -2) {
            CodeGenerator::genIType("+", tmpDst, 0, argBucket->getSymbol()->getImmediateValue());
        } else {
            argLoc = argBucket->getSymbol()->getLocation();
            //将参数放到tmpDst寄存器
            CodeGenerator::emitCodeM(loadOP, -argLoc, FP, tmpDst);
        }

        //将tmpDst中的值压栈
        CodeGenerator::emitCodeM("store", -argType->getSymbol()->getSize() * i, SP, tmpDst);
        //SP下移
//        CodeGenerator::genIType("-", SP, SP, argType->getSymbol()->getSize() * (i + 1));

        regManager->freeReg(tmpDst);
        delete argBucket;
    }

//    CodeGenerator::genIType("+", FP, SP, 0);
    CodeGenerator::genJType("jal", name);
    if (isFunc) {
        tmp = regManager->getTmpReg();
        CodeGenerator::genRType("+", tmp, V1, 0);
        if (reg != NULL) *reg = tmp;
    } else {
        if (reg != NULL) *reg = -4;
    }
//    CodeGenerator::genIType("+", SP, FP, 0);
    //todo 改动：此处逻辑错误，应该在被调用者里取出返回地址
//    CodeGenerator::emitCodeM("load", -12, FP, RA);
    CodeGenerator::emitCodeM("load", -8, FP, V1);
    CodeGenerator::emitCodeM("load", -12, FP, FP);
    std::cout << "out call " << std::endl;
    regManager->freeReg(tmp);
    return returnBucket;
}

SymbolBucket *VariableTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    if (reg != NULL)
        *reg = -1;
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
    locationR = -bucketR->getSymbol()->getLocation();
    locationL = -bucketL->getSymbol()->getLocation();
    std::cout << "regL : " << regL << " regR " << regR << std::endl;
    if (regL == -1 && regR == -1) {
        int tmpSrc_1 = regManager->getTmpReg(isFloat);
        int tmpSrc_2 = regManager->getTmpReg(isFloat);
        int tmpDst = regManager->getTmpReg(isFloat);
        if (op == ":=") {
            //todo 变量大小大于4
            if (bucketR->getSymbol()->getSize() > 4) {
                if (bucketL->getSymbol()->getSize() == bucketR->getSymbol()->getSize()) {
//                CodeGenerator::emitCodeB(loadOPR, storeOPL, bucketR->getSize(), locationL, locationR, FP, 4);
                } else {
                    std::cout << getLineNum() << ": error two record has different size" << std::endl;
                    exit(-1);
                }
            } else {
                //赋值操作右节点的值直接写进左节点内存，设置reg为-1代表结果在内存中
                CodeGenerator::emitCodeM(loadOPR, locationR, FP, tmpSrc_1, isFloat);
                CodeGenerator::emitCodeM(storeOPL, locationL, FP, tmpSrc_1, isFloat);
                if (reg != NULL)
                    *reg = -1;
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
    } else if (regL == -2 || regR == -2) {
        int tmpDst, tmpSrc;
        cout << "br = " << bucketR << " bl = " << bucketL << endl;
        int intImmeR, intImmeL;
        if (bucketR != NULL)
            intImmeR = bucketR->getSymbol()->getImmediateValue();
        if (bucketL != NULL)
            intImmeL = bucketL->getSymbol()->getImmediateValue();

        cout << "immeR = " << intImmeR << " immeL = " << intImmeL << endl;
        if (regL == -2 && regR == -2) {
            tmpDst = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpDst, tmpDst, intImmeR);
            CodeGenerator::genIType(op, tmpDst, tmpDst, intImmeL);
            if (reg != NULL) *reg = tmpDst;
        } else if (regL == -2 && regR == -1) {
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::emitCodeM(loadOPR, locationR, FP, tmpSrc, isFloat);
            CodeGenerator::genIType(op, tmpDst, tmpSrc, intImmeL);
            if (reg != NULL) *reg = tmpDst;
        } else if (regL == -1 && regR == -2) {
            if (op == ":=") {
                tmpDst = regManager->getTmpReg(isFloat);
                CodeGenerator::genIType(op, tmpDst, 0, intImmeR);
                CodeGenerator::emitCodeM(storeOPL, locationL, FP, tmpDst, isFloat);
                if (reg != NULL) *reg = tmpDst;
            } else {
                tmpDst = regManager->getTmpReg(isFloat);
                tmpSrc = regManager->getTmpReg(isFloat);
                CodeGenerator::emitCodeM(loadOPL, locationL, FP, tmpSrc, isFloat);
                CodeGenerator::genIType(op, tmpDst, tmpSrc, intImmeR);
                if (reg != NULL) *reg = tmpDst;
            }
        } else if (regL == -2 && regR > 0) {
            //左边字面量，右边在寄存器里，则不会有“:=”的情况
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpSrc, 0, intImmeL);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regR);
            if (reg != NULL) *reg = tmpDst;
        } else if (regL > 0 && regR == -2) {
            //左边在寄存器里，右边字面量，也不会有:=的情况
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpSrc, 0, intImmeR);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regL);
            if (reg != NULL) *reg = tmpDst;
        }
        regManager->freeReg(tmpSrc);
        autoFreeReg(tmpDst, reg);
    } else if (regR > 0) {
        int tmpSrc = regManager->getTmpReg(isFloat);
        int tmpDst = regManager->getTmpReg(isFloat);
        if (op == ":=") {
            CodeGenerator::emitCodeM(storeOPL, locationL, FP, regR);
        } else {
            CodeGenerator::emitCodeM(loadOPL, locationL, FP, tmpSrc, isFloat);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regR);
            if (reg != NULL) *reg = tmpDst;
        }
        regManager->freeReg(tmpSrc);
        autoFreeReg(tmpDst, reg);
    }
    delete bucketL;
    delete bucketR;
    autoFreeReg(regL, reg);
    autoFreeReg(regR, reg);
    return returnBucket;
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
    CodeGenerator::emitCodeM("load", idBucket->getSymbol()->getLocation(), FP, idReg);
    bucketR = dst->genCode(symbolTable, &regR);
    selectOP(bucketR, regR, loadOPR, storeOPR, locationR, symbolTable->getLevel());
    locationR = bucketR->getSymbol()->getLocation();
    int compReg = regManager->getTmpReg();
    int dstReg = regManager->getTmpReg();
    //获取循环终值，与当前id值进行比较以决定是否跳出循环
    if (locationR == -1) {
        int immeR = bucketR->getSymbol()->getImmediateValue();
        CodeGenerator::genIType("+", dstReg, 0, immeR);
    } else {
        CodeGenerator::emitCodeM(loadOPR, locationR, FP, dstReg);
    }
    CodeGenerator::genRType("<=", compReg, idReg, dstReg);
    CodeGenerator::genIType("beq", compReg, 0, 0, breakLabel);
    regManager->freeReg(dstReg);
    //生成循环体
    body->genCode(symbolTable, &bodyReg);

    //根据for循环的类型决定进行id++或id--
    int tmp = regManager->getTmpReg();
    CodeGenerator::emitCodeM("load", idBucket->getSymbol()->getLocation(), FP, tmp);
    if (direction == "to") {
        CodeGenerator::genIType("+", tmp, tmp, 1);
    } else {
        CodeGenerator::genIType("-", tmp, tmp, 1);
    }

    CodeGenerator::emitCodeM("store", idBucket->getSymbol()->getLocation(), FP, tmp);
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
    locationID = bucketID->getSymbol()->getLocation();
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
    locationC = bucketC->getSymbol()->getLocation();

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
    locationC = bucketC->getSymbol()->getLocation();
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
    int elemSize = elemType->getSymbol()->getSize();
    int exprReg;
    // the stack offset of the index
    int indexLocation;
    std::string loadOP, storeOP;
    SymbolBucket *indexBucket = index->genCode(symbolTable, &exprReg);
    selectOP(indexBucket, exprReg, loadOP, storeOP, indexLocation, symbolTable->getLevel());
    indexLocation = indexBucket->getSymbol()->getLocation();

    int tmpSrc_1 = regManager->getTmpReg();
    int tmpSrc_2 = regManager->getTmpReg();
    int tmpDst = regManager->getTmpReg();
    CodeGenerator::emitCodeM("load", indexLocation, FP, tmpSrc_1);
    CodeGenerator::genIType("+", tmpSrc_2, 0, elemSize);
    CodeGenerator::genRType("*", tmpDst, tmpSrc_1, tmpSrc_2);
    CodeGenerator::genIType("+", tmpDst, tmpDst, type->getSymbol()->getLocation());
    if (reg != NULL) *reg = -3;
    //returnBucket->setOffsetReg(tmpDst);
    returnBucket->getSymbol()->setLocation(tmpDst);
    regManager->freeReg(tmpSrc_1);
    regManager->freeReg(tmpSrc_2);

    returnBucket->getSymbol()->setSize(elemSize);
    autoFreeReg(exprReg, reg);
    return returnBucket;
}

SymbolBucket *RecordElemTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    SymbolBucket *returnBucket = NULL;
    SymbolBucket *bucket = environment->find(rname);
    SymbolBucket *member = bucket->getNextBucket();
    do {
        if (member->getSymbol()->getName() == ename) {
            returnBucket = new SymbolBucket(bucket->getSymbol(), symbolTable);
            returnBucket->getSymbol()->setLocation(member->getSymbol()->getLocation());
            returnBucket->getSymbol()->setSize(member->getSymbol()->getSize());
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
    operandLocation = oprandBucket->getSymbol()->getLocation();
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
//    SymbolBucket *typeBucket = environment->find(type);
    //todo 暴力改type
    Symbol *symbol = new Symbol(getLineNum(), "LiteralTreeNode", type);
    SymbolBucket *returnBucket = new SymbolBucket(symbol, symbolTable);
    returnBucket->getSymbol()->setSize(getSize(type));

    if (type == "integer") {
        returnBucket->getSymbol()->setImmediateValue(getInt());
        if (reg != NULL) *reg = -2;
    } else if (type == "real") {
        int labelReg = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constRealMap[value], labelReg);
        int tmpDst = regManager->getTmpReg(1);
        CodeGenerator::emitCodeM("load", 0, labelReg, tmpDst, 1);
        if (reg != NULL) *reg = tmpDst;
        regManager->freeReg(labelReg);
        if (reg != NULL) *reg = -tmpDst;
    } else {
        int labelReg = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constCharMap[value], labelReg);
        if (reg != NULL) *reg = labelReg;
    }
    return returnBucket;
}

string ProgramBodyTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "programbody treenode check type" << endl;
    return this->body->typeCheck(symtab);
}

string VariableTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "variable treenode: " << name << " check type" << endl;
    SymbolBucket *var = symtab->find(name);
    if (var == nullptr) return "failure";
    if (var->getSymbol()->getTypeName() == "const") {
        return "const-" + var->getNextBucket()->getSymbol()->getTypeName();
    } else {
        return var->getSymbol()->getTypeName();
    }
}

string LiteralTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "literal treenode: " << this->value << " check type" << endl;
    return this->type;
}

string ArrayElemTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "array elem treenode: " << name << " check type" << endl;
    SymbolBucket *b = symtab->find(name);//根据数组名找
    if (b == NULL || b->getSymbol()->getTypeName() != "array") {
        if (b == NULL)
            checkOut << getLineNum() << " : name is not defined." << endl;
        else
            checkOut << getLineNum() << " : name is not a array type." << endl;
        return "failure";
    } else {
        return b->getNextBucket()->getLastBucket()->getNextBucket()->getSymbol()->getTypeName();
    }
}

string CompoundStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "compound treenode check type" << endl;
    if ((this->stmtlist->typeCheck(symtab)) != "failure")
        return "success";
    return "failure";
}

string IfStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "if treenode check type" << endl;
    string s1 = condition->typeCheck(symtab);
    string s2 = this->then_stmt->typeCheck(symtab);
    string s3 = this->else_stmt->typeCheck(symtab);
    if (s1 != "failure" && s2 != "failure" && (this->else_stmt == NULL ? 1 : (s3 != "failure"))) {
        return "success";
    }
    return "failure";
}

string RepeatStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "repeat treenode check type" << endl;
    string s1 = condition->typeCheck(symtab);
    string s2 = body->typeCheck(symtab);
    if (s1 != "failure" && s2 != "failure") {
        return "success";
    }
    return "failure";
}

string WhileStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "while treenode check type" << endl;
    string s1 = condition->typeCheck(symtab);
    string s2 = body->typeCheck(symtab);
    if (s1 != "failure" && s2 != "failure") {
        return "success";
    }
    return "failure";
}

string SwitchStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "switch treenode check type" << endl;
    string s1 = expr->typeCheck(symtab);
    string s2 = this->case_list->typeCheck(symtab);
    if (s1 != "failure" && s2 != "failure") {
        return "success";
    }

    return "failure";
}

string ForStmtTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "for treenode check type" << endl;
    string s1 = this->src->typeCheck(symtab);
    string s2 = this->dst->typeCheck(symtab);
    string s3 = body->typeCheck(symtab);
    if (s1 != "failure" && s2 != "failure" && s3 != "failure") {
        return "success";
    }
    return "failure";
}

string UnaryExprTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "unary expr treenode check type" << endl;
    string type = this->oprand->typeCheck(symtab);
    if (type != "integer" && type != "const-integer") {
        checkOut << getLineNum() << ": " << "The right value must be an integer." << endl;
        return "failure";
    } else if (type == "failure") {
        checkOut << getLineNum() << ": " << "The right variable is not defined!" << endl;
        return "failure";

    }
    return type;
}

string BinaryExprTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "binary expr treenode check type" << endl;
    string ltype = this->loprand->typeCheck(symtab);
    string rtype = this->roprand->typeCheck(symtab);
    checkOut << "variable left type: " << ltype << endl;
    checkOut << "binary expr right type: " << rtype << endl;
    if (ltype == "integer" && (rtype == "integer" || rtype == "const-integer"))
        return "integer";
    else if (ltype == "real" && (rtype == "real" || rtype == "const-real"))
        return "real";
    else if (ltype == "char") {
        if (rtype == "char" || rtype == "string" || rtype == "const-string" || rtype == "const-char")
            return "char";
    } else if (ltype == "string") {
        if (rtype == "char" || rtype == "string" || rtype == "const-string" || rtype == "const-char")
            return "string";
    } else if (ltype == "const-char" || ltype == "const-integer" || ltype == "const-string" || ltype == "const-real") {
        checkOut << getLineNum() << ": " << "The const variable cannot be lvalue!" << endl;
        return "failure";
    } else if (ltype == rtype || rtype == "const-" + ltype) {
        return ltype;
    } else if (ltype == "failure" || rtype == "failure") {
        if (ltype == "failure")checkOut << getLineNum() << ": " << "The left oprand is not defined!" << endl;
        if (rtype == "failure")checkOut << getLineNum() << ": " << "The right oprand is not defined!" << endl;
        return "failure";
    }
    checkOut << getLineNum() << ": " << "Can not transform the type " << rtype << " to the type " << ltype << "."
             << endl;
    return "failure";
}

string CaseExprTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "case expr treenode check type" << endl;
    if ((this->body->typeCheck(symtab)) != "failure") {
        return "success";
    }
    return "failure";
}

string CallExprTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "call expr treenode: " << name << " check type" << endl;
    if (symtab->find(name) == NULL && name != "write" && name != "read") {
        checkOut << getLineNum() << ": " << "Can not find the function " << name << "." << endl;
        return "failure";
    }

    SymbolBucket *func = symtab->find(name);
    int i = 0;
    if (func != NULL) {
        SymbolBucket *member = func->getNextBucket();
        do {
            string argType = (*args)[i]->typeCheck(symtab);//对每一个实参检查类型
            string memberType = member->getSymbol()->getTypeName();
            if (argType.find(memberType) == string::npos) {
                checkOut << getLineNum() << " : argument " << (*args)[i]->getName() << " type dismatch！" << endl;
                return "failure";
            }
            i++;
            member = member->getLastBucket()->getNextBucket();
        } while (i < (*args).size() && member != func);//member != func->getLastBucket() &&
        if (i < (*args).size()) {
            checkOut << getLineNum() << " : number of arguments is not match!" << endl;
            return "failure";
        }
    }
    if (func != NULL)
        return func->getLastBucket()->getSymbol()->getTypeName();
    else return "success";
}

string RecordElemTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "record elem treenode: " << rname << " check type" << endl;
    SymbolBucket *bucket = symtab->find(rname);
    if (bucket == NULL) {
        checkOut << getLineNum() << ": " << "Can not find the record " << rname << "." << endl;
        return "failure";
    }
    SymbolBucket *member = bucket->getNextBucket();
    do {
        if (member->getSymbol()->getName() == ename) {
            return member->getSymbol()->getTypeName();
        }
        member = member->getLastBucket()->getNextBucket();
    } while (member != bucket);
    checkOut << getLineNum() << ": " << "Can not find the element " << ename << " in the record " << rname << "."
             << endl;
    return "failure";
}

SymbolBucket *CompoundStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    stmtlist->genCode(symbolTable);
    return NULL;
}

SymbolBucket *FuncOrProcTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    string label = name;
    //labelManager->addFuncLabel(label);
    CodeGenerator::addLabel(label);
    body->genCode(tab);
    return NULL;
}
