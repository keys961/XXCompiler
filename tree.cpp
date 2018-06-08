#include "tree.h"
#include "codegen.h"
#include <sstream>

bool isMain = true;

//void selectOP(SymbolBucket *bucket, int &reg, std::string &load, std::string &store, int &loc, int currentLevel = 0) {
//    if (reg == -3 && bucket != nullptr) {
//        reg = -1;
//        // loc = bucket->getOffsetReg();
//        // 表明 loc是一个寄存器号，array和record的情形
//        loc = bucket->getSymbol()->getLocation();
//        load = "load_reg";
//        store = "store_reg";
//        return;
//    } else {
//        load = "load";
//        store = "store";
//    }
//
//    if (reg == -1 && bucket != nullptr) {
//        loc = bucket->getSymbol()->getLocation();
//        std::cout << "in select " << bucket->getCurrentTable() << std::endl;
//        int level = bucket->getCurrentTable()->getLevel();
//        if (level < currentLevel) {
//            char ch[5] = {0,};
//            sprintf(ch, "%d", currentLevel - level);
//            load = load + "-" + ch;
//            store = store + "-" + ch;
//        }
//    }
//
//    std::cout << "out select" << std::endl;
//}

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
    for (auto &i : list) {
        i->updateEnvironment(symtab);
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
            b->getSymbol()->setLocation(symtab->getAndUpdateLocation(b->getSymbol()->getSize()));
        }
    }
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
    vector<SymbolBucket *> v;
    subSymtab->getSymBucketList(v);
    SymbolBucket *tmpBucket = bucket;
    subSymtab->setLocation(0);//初始化函数符号表的栈深度为0
    for (auto &i : v) {
        if (isPrint)cout << "func - " << name << " : " << i->getSymbol()->getName() << endl;
        i->getSymbol()->setLocation(subSymtab->getAndUpdateLocation(i->getSymbol()->getSize()));
        auto *newBucket = new SymbolBucket(i);
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
        auto *returnNameBucket = new SymbolBucket(returnTypeBucket);
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
    auto *rop = (LiteralTreeNode *) this->roprand;
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
    SymbolBucket *end = new SymbolBucket(rop->getLiteralType(), getLineNum(), cu, symtab);
    //标记大小
    head->getSymbol()->setSize(getSizeByType(rop->getLiteralType()));
    end->getSymbol()->setSize(getSizeByType(this->roprand->getName()));
    head->getSymbol()->setLocation(symtab->getAndUpdateLocation(getSizeByType(rop->getLiteralType())));
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
    size = (upper - lower + 1) * elemBucket->getSymbol()->getSize();//数组在栈中总大小
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
    int u = ((LiteralTreeNode *) upper)->getInt() - 1;//range上界
    int l = ((LiteralTreeNode *) lower)->getInt() - 1;//range下界
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
    for (auto &elem : elems) {
        auto *v = (VariableTreeNode *) elem;
        SymbolBucket *vb = v->getTypeNode()->genSymBucket(elem->getName(), symtab);
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
    for (auto &i : this->list) {
        if ((i->typeCheck(symtab)) == "failure") {
            res = "failure";
        }
    }
    return res;
}

//===============代码生成===============
//todo 初始化
SymbolBucket *ProgramBodyTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    if (!isMain) {
        //刚进来时，SP位于RA所在的4字节内存的底部，要取到RA所在的地址头需要+4
        CodeGenerator::genIType("+", SP, SP, 4);
        CodeGenerator::emitCodeM(STORE, 0, SP, RA);
        CodeGenerator::genIType("-", SP, SP, 4);
        //此处同步FP、SP
        CodeGenerator::genRType("+", FP, SP, 0);
    } else {
        code << ".data 0x10000000" << std::endl;
        for (auto &iter : constCharMap) {
            std::string constStr = iter.first;
            std::string label = iter.second;
            CodeGenerator::emitCodeConstStr(constStr, label);
        }
        for (auto &iter : constRealMap) {
            std::string constStr = iter.first;
            std::string label = iter.second;
            CodeGenerator::emitCodeConstReal(constStr, label);
        }
        code << ".text" << std::endl;
        code << "main:" << std::endl;
    }

    std::vector<SymbolBucket *> bucketList;
    //todo 获取bucketlist
    symbolTable->getSymBucketList(bucketList);
    //所需的栈大小
    int totalStackSize = 0;
//    for (int i = 0; i < bucketList.size(); i++) {
//        SymbolBucket *b = bucketList[i];
//        if (b->getSymbol()->getLocation() != -1) {
//            std::cout << b->getSymbol()->getName() << "'s size is " << b->getSymbol()->getSize() << std::endl;
//            totalStackSize += b->getSymbol()->getSize();
//        }
//    }
    for(SymbolBucket *bucket : bucketList) {
        if (bucket->getSymbol()->getLocation() != -1) {
            std::cout << bucket->getSymbol()->getName() << "'s size is " << bucket->getSymbol()->getSize() << std::endl;
            totalStackSize += bucket->getSymbol()->getSize();
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
    if (!isMain) {
        //当前函数名
        std::string programName = symbolTable->getTableName();
        programName = programName.substr(0, programName.find('-'));
        //最后最后一个symbol的名字
        std::string lastSymbolName = bucketList[bucketList.size() - 1]->getSymbol()->getName();
        //两者相等说明该函数有返回值
        if(programName == lastSymbolName) {
            SymbolBucket *returnValueBucket = bucketList[bucketList.size() - 1];
            int location = returnValueBucket->getSymbol()->getLocation();
            std::string type = returnValueBucket->getSymbol()->getTypeName();
            if(type == "integer" || type == "char") {
                CodeGenerator::emitCodeM(LOAD, -location, FP, 3);
                CodeGenerator::emitCodeM(STORE, 8, FP, 3);
            } else if(type == "real") {
                int tmpReg = regManager->getTmpReg(1);
                CodeGenerator::emitCodeM(LOAD, -location, FP, tmpReg);
                CodeGenerator::emitCodeM(STORE, 8, FP, tmpReg);
                regManager->freeReg(tmpReg);
            }
        }
        //12指的是存fp、v1、ra的内存大小，12字节
        CodeGenerator::genIType("+", SP, SP, totalStackSize + 12);
        CodeGenerator::emitCodeM(LOAD, 4, FP, RA);
        CodeGenerator::genRType("jr", RA, 0, 0);
    } else {
        CodeGenerator::genJType("j", "exit");
    }
    if (isMain) {
        isMain = false;
    }
    routine_decl->genCode(symbolTable);
    return nullptr;
}

SymbolBucket *ListTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    std::cout << list.size() << std::endl;
    for (auto &i : list) {
        i->genCode(symbolTable, reg);
    }
    return nullptr;
}

void CallExprTreeNode::genSysFunc(SymbolTable *symbolTable, std::string name) {
    if ((*args).size() > 1 || (*args).empty()) {
        std::cout << getLineNum() << " write's argument num is incorrect " << std::endl;
    }
    int argReg;
    SymbolBucket *argBucket = (*args)[0]->genCode(symbolTable, &argReg);
    std::string type = argBucket->getSymbol()->getTypeName();
    std::string loadOP, storeOP;
    int location;
//    selectOP(argBucket, argReg, loadOP, storeOP, location, symbolTable->getLevel());
    location = argBucket->getSymbol()->getLocation();
    if (type == "integer") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(LOAD, -location, FP, A0);
        } else if (argReg == -2) {
            int imme = argBucket->getSymbol()->getImmediateValue();
            CodeGenerator::genIType("+", A0, 0, imme);
        }
        CodeGenerator::emitSysCall("printInteger");
    } else if (type == "real") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(LOAD, -location, FP, F12, 1);
        } else if (argReg == -2) {
            int imme = argBucket->getSymbol()->getImmediateValue();
            CodeGenerator::genIType("+", F12, 0, imme);
        }
        CodeGenerator::emitSysCall("printReal");
    } else if (type == "char") {
        if (argReg == -1) {
            CodeGenerator::emitCodeM(LOAD, -location, FP, A0);
        } else if (argReg > 0) {
            CodeGenerator::emitCodeM(LOAD, 0, argReg, A0);
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
        return nullptr;
    }
    environment = symbolTable;
    std::cout << name << std::endl;
    SymbolBucket *funcBucket = environment->find(name);
    std::cout << funcBucket << std::endl;
    SymbolBucket *returnBucket;
    returnBucket = new SymbolBucket(funcBucket->getSymbol(), symbolTable);
    if (funcBucket->getSymbol()->getTypeName() != "func")
        returnBucket->getSymbol()->setTypeName("null");
    std::vector<SymbolBucket *> argsTypeList;
    SymbolBucket *member = funcBucket->getNextBucket();
    do {
        argsTypeList.push_back(funcBucket->getNextTable()->find(member->getSymbol()->getName()));
        member = member->getLastBucket()->getNextBucket();
    } while (member != funcBucket);
    //依次压入FP（调用者的）、返回值、返回地址
    CodeGenerator::emitCodeM(STORE, 0, SP, FP);
    CodeGenerator::emitCodeM(STORE, -4, SP, V1);
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
//        selectOP(argBucket, argReg, loadOP, storeOP, argLoc, symbolTable->getLevel());
        //-2表明参数是字面量，则直接从该bucket的symbol的立即值中取值
        if (argReg == -2) {
            CodeGenerator::genIType("+", tmpDst, 0, argBucket->getSymbol()->getImmediateValue());
        } else {
            argLoc = argBucket->getSymbol()->getLocation();
            //将参数放到tmpDst寄存器
            CodeGenerator::emitCodeM(LOAD, -argLoc, FP, tmpDst);
        }

        //将tmpDst中的值压栈
        CodeGenerator::emitCodeM(STORE, -argType->getSymbol()->getSize() * i, SP, tmpDst);
        regManager->freeReg(tmpDst);
        delete argBucket;
    }

    CodeGenerator::genJType("jal", name);
    if (isFunc) {
        tmp = regManager->getTmpReg();
        CodeGenerator::emitCodeM(LOAD, 8, FP, V1);
        CodeGenerator::genRType("+", tmp, V1, 0);
        if (reg != nullptr) *reg = tmp;
    } else {
        if (reg != nullptr) *reg = -4;
    }

    CodeGenerator::emitCodeM(LOAD, 12, FP, FP);
    std::cout << "out call " << std::endl;
    autoFreeReg(tmp, reg);
    return returnBucket;
}

