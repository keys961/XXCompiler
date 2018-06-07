#include "tree.h"

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
        //设置函数返回值在函数符号表中的位置
        returnNameBucket->getSymbol()->setLocation(subSymtab->getAndUpdateLocation(returnNameBucket->getSymbol()->getSize()));
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
    } else if (rop->getLiteralType() == "string") {
        sprintf(cu, "%s", rop->getString().c_str());//todo
    } else if (rop->getLiteralType() == "real") {
        sprintf(cu, "%f", rop->getDouble());
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

