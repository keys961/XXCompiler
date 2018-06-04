//
// Created by 王泽杰 on 2018/5/30.
//

#ifndef COMPILER_OPMAP_H
#define COMPILER_OPMAP_H

#include <map>
#include "symbol.h"
#include "codegen.h"

extern RegManager *regManager;
enum option{ASSIGN, PLUS, SUB, MUL, DIV, REM, AND, OR, GE, GRATER, LE, LESS, EQUAL, NE, XOR, BEQ, BNE, J, JR, JAL};
std::map<std::string, enum option> opMap;

void Initialize() {
    opMap["="] = ASSIGN;
    opMap["+"] = PLUS;
    opMap["-"] = SUB;
    opMap["*"] = MUL;
    opMap["/"] = DIV;
    opMap["%"] = REM;
    opMap["&&"] = AND;
    opMap["||"] = OR;
    opMap[">="] = GE;
    opMap[">"] = GRATER;
    opMap["<="] = LE;
    opMap["<"] = LESS;
    opMap["=="] = EQUAL;
    opMap["!="] = NE;
    opMap["~"] = XOR;
    opMap["beq"] = BEQ;
    opMap["bne"] = BNE;
    opMap["j"] = J;
    opMap["jr"] = JR;
    opMap["jal"] = JAL;
}

int isFloatType(SymbolBucket* b, int reg) {
    if ( (b != NULL && b->getSymbol().getTypeName() == "float") || reg > 31)
        return 1;
    else return 0;
}

void autoFreeReg(int beFree, int* contrain) {
    if (isTmpReg(beFree)) {
        if (contrain != NULL && *contrain != beFree) {
            regManager->freeReg(beFree);
        }
    }
}

int getSize(const string &type) {
    int size;
    if (type == "integer")
        size = 4;
    else if (type == "real")
        size = 4;
    else if (type == "char")
        size = 1;
    else if (type == "string")
        size = 4;
    return size;
}

#endif //COMPILER_OPMAP_H