SymbolBucket *VariableTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    if (reg != nullptr)
        *reg = -1;
//    if (!isConst) {
    std::cout << "vg : " << name << " environment : " << symbolTable << std::endl;
    environment = symbolTable;
    SymbolBucket *b = environment->find(name);
    std::cout << "b = " << b << std::endl;
    if (b == nullptr) {
        std::cout << getLineNum() << ": variable " << name << " is not defined" << std::endl;
    }
    auto *returnBucket = new SymbolBucket(*b);
    if (isConst) {
        returnBucket->getSymbol()->setTypeName(b->getNextBucket()->getSymbol()->getName());
    }
    returnBucket->setCurrentTable(b->getCurrentTable());
    return returnBucket;
//    }
//    else {
////        traceGen("cg");
//        VariableTreeNode *lhs = new VariableTreeNode(name);
//        BinaryExprTreeNode *binaryExprTreeNode = new BinaryExprTreeNode("=", lhs, constValue);
//        binaryExprTreeNode->genCode(symbolTable);
//        regManager->freeAll();
//
//    }
}

SymbolBucket *BinaryExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    int regR, regL;
    int locationR = 0, locationL = 0;
    // for arrayElem and recordElem
    SymbolBucket *bucketR, *bucketL, *returnBucket;
    bucketR = roprand->genCode(environment, &regR);
    bucketL = loprand->genCode(environment, &regL);
    int isFloat = isFloatType(bucketR, regR) && isFloatType(bucketL, regL);
    if (bucketL != nullptr)
        returnBucket = new SymbolBucket(*bucketL);
    else
        returnBucket = nullptr;
    std::string loadOPR, storeOPR;
    std::string loadOPL, storeOPL;
