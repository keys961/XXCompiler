#ifndef COMPILER_TREE_H
#define COMPILER_TREE_H

#include <string>
#include <vector>
#include "symbol.h"

class TreeNode {
private:
    std::string name;
    int lineNum;
    long addr;

protected:
    SymbolTable *environment;
    std::vector<TreeNode *> children;

public:

    TreeNode() : addr((long) this) {}

    const std::string &getName() const {
        return name;
    }

    void setName(const std::string &name) {
        this->name = name;
    }

    int getLineNum() const {
        return lineNum;
    }

    void setLineNum(int lineNum) {
        this->lineNum = lineNum;
    }

    SymbolTable *getEnvironment() const {
        return environment;
    }

    void setEnvironment(SymbolTable *environment) {
        this->environment = environment;
    }

    virtual void updateEnvironment(SymbolTable *environment) {}

    virtual SymbolBucket *generateCode(SymbolTable *environment) { return NULL; }

    virtual std::string typeCheck(SymbolTable *environment) { return "type check"; }


};

class StatementTreeNode : public TreeNode {

protected:
    int label;

public:
    virtual ~StatementTreeNode();

    void setLabel(int label);

    void printSelf();

};

class ExprTreeNode : public TreeNode {

public:
    virtual ~ExprTreeNode();

    void printSelf();
};

class ListTreeNode : public TreeNode {
private:
    const std::string type;
    std::vector<TreeNode *> list;

public:

    ListTreeNode(const std::string _name, std::vector<TreeNode *> &_list)
            : type(_name), list(_list) {
    }

    void insert(TreeNode *newNode) {
        list.push_back(newNode);
    }

    TreeNode *get(int index) {
        return list[index];
    }

    int size() {
        return list.size();
    }

    std::vector<TreeNode *> &getList() {
        return list;
    }

    void printSelf();

    std::vector<TreeNode *> getChildren() {
        return list;
    }
};

class FuncOrProcTreeNode : public TreeNode {
private:
    const std::string name;
    ListTreeNode *args;
    ListTreeNode *body;
    CommonTypeTreeNode *return_type;
    bool isFunc;
    SymbolTable *tab;

public:
    FuncOrProcTreeNode(const std::string name, TreeNode *args, TreeNode *body,
                       TreeNode *rtype=nullptr,bool isFunc=false)
            : name(name), args((ListTreeNode *) args), body((ListTreeNode *) body),
              isFunc(isFunc),return_type((CommonTypeTreeNode*)rtype)
    {
        children.push_back(this->args);
        children.push_back(this->body);
    }
};

class IDTreeNode : public TreeNode {
public:
    virtual ~IDTreeNode() {}

    void printSelf();

    virtual const std::string getType();
};

class ProgramHeadTreeNode : public TreeNode {
private:
    const std::string name;
public:
    ProgramHeadTreeNode(const std::string name) : name(name) {}

};

class ProgramBodyTreeNode : public TreeNode {
private:
    ListTreeNode *const_decl;
    ListTreeNode *type_decl;
    ListTreeNode *var_decl;
    ListTreeNode *routine_decl;
    ListTreeNode *body;

public:
    ProgramBodyTreeNode(TreeNode *const_,
                        TreeNode *type_,
                        TreeNode *var_,
                        TreeNode *routine_,
                        TreeNode *body_)
            : const_decl((ListTreeNode *) const_), type_decl((ListTreeNode *) type_),
              var_decl((ListTreeNode *) var_), routine_decl((ListTreeNode *) routine_), body((ListTreeNode *) body_) {
        children.push_back(const_decl);
        children.push_back(type_decl);
        children.push_back(var_decl);
        children.push_back(routine_decl);
        children.push_back(body);
    }
};

class TypeTreeNode : public TreeNode {
public:
    virtual ~TypeTreeNode() {}

    void printSelf();
};

//-----------------------------------------------
//Expr treenode

class BinaryExprTreeNode : public ExprTreeNode {
private:
    const std::string op;
    TreeNode *loprand;
    TreeNode *roprand;

public:
    BinaryExprTreeNode(const std::string op, TreeNode *loprand, TreeNode *roprand)
            : op(op), loprand(loprand), roprand(roprand) {
        children.push_back(roprand);
        children.push_back(loprand);
    }
};

class UnaryExprTreeNode : public ExprTreeNode {
private:
    const std::string op;
    TreeNode *oprand;

public:
    UnaryExprTreeNode(const std::string op, TreeNode *oprand) : op(op), oprand(oprand) {
        children.push_back(oprand);
    }
};

class CallExprTreeNode : public ExprTreeNode {
private:
    const std::string name;//function name or procedure name
    std::vector<TreeNode *> *args;
    bool isFunc;

public:
    CallExprTreeNode(const std::string name, std::vector<TreeNode *> *args = nullptr, bool isFunc = true)
            : name(name), args(args), isFunc(isFunc) {}

};

class CaseExprTreeNode : public ExprTreeNode {
private:
    IDTreeNode *label;//case后跟的值
    StatementTreeNode *body;//冒号后的条件句

public:
    CaseExprTreeNode(IDTreeNode *label, StatementTreeNode *body)
            : label(label), body(body) {}
};

//--------------------------------------------
//type treenode

//系统自带简单类型
class CommonTypeTreeNode : public TypeTreeNode {
private:
    const std::string type;//string int char double
public:
    CommonTypeTreeNode(const std::string type) : type(type) {}
};

