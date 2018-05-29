#include "tree.h"

void FuncOrProcTreeNode::printSelf() {
    astOut << "Node ID " << std::hex << addr << ":" << " FuncOrProcTreeNode" << std::endl;
    astOut << "\tname: " << name << "; isFunction: " << isFunc << std::endl;
    astOut << "\targs node: " << args << "; body node: " << body
           << "; return type node: " << return_type << std::endl;
    args->printSelf();
    body->printSelf();
    return_type->printSelf();
}
