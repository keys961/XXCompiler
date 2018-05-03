#ifndef COMPILER_TREE_H
#define COMPILER_TREE_H

#include <string>
#include <vector>
#include "symbol.h"

class TreeNode
{
private:
    std::string name;
    int lineNum;
protected:
    SymbolTable* environment;
    std::vector<TreeNode*> children;
public:
    TreeNode() {}

    const std::string &getName() const
    {
        return name;
    }

    void setName(const std::string &name)
    {
        this->name = name;
    }

    int getLineNum() const
    {
        return lineNum;
    }

    void setLineNum(int lineNum)
    {
        this->lineNum = lineNum;
    }

    SymbolTable *getEnvironment() const
    {
        return environment;
    }

    void setEnvironment(SymbolTable *environment)
    {
        this->environment = environment;
    }

    virtual void updateEnvironment(SymbolTable* environment) {}

    virtual SymbolBucket* generateCode(SymbolTable* environment) { return NULL; }

    virtual std::string typeCheck(SymbolTable* environment) { return "type check"; }


};

#endif //COMPILER_TREE_H
