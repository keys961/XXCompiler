//
// Created by yejt on 18-5-21.
//

#ifndef COMPILER_OPTIMIZER_H
#define COMPILER_OPTIMIZER_H

#include "tree.h"

class TreeOptimizer
{
private:
    TreeNode* root;
    TreeNode* optimizeExpression();
    TreeNode* optimizeStatement();
public:
    TreeOptimizer(TreeNode* root): root(root) {}
    TreeNode* getOptimizedTree();
};

#endif //COMPILER_OPTIMIZER_H
