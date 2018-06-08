//
// Created by 王泽杰 on 2018/6/6.
//
#include "utils.h"

void Initialize() {
    opMap["="] = ASSIGN1;
    opMap["+"] = PLUS1;
    opMap["-"] = SUB1;
    opMap["*"] = MUL1;
    opMap["/"] = DIV1;
    opMap["%"] = REM1;
    opMap["&&"] = AND1;
    opMap["||"] = OR1;
    opMap[">="] = GE1;
    opMap[">"] = GRATER1;
    opMap["<="] = LE1;
    opMap["<"] = LESS1;
    opMap["=="] = EQUAL1;
    opMap["!="] = NE1;
    opMap["~"] = XOR1;
    opMap["beq"] = BEQ1;
    opMap["bne"] = BNE1;
    opMap["j"] = J1;
    opMap["jr"] = JR1;
    opMap["jal"] = JAL1;
}

int isRealType(SymbolBucket* b, int reg) {
    if ( (b != nullptr && b->getSymbol()->getTypeName() == "real") || reg > 31)
        return 1;
    else return 0;
}

int getSize(const std::string &type) {
    int size;
    if (type == "integer")
        size = 4;
    else if (type == "real")
        size = 4;
    else if (type == "char")
        size = 4;
    return size;
}

//utils 函数
int getSizeByType(std::string type) {
    if (type == "integer") {
        return 4;
    } else if (type == "char") {
        return 4;
    } else if (type == "real") {
        return 4;
    }
    return -1;
}