//    selectOP(bucketR, regR, loadOPR, storeOPR, locationR, symbolTable->getLevel());
//    selectOP(bucketL, regL, loadOPL, storeOPL, locationL, symbolTable->getLevel());
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
                CodeGenerator::emitCodeM(LOAD, locationR, FP, tmpSrc_1, isFloat);
                CodeGenerator::emitCodeM(STORE, locationL, FP, tmpSrc_1, isFloat);
                if (reg != nullptr)
                    *reg = -1;
            }
        } else {
            CodeGenerator::emitCodeM(LOAD, locationL, FP, tmpSrc_1, isFloat);
            CodeGenerator::emitCodeM(LOAD, locationR, FP, tmpSrc_2, isFloat);
            CodeGenerator::genRType(op, tmpDst, tmpSrc_1, tmpSrc_2, isFloat);
            if (reg != nullptr) *reg = tmpDst;
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
        if (bucketR != nullptr)
            intImmeR = bucketR->getSymbol()->getImmediateValue();
        if (bucketL != nullptr)
            intImmeL = bucketL->getSymbol()->getImmediateValue();

        cout << "immeR = " << intImmeR << " immeL = " << intImmeL << endl;
        if (regL == -2 && regR == -2) {
            tmpDst = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpDst, tmpDst, intImmeR);
            CodeGenerator::genIType(op, tmpDst, tmpDst, intImmeL);
            if (reg != nullptr) *reg = tmpDst;
        } else if (regL == -2 && regR == -1) {
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::emitCodeM(LOAD, locationR, FP, tmpSrc, isFloat);
            CodeGenerator::genIType(op, tmpDst, tmpSrc, intImmeL);
            if (reg != nullptr) *reg = tmpDst;
        } else if (regL == -1 && regR == -2) {
            if (op == ":=") {
                tmpDst = regManager->getTmpReg(isFloat);
                CodeGenerator::genIType(op, tmpDst, 0, intImmeR);
                CodeGenerator::emitCodeM(STORE, locationL, FP, tmpDst, isFloat);
                if (reg != nullptr) *reg = tmpDst;
            } else {
                tmpDst = regManager->getTmpReg(isFloat);
                tmpSrc = regManager->getTmpReg(isFloat);
                CodeGenerator::emitCodeM(LOAD, locationL, FP, tmpSrc, isFloat);
                CodeGenerator::genIType(op, tmpDst, tmpSrc, intImmeR);
                if (reg != nullptr) *reg = tmpDst;
            }
        } else if (regL == -2 && regR > 0) {
            //左边字面量，右边在寄存器里，则不会有“:=”的情况
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpSrc, 0, intImmeL);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regR);
            if (reg != nullptr) *reg = tmpDst;
        } else if (regL > 0 && regR == -2) {
            //左边在寄存器里，右边字面量，也不会有:=的情况
            tmpDst = regManager->getTmpReg(isFloat);
            tmpSrc = regManager->getTmpReg(isFloat);
            CodeGenerator::genIType(op, tmpSrc, 0, intImmeR);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regL);
            if (reg != nullptr) *reg = tmpDst;
        }
        regManager->freeReg(tmpSrc);
        autoFreeReg(tmpDst, reg);
    } else if (regR > 0) {
        int tmpSrc = regManager->getTmpReg(isFloat);
        int tmpDst = regManager->getTmpReg(isFloat);
        if (op == ":=") {
            CodeGenerator::emitCodeM(STORE, locationL, FP, regR, isFloat);
            if (reg != nullptr) *reg = -1;
        } else {
            CodeGenerator::emitCodeM(LOAD, locationL, FP, tmpSrc, isFloat);
            CodeGenerator::genRType(op, tmpDst, tmpSrc, regR);
            if (reg != nullptr) *reg = tmpDst;
        }
        regManager->freeReg(tmpSrc);
        autoFreeReg(tmpDst, reg);
    } else if(regL > 0 && regR == -1) {
        //左边在寄存器里，右边在内存里
        int tmpSrc = regManager->getTmpReg(isFloat);
        CodeGenerator::emitCodeM(LOAD, locationR, FP, tmpSrc, isFloat);
        CodeGenerator::genRType(op, regL, regL, tmpSrc);
        if (reg != nullptr) *reg = regL;
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
//    selectOP(bucketL, regL, loadOPL, storeOPL, locationL, symbolTable->getLevel());
    CodeGenerator::genIType("beq", regL, 0, 0, breakLabel);
    body->genCode(symbolTable, &regR);
    CodeGenerator::genJType("j", loopLabel);
    //将循环结束标签紧接在循环体后面，结束循环时只要跳到此处即可
    CodeGenerator::addLabel(breakLabel);
    delete bucketL;
    //todo free寄存器
    regManager->freeReg(regL);
    regManager->freeReg(regR);
    return nullptr;
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
    CodeGenerator::emitCodeM(LOAD, idBucket->getSymbol()->getLocation(), FP, idReg);
    bucketR = dst->genCode(symbolTable, &regR);
//    selectOP(bucketR, regR, loadOPR, storeOPR, locationR, symbolTable->getLevel());
    locationR = bucketR->getSymbol()->getLocation();
    int compReg = regManager->getTmpReg();
    int dstReg = regManager->getTmpReg();
    //获取循环终值，与当前id值进行比较以决定是否跳出循环
    if (locationR == -1) {
        int immeR = bucketR->getSymbol()->getImmediateValue();
        CodeGenerator::genIType("+", dstReg, 0, immeR);
    } else {
        CodeGenerator::emitCodeM(LOAD, locationR, FP, dstReg);
    }
    CodeGenerator::genRType("<=", compReg, idReg, dstReg);
    CodeGenerator::genIType("beq", compReg, 0, 0, breakLabel);
    regManager->freeReg(dstReg);
    //生成循环体
    body->genCode(symbolTable, &bodyReg);

    //根据for循环的类型决定进行id++或id--
    int tmp = regManager->getTmpReg();
    CodeGenerator::emitCodeM(LOAD, idBucket->getSymbol()->getLocation(), FP, tmp);
    if (direction == "to") {
        CodeGenerator::genIType("+", tmp, tmp, 1);
    } else {
        CodeGenerator::genIType("-", tmp, tmp, 1);
    }

    CodeGenerator::emitCodeM(STORE, idBucket->getSymbol()->getLocation(), FP, tmp);
    CodeGenerator::genJType("j", loopLabel);
    CodeGenerator::addLabel(breakLabel);
    regManager->freeReg(tmp);
    regManager->freeReg(regR);
    regManager->freeReg(bodyReg);
    regManager->freeReg(idReg);
    delete bucketL;
    delete bucketR;
    return nullptr;
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
//    selectOP(bucketE, regE, loadOPE, storeOPE, locationE, symtab->getLevel());
    if (regE == -1) {
        int tmp = regManager->getTmpReg();
        CodeGenerator::emitCodeM(LOAD, locationE, FP, tmp);
        //case
        bucketCase = case_list->genCode(symtab, &tmp);
        regManager->freeReg(tmp);
    } else if (regE > 0) {
        bucketCase = case_list->genCode(symtab, &regE);
    }
    regManager->freeReg(regE);
    int switchNumber = labelManager->getSwitchLabel();
    std::stringstream ss;
    ss << "endSwitch" << switchNumber;
    std::string endSwitchLabel = ss.str();
    CodeGenerator::addLabel(endSwitchLabel);
    labelManager->addSwitchLabel();
    delete bucketE;
    return nullptr;
}