class RangeTypeTreeNode : public TypeTreeNode {
private:
    IDTreeNode *upper;
    IDTreeNode *lower;

public:
    RangeTypeTreeNode(IDTreeNode *upper, IDTreeNode *lower) : upper(upper), lower(lower) {}

};

class ArrayTypeTreeNode : public TypeTreeNode {
private:
    RangeTypeTreeNode *index;//数组下标范围
    CommonTypeTreeNode *elem;//数组元素类型

public:
    ArrayTypeTreeNode(RangeTypeTreeNode *index, CommonTypeTreeNode *elem)
            : index(index), elem(elem) {}
};

//结构体类型
class RecordTypeTreeNode : public TypeTreeNode {
private:
    std::vector<TreeNode *> elems;//record的各个域可以是不同的类型

public:
    RecordTypeTreeNode(std::vector<TreeNode *> &elems) : elems(elems) {}

    void insert(TreeNode *tmp) {
        this->elems.push_back(tmp);
    }

    TreeNode *get(int index) {
        return elems[index];
    }

    int size() {
        return elems.size();
    }

    std::vector<TreeNode *> &getList() {
        return elems;
    }

    void printSelf();

    std::vector<TreeNode *> getChildren() {
        return elems;
    }
};

class EnumTypeTreeNode : public TypeTreeNode {
private:
    ListTreeNode *elems;
    const std::string name;

public:
    EnumTypeTreeNode(TreeNode *elems,const std::string name)
            : elems((ListTreeNode *) elems),name(name) {}
};

//用户自定义类型
class CustomTypeTreeNode : public TypeTreeNode {
private:
    const std::string name;
    TypeTreeNode *type;
public:
    CustomTypeTreeNode(const std::string name, TreeNode *type)
            : name(name), type((TypeTreeNode *) type) {}
};

//---------------------------------------
//statement tree node

//复合条件句(begin...end)
class CompoundStmtTreeNode : public StatementTreeNode {
private:
    ListTreeNode *stmtlist;

public:
    CompoundStmtTreeNode(ListTreeNode *list) : stmtlist(list) {
        children.push_back(stmtlist);
    }
};

class IfStmtTreeNode : public StatementTreeNode {
private:
    ExprTreeNode *condition;
    StatementTreeNode *then_stmt;
    StatementTreeNode *else_stmt;

public:

    IfStmtTreeNode(ExprTreeNode *c, StatementTreeNode *t, StatementTreeNode *e = nullptr)
            : condition(c), then_stmt(t), else_stmt(e) {
        children.push_back(c);
        children.push_back(t);
        if (e != nullptr)
            children.push_back(e);
    }
};

class RepeatStmtTreeNode : public StatementTreeNode {
private:
    ExprTreeNode *condition;
    StatementTreeNode *body;

public:
    RepeatStmtTreeNode(ExprTreeNode *condition, StatementTreeNode *body)
            : condition(condition), body(body) {
        children.push_back(condition);
        children.push_back(body);
    }
};

class WhileStmtTreeNode : public StatementTreeNode {
private:
    ExprTreeNode *condition;
    StatementTreeNode *body;

public:
    WhileStmtTreeNode(ExprTreeNode *condition, StatementTreeNode *body)
            : condition(condition), body(body) {
        children.push_back(condition);
        children.push_back(body);
    }
};

class SwitchStmtTreeNode : public StatementTreeNode {
private:
    ExprTreeNode *expr;
    ListTreeNode *case_list;
public:
    SwitchStmtTreeNode(ExprTreeNode *expr, ListTreeNode *list)
            : expr(expr), case_list(list) {
        children.push_back(expr);
        children.push_back(list);
    }

};

class ForStmtTreeNode : public StatementTreeNode {
private:
    ExprTreeNode *src;//循环初始值
    const std::string direction; //to or downto
    ExprTreeNode *dst; //循环结束值
    StatementTreeNode *body;
public:
    ForStmtTreeNode(ExprTreeNode *src, const std::string direc,
                    ExprTreeNode *dst, StatementTreeNode *body)
            : src(src), direction(direc), dst(dst), body(body) {
        children.push_back(src);
        children.push_back(dst);
        children.push_back(body);
    }

};

class GotoStmtTreeNode : public StatementTreeNode {
private:
    const std::string label;

public:
    GotoStmtTreeNode(const std::string label) : label(label) {}
};

//-----------------------------------------------
//id treenode

//用于表示变量，const变量额外做个标记，默认是false
//遇到声明列表时要分拆成一个个单独的变量
class VariableTreeNode : public IDTreeNode {
private:
    const std::string name;
    TypeTreeNode *type;
    bool isConst;

public:
    VariableTreeNode(const std::string name, TreeNode *type= nullptr, bool isConst = false)
            :name(name),type((TypeTreeNode *)type),isConst(isConst) {}

};

//字面值常量，需要指明值和类型，类型如char,int,double
class LiteralTreeNode:public IDTreeNode{
private:
    const std::string value;
    const std::string type;

public:
    LiteralTreeNode(const std::string value,const std::string type)
            :value(value),type(type){}
};

class ArrayElemTreeNode:public IDTreeNode{
private:
    const std::string name;//数组名
    ExprTreeNode *index;

public:
    ArrayElemTreeNode(const std::string name,TreeNode * expr)
            :name(name),index((ExprTreeNode *)expr){}
};

class RecordElemTreeNode:public IDTreeNode{
private:
    const std::string rname;//record的名字
    const std::string ename;//元素的名字

public:
    RecordElemTreeNode(const std::string n1,const std::string n2)
            :rname(n1),ename(n2){}
};


#endif //COMPILER_TREE_H
