//
// Created by 王泽杰 on 2018/5/30.
//

#ifndef COMPILER_OPMAP_H
#define COMPILER_OPMAP_H

#include <map>
#include "symbol.h"

//extern RegManager *regManager;
enum myOption{ASSIGN1, PLUS1, SUB1, MUL1, DIV1, REM1, AND1, OR1, GE1, GRATER1, LE1, LESS1, EQUAL1, NE1, XOR1, BEQ1, BNE1, J1, JR1, JAL1};
extern std::map<std::string, enum myOption> opMap;

void Initialize();

int isFloatType(SymbolBucket* b, int reg);

int getSize(const std::string &type);

#endif //COMPILER_OPMAP_H