SymbolBucket *CaseExprTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    SymbolBucket *caseBucket;
    int idReg, regE;
    int caseLocation;
    std::string loadOPID, storeOPID;
    int caseNum = labelManager->getCaseLabel();
    std::stringstream ss;
    ss << "case" << caseNum;
    std::string caseLabel = ss.str();
    ss.str("");
    ss << "endSwitch" << labelManager->getSwitchLabel();
    std::string endSwitchLabel = ss.str();
    regE = *reg;

    caseBucket = label->genCode(symbolTable, &idReg);

//    selectOP(caseBucket, idReg, loadOPID, storeOPID, caseLocation, symbolTable->getLevel());
    caseLocation = caseBucket->getSymbol()->getLocation();
    int tmpReg = regManager->getTmpReg();
    if(caseLocation < 0) {
        CodeGenerator::genIType("+", tmpReg, 0, caseBucket->getSymbol()->getImmediateValue());
    } else {
        CodeGenerator::emitCodeM(LOAD, -caseLocation, FP, tmpReg);
    }
    CodeGenerator::genIType("bne", tmpReg, regE, 0, caseLabel);
    labelManager->addCaseLabel();
    regManager->freeReg(tmpReg);
    regManager->freeReg(idReg);
    body->genCode(symbolTable);
    CodeGenerator::genJType("j", endSwitchLabel);
    CodeGenerator::addLabel(caseLabel);
    delete caseBucket;
}

