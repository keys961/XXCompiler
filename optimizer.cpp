//
// Created by yejt on 18-5-21.
//

#include "optimizer.h"

TreeNode *TreeOptimizer::optimizeExpression()
{
    return nullptr;
}

TreeNode *TreeOptimizer::optimizeStatement()
{
    return nullptr;
}

TreeNode *TreeOptimizer::getOptimizedTree()
{
    this->root = optimizeExpression();
    this->root = optimizeStatement();

    return this->root;
}
