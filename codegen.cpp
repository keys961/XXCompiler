//
// Created by yejt on 18-4-30.
//
#include "codegen.h"

void autoFreeReg(int beFree, int *contrain) {
    if (isTmpReg(beFree)) {
        if (contrain != NULL && *contrain != beFree) {
            regManager->freeReg(beFree);
        }
    }
}

bool isTmpReg(int r) {
    return r >= 8 && r <= 15;
}

void CodeGenerator::genRType(const std::string &op, int dst, int src_1, int src_2, int isReal) {
    std::string c;
    std::string temp = " " + regTable[dst] + "," + regTable[src_1] + "," + regTable[src_2];
    std::string temp2 = " " + regTable[dst] + "," + regTable[src_2] + "," + regTable[src_1];
    enum myOption opEnum = opMap[op];
    std::stringstream ss;
    ss << "equal" << equal;
    std::string s = ss.str();
    switch (opEnum) {
        case PLUS1:
        case ASSIGN1:
            if (!isReal) {
                c = "add" + temp;
            } else {
                c = "add.s" + temp;
            }
            break;
        case SUB1:
            if (!isReal) {
                c = "sub" + temp;
            } else {
                c = "sub.s" + temp;
            }
            break;
        case MUL1:
            if (!isReal) {
                c = "mul" + temp;
            } else {
                c = "mul.s" + temp;
            }
            break;
        case DIV1:
            if (!isReal) {
                c = "div" + temp;
            } else {
                c = "div.s" + temp;
            }
            break;
        case REM1:
            c = "rem" + temp;
            break;
        case AND1:
            c = "and" + temp;
            break;
        case OR1:
            c = "or" + temp;
            break;
        case GE1:
            c = "slt" + temp + "\n";
            c = c + "xori " + regTable[dst] + "," + regTable[dst] + "," + "1";
            break;
        case GRATER1:
            c = "slt" + temp2;
            break;
        case LE1:
            c = "slt" + temp2 + "\n";
            c = c + "xori " + regTable[dst] + "," + regTable[dst] + "," + "1";
            break;
        case LESS1:
            c = "slt" + temp;
            break;
        case EQUAL1:
            c = "add " + regTable[dst] + "," + regTable[0] + "," + regTable[0] + "\n";
            c = c + "beq " + regTable[src_1] + "," + regTable[src_2] + "," + s + "\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + "," + "-1" + "\n";
            c = c + s + ":\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + ",1";
            equal++;
            break;
        case NE1:
            c = "add " + regTable[dst] + "," + regTable[0] + "," + regTable[0] + "\n";
            c = c + "bne " + regTable[src_1] + "," + regTable[src_2] + "," + s + "\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + "," + "-1" + "\n";
            c = c + s + ":\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + ",1";
            equal++;
            break;
        case XOR1:
            c = "xori " + regTable[dst] + ", " + regTable[src_2] + ", -1";
            break;
        case JR1:
            c = "jr " + regTable[dst];
    }
    code << c << std::endl;
}

void CodeGenerator::genIType(const std::string &op, int dst, int src, int imm, const std::string &label) {
    char ch[16] = {0,};
    sprintf(ch, "%d", imm);
    std::string c;
    std::string temp = " " + regTable[dst] + "," + regTable[src] + ",";
    enum myOption option1 = opMap[op];
    int tmp = regManager->getTmpReg();
    std::stringstream ss;
    ss << "equal" << equal;
    std::string s = ss.str();
    switch (option1) {
        case PLUS1:
        case ASSIGN1:
            c = "addi" + temp + ch;
            break;
        case SUB1:
            c = "addi" + temp + "-" + ch;
            break;
        case MUL1:
            c = "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "mul" + temp + regTable[tmp];
            break;
        case DIV1:
            c = "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "div" + temp + regTable[tmp];
            break;
        case REM1:
            c = "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "rem " + temp + regTable[tmp];
            break;
        case AND1:
            c = "andi" + temp + ch;
            break;
        case OR1:
            c = "ori" + temp + ch;
            break;
        case GE1:
            c = "slti " + regTable[dst] + "," + regTable[src] + "," + ch + "\n";
            c = c + "xori " + regTable[dst] + "," + regTable[dst] + "," + "1";
            break;
        case GRATER1:
            c = "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "slt " + regTable[dst] + "," + regTable[tmp] + "," + regTable[src];
            break;
        case LE1:
            c = "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "slt " + regTable[tmp] + "," + regTable[tmp] + "," + regTable[src] + "\n";
            c = c + "xori " + regTable[dst] + "," + regTable[tmp] + "," + "1";
            break;
        case LESS1:
            c = "slti" + temp + ch;
            break;
        case EQUAL1:
            c = "add " + regTable[dst] + "," + regTable[0] + "," + regTable[0] + "\n";
            c = c + "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "beq " + regTable[src] + "," + regTable[tmp] + "," + s + "\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + "," + "-1" + "\n";
            c = c + s + ":\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + ",1";
            equal++;
            break;
        case NE1:
            c = "add " + regTable[dst] + "," + regTable[0] + "," + regTable[0] + "\n";
            c = c + "addi " + regTable[tmp] + "," + regTable[0] + "," + ch + "\n";
            c = c + "bne " + regTable[src] + "," + regTable[tmp] + "," + s + "\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + "," + "-1" + "\n";
            c = c + s + ":\n";
            c = c + "addi " + regTable[dst] + "," + regTable[dst] + ",1";
            equal++;
            regManager->freeReg(tmp);
            break;
        case BEQ1: {
            c = "beq" + temp + label;
            break;
        }
        case BNE1: {
            c = "bne" + temp + label;
            break;
        }
    }
    regManager->freeReg(tmp);
    code << c << std::endl;
}

void CodeGenerator::genJType(const std::string &op, const std::string &label) {
    std::string c;
    enum myOption option1 = opMap[op];
    switch (option1) {
        case J1:
            c = op + " " + label;
            break;
        case JAL1:
            c = op + " " + label;
            break;
    }
    code << c << std::endl;
}

void CodeGenerator::genLoadOrStore(const std::string &op, int offset, int reg1, int reg2, int isReal) {
    std::string c;
    char ch[16] = {0,};
    std::string option;
    const std::string &localOP = op;
    if (op == "load") {
        if (!isReal)
            option = "lw";
        else option = "l.s";
    } else {
        if (!isReal)
            option = "sw";
        else
            option = "s.s";
    }
    sprintf(ch, "%d", offset);
    c = option + " " + regTable[reg2] + ", " + ch + "(" + regTable[reg1] + ")";
    code << c << std::endl;
}

void CodeGenerator::genSysCall(const std::string &type) {
    if (type == "printString") {
        code << "addi $v0, $zero, 4" << std::endl;
    } else if (type == "printInteger") {
        code << "addi $v0, $zero, 1" << std::endl;
    } else if (type == "printReal") {
        code << "addi $v0, $zero, 2" << std::endl;
    } else if (type == "printChar") {
        code << "li $v0, 4" << std::endl;
    }
    code << "syscall" << std::endl;
}
