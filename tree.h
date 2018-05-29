#ifndef COMPILER_TREE_H
#define COMPILER_TREE_H

#include <string>
#include <vector>
#include <fstream>
#include "symbol.h"

extern std::ofstream astOut;

class CommonTypeTreeNode;

class TreeNode {
private:
    std::string name;
    int lineNum;

protected:
    long addr;
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " TreeNode" << std::endl;
        if (!children.empty()) {
            astOut << "\tChildren ID: ";
            for (auto &it : children)
                astOut << it << " ";
            astOut << std::endl;
        }
        // Recursively print
        for(auto& it : children)
            it->printSelf();
    }

};

class StatementTreeNode : public TreeNode {

protected:
    int label;

public:
    virtual ~StatementTreeNode() {}

    void setLabel(int label) { this->label = label; }

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " StatementTreeNode" << std::endl;
        astOut << "\tlabel: " << label << std::endl;
    }

};

class ExprTreeNode : public TreeNode {

public:
    virtual ~ExprTreeNode() { }

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ExprTreeNode" << std::endl;
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ListTreeNode" << std::endl;
        astOut << "\ttype: " << type << std::endl;
        if(!list.empty()) {
            astOut << "\t items: ";
            for(auto &it : list)
                astOut << it << " ";
            astOut << std::endl;
        }

        for(auto& it : list)
            it->printSelf();
    }

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

    virtual void printSelf();
};

class IDTreeNode : public TreeNode {
public:
    virtual ~IDTreeNode() {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " IDTreeNode" << std::endl;
    }

    virtual const std::string getType() {
        return "default";
    }
};

class ProgramHeadTreeNode : public TreeNode {
private:
    const std::string name;
public:
    ProgramHeadTreeNode(const std::string name) : name(name) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ProgramHeadTreeNode" << std::endl;
        astOut << "\tname: " << name << std::endl;
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ProgramTreeNode" << std::endl;
        astOut << "\tname: " << this->getName() << std::endl;
        astOut << "\tconst_part: " << const_decl << std::endl;
        astOut << "\ttype_part: " << type_decl << std::endl;
        astOut << "\tvar_part: " << var_decl << std:: endl;
        astOut << "\tfunction_procedure_part: " << routine_decl << std::endl;
        astOut << "\tbody_part: " << body << std::endl;

        const_decl->printSelf();
        type_decl->printSelf();
        var_decl->printSelf();
        routine_decl->printSelf();
        body->printSelf();
    }
};

class TypeTreeNode : public TreeNode {
public:
    virtual ~TypeTreeNode() {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " TypeTreeNode" << std::endl;
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " BinaryExprTreeNode" << std::endl;
        astOut << "\toperator: " << op << std::endl;
        astOut << "\tleft operand: " << loprand << std::endl;
        astOut << "\tright operand: " << roprand << std::endl;
        loprand->printSelf();
        roprand->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " UnaryExprTreeNode" << std::endl;
        astOut << "\toperator: " << op << std::endl;
        astOut << "\toperand: " << oprand << std::endl;
        oprand->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " CallExprTreeNode" << std::endl;
        astOut << "\tname: " << name << "; isFunc: " << isFunc <<std::endl;
        if(args && !args->empty()) {
            astOut << "\targ nodes: ";
            for (auto &it : *args)
                astOut << it << " ";
            astOut << std::endl;

            for(auto& it : *args)
                it->printSelf();
        }

    }
};

class CaseExprTreeNode : public ExprTreeNode {
private:
    IDTreeNode *label;//case后跟的值
    StatementTreeNode *body;//冒号后的条件句

public:
    CaseExprTreeNode(IDTreeNode *label, StatementTreeNode *body)
            : label(label), body(body) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " CaseExprTreeNode" << std::endl;
        astOut << "\tlabel node: " << label << std::endl;
        astOut << "\tstatement node: " << body <<std::endl;
    }
};

//--------------------------------------------
//type treenode

//系统自带简单类型
class CommonTypeTreeNode : public TypeTreeNode {
private:
    const std::string type;//string int char double
public:
    CommonTypeTreeNode(const std::string type) : type(type) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " CommonTypeTreeNode" << std::endl;
        astOut << "\ttype: " << type << std::endl;
    }
};

class RangeTypeTreeNode : public TypeTreeNode {
private:
    IDTreeNode *upper;
    IDTreeNode *lower;

public:
    RangeTypeTreeNode(IDTreeNode *upper, IDTreeNode *lower) : upper(upper), lower(lower) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " RangeTypeTreeNode" << std::endl;
        astOut << "\tupper node: " << upper << std::endl;
        astOut << "\tlower node: " << lower << std::endl;

        upper->printSelf();
        lower->printSelf();
    }
};