SymbolBucket *IfStmtTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    SymbolBucket *bucketC;
    int regC, regB, regE;
    int locationC;
    int ifNum = labelManager->getIfLabel();
    std::string loadOPC, storeOPC;
    bucketC = condition->genCode(symbolTable, &regC);
//    selectOP(bucketC, regC, loadOPC, storeOPC, locationC, symbolTable->getLevel());
    locationC = bucketC->getSymbol()->getLocation();

    std::stringstream ss;
    ss << "endif" << ifNum;
    std::string endifLabel = ss.str();
    ss.str("");
    ss << "endelse" << ifNum;
    std::string endelseLabel = ss.str();

    CodeGenerator::genIType("beq", regC, 0, 0, endifLabel);

    then_stmt->genCode(symbolTable, &regB);
    if (else_stmt != nullptr) {
        CodeGenerator::genJType("j", endelseLabel);
        CodeGenerator::addLabel(endifLabel);
        else_stmt->genCode(symbolTable, &regE);
        CodeGenerator::addLabel(endelseLabel);
    } else {
        CodeGenerator::addLabel(endifLabel);
    }
    labelManager->addIfLabel();
    regManager->freeReg(regC);
    return nullptr;
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
//    selectOP(bucketC, regC, loadOPC, storeOPC, locationC, symbolTable->getLevel());
    locationC = bucketC->getSymbol()->getLocation();
    CodeGenerator::genIType("beq", regC, 0, 0, doLabel);

    regManager->freeReg(regC);
    return nullptr;
}

