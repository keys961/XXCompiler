#include "tree.h"

void FuncOrProcTreeNode::printSelf() {
    if(printedNodes.find(this) != printedNodes.end()) {
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