class ArrayTypeTreeNode : public TypeTreeNode {
private:
    RangeTypeTreeNode *index;//数组下标范围
    CommonTypeTreeNode *elem;//数组元素类型

public:
    ArrayTypeTreeNode(RangeTypeTreeNode *index, CommonTypeTreeNode *elem)
            : index(index), elem(elem) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ArrayTypeTreeNode" << std::endl;
        astOut << "\trange node: " << index << std::endl;
        astOut << "\ttype node: " << elem << std::endl;

        index->printSelf();
        elem->printSelf();
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " RecordTypeTreeNode" << std::endl;
        if(!elems.empty()) {
            astOut << "\trecord element nodes: ";
            for(auto& it : elems)
                astOut << it << " ";
            astOut << std::endl;

            for(auto& it : elems)
                it->printSelf();
        }
    }

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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " EnumTypeTreeNode" << std::endl;
        astOut << "\tname: " << name << "; enums node: " << elems << std::endl;

        elems->printSelf();
    }
};

//用户自定义类型
class CustomTypeTreeNode : public TypeTreeNode {
private:
    const std::string name;
    TypeTreeNode *type;
public:
    CustomTypeTreeNode(const std::string name, TreeNode *type)
            : name(name), type((TypeTreeNode *) type) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " CustomTypeTreeNode" << std::endl;
        astOut << "\tname: " << name << "; type node: " << type << std::endl;
        if(type)
            type->printSelf();
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " CompoundStmtTreeNode" << std::endl;
        astOut << "\tstatements node: " << stmtlist << std::endl;

        stmtlist->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " IfStmtTreeNode" << std::endl;
        astOut << "\tcondition node: " << condition << std::endl;
        astOut << "\tthen node: " << then_stmt << std::endl;
        astOut << "\telse node: " << else_stmt << std::endl;

        condition->printSelf();
        then_stmt->printSelf();
        if(else_stmt)
            else_stmt->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " RepeatStmtTreeNode" << std::endl;
        astOut << "\tcondition node: " << condition << std::endl;
        astOut << "\tstatement node: " << body << std::endl;

        condition->printSelf();
        body->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " WhileStmtTreeNode" << std::endl;
        astOut << "\tcondition node: " << condition << std::endl;
        astOut << "\tstatement node: " << body << std::endl;

        condition->printSelf();
        body->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " SwitchStmtTreeNode" << std::endl;
        astOut << "\texpression node: " << expr << std::endl;
        astOut << "\tcase list node: " << case_list << std::endl;

        expr->printSelf();
        case_list->printSelf();
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ForStmtTreeNode" << std::endl;
        astOut << "\tdirection: " << direction << std::endl;
        astOut << "\tsrc node: " << src << "; dst node: " << dst << std::endl;
        astOut << "\tbody node: " << body << std::endl;
        src->printSelf();
        dst->printSelf();
        body->printSelf();
    }
};

class GotoStmtTreeNode : public StatementTreeNode {
private:
    const std::string label;

public:
    GotoStmtTreeNode(const std::string label) : label(label) {}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " GotoStmtTreeNode" << std::endl;
        astOut << "\tlabel: " << label << std::endl;
    }
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

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " VariableTreeNode" << std::endl;
        astOut << "\tname: " << name << "; isConst: " << isConst << std::endl;
        astOut << "\ttype node: " << type << std::endl;
        if(type)
            type->printSelf();
    }
};

//字面值常量，需要指明值和类型，类型如char,int,double
class LiteralTreeNode:public IDTreeNode{
private:
    const std::string value;
    const std::string type;

public:
    LiteralTreeNode(const std::string value,const std::string type)
            :value(value),type(type){}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " LiteralTreeNode" << std::endl;
        astOut << "\tvalue: " << value << "; type: " << type << std::endl;
    }
};

class ArrayElemTreeNode:public IDTreeNode{
private:
    const std::string name;//数组名
    ExprTreeNode *index;

public:
    ArrayElemTreeNode(const std::string name,TreeNode * expr)
            :name(name),index((ExprTreeNode *)expr){}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " ArrayElemTreeNode" << std::endl;
        astOut << "\tname: " << name << std::endl;
        astOut << "\tindex node: " << index << std::endl;
        index->printSelf();
    }
};

class RecordElemTreeNode:public IDTreeNode{
private:
    const std::string rname;//record的名字
    const std::string ename;//元素的名字

public:
    RecordElemTreeNode(const std::string n1,const std::string n2)
            :rname(n1),ename(n2){}

    virtual void printSelf() {
        astOut << "Node ID " << std::hex << addr << ":" << " RecordElemTreeNode" << std::endl;
        astOut << "\trecord name: " << rname << "; element name: " << ename << std::endl;
    }
};

#endif //COMPILER_TREE_H