SymbolBucket *ArrayElemTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    //获取整个数组的symbolbucket, 这个bucket的location表示的是数组的第一个元素的location
    SymbolBucket *type = environment->find(name);
    //获取数组的元素类型
    SymbolBucket *elemType = type->getLastBucket();
    auto *returnBucket = new SymbolBucket(elemType->getSymbol(), symbolTable);
    int exprReg;
    //获取当前所需要的数组元素的bucket
    SymbolBucket *indexBucket = index->genCode(symbolTable, &exprReg);
    //数组的元素类型的大小
    int elemSize = elemType->getSymbol()->getSize();
    //数组的第一个元素的location
    int firstLocation = type->getSymbol()->getLocation();
    //当前元素栈偏移
    int indexLocation;
//    std::string loadOP, storeOP;
//    selectOP(indexBucket, exprReg, loadOP, storeOP, indexLocation, symbolTable->getLevel());
//    indexLocation = indexBucket->getSymbol()->getLocation();
    if (exprReg == -2) {
        indexLocation = firstLocation + indexBucket->getSymbol()->getImmediateValue() * elemSize;
    }
//    int tmpSrc_1 = regManager->getTmpReg();
//    int tmpSrc_2 = regManager->getTmpReg();
//    int tmpDst = regManager->getTmpReg();
//    CodeGenerator::emitCodeM("load", -indexLocation, FP, tmpSrc_1);
//    CodeGenerator::genIType("+", tmpSrc_2, 0, elemSize);
//    CodeGenerator::genRType("*", tmpDst, tmpSrc_1, tmpSrc_2);
//    CodeGenerator::genIType("+", tmpDst, tmpDst, type->getSymbol()->getLocation());
    if (reg != nullptr) *reg = -1;
    //returnBucket->setOffsetReg(tmpDst);
    returnBucket->getSymbol()->setLocation(indexLocation);
//    regManager->freeReg(tmpSrc_1);
//    regManager->freeReg(tmpSrc_2);

    returnBucket->getSymbol()->setSize(elemSize);
//    autoFreeReg(exprReg, reg);
    return returnBucket;
}

SymbolBucket *RecordElemTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    environment = symbolTable;
    SymbolBucket *returnBucket = nullptr;
    SymbolBucket *bucket = environment->find(rname);
    SymbolBucket *member = bucket->getNextBucket();
    do {
        if (member->getSymbol()->getName() == ename) {
            returnBucket = new SymbolBucket(member->getSymbol(), symbolTable);
            returnBucket->getSymbol()->setLocation(member->getSymbol()->getLocation());
            returnBucket->getSymbol()->setSize(member->getSymbol()->getSize());
            break;
        }
        member = member->getNextBucket();
    } while (member != bucket);
    if (reg != nullptr) *reg = -1;
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
    auto *returnBucket = new SymbolBucket(oprandBucket->getSymbol(), symbolTable);
//    selectOP(oprandBucket, oprandReg, loadOP, storeOP, operandLocation, symbolTable->getLevel());
    std::cout << "in unaryExpr reg = " << oprandReg << " with op = " << op << std::endl;
    if (oprandBucket->getSymbol()->getLocation() >= 0) {
        operandLocation = oprandBucket->getSymbol()->getLocation();
        int tmpDst = regManager->getTmpReg();

        CodeGenerator::emitCodeM(LOAD, -operandLocation, FP, tmpDst);
        CodeGenerator::genRType(op, tmpDst, 0, tmpDst);
        if (reg != nullptr) *reg = tmpDst;
    } else {
//        if (op == "-")
//            returnBucket->getSymbol()->setImmediateValue(-oprandBucket->getSymbol()->getImmediateValue());
//        else
//            returnBucket->getSymbol()->setImmediateValue(oprandBucket->getSymbol()->getImmediateValue());
//        if(reg != NULL) *reg = -2;
        int intImme = oprandBucket->getSymbol()->getImmediateValue();
        int tmpDst = regManager->getTmpReg();
        CodeGenerator::genIType("+", tmpDst, 0, intImme);
        CodeGenerator::genRType(op, tmpDst, 0, tmpDst);
        if (reg != nullptr) *reg = tmpDst;
    }


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
    auto *returnBucket = new SymbolBucket(symbol, symbolTable);
    returnBucket->getSymbol()->setSize(getSize(type));

    if (type == "integer") {
        returnBucket->getSymbol()->setImmediateValue(getInt());
        if (reg != nullptr) *reg = -2;
    } else if (type == "real") {
        int labelReg = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constRealMap[value], labelReg);
        int tmpDst = regManager->getTmpReg(1);
        CodeGenerator::emitCodeM(LOAD, 0, labelReg, tmpDst, 1);
        if (reg != nullptr) *reg = tmpDst;
        regManager->freeReg(labelReg);
    } else {
        int labelReg = regManager->getTmpReg();
        CodeGenerator::emitCodeLA(constCharMap[value], labelReg);
        if (reg != nullptr) *reg = labelReg;
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
    if (b == nullptr || b->getSymbol()->getTypeName() != "array") {
        if (b == nullptr)
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
    if (s1 != "failure" && s2 != "failure" && (this->else_stmt == nullptr ? 1 : (s3 != "failure"))) {
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
    if (symtab->find(name) == nullptr && name != "write" && name != "read") {
        checkOut << getLineNum() << ": " << "Can not find the function " << name << "." << endl;
        return "failure";
    }

    SymbolBucket *func = symtab->find(name);
    int i = 0;
    if (func != nullptr) {
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
    if (func != nullptr)
        return func->getLastBucket()->getSymbol()->getTypeName();
    else return "success";
}

string RecordElemTreeNode::typeCheck(SymbolTable *symtab) {
    checkOut << "record elem treenode: " << rname << " check type" << endl;
    SymbolBucket *bucket = symtab->find(rname);
    if (bucket == nullptr) {
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
    return nullptr;
}

SymbolBucket *FuncOrProcTreeNode::genCode(SymbolTable *symbolTable, int *reg) {
    string label = name;
    //labelManager->addFuncLabel(label);
    CodeGenerator::addLabel(label);
    body->genCode(tab);
    return nullptr;
}
