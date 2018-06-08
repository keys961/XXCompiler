#ifndef COMPILER_CODEGEN_H
#define COMPILER_CODEGEN_H

#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <map>
#include <sstream>
#include "utils.h"

#define SP 29
#define FP 30
#define RA 31
#define A0 4
#define F12 44
#define V1 3
extern std::ofstream code;

class RegManager;

class LabelManager;

extern RegManager *regManager;
extern LabelManager *labelManager;
const std::string regTable[] = {
        "$zero",
        "$at",
        "$v0",
        "$v1",
        "$a0",
        "$a1",
        "$a2",
        "$a3",
        "$t0",
        "$t1",
        "$t2",
        "$t3",
        "$t4",
        "$t5",
        "$t6",
        "$t7",
        "$s0",
        "$s1",
        "$s2",
        "$s3",
        "$s4",
        "$s5",
        "$s6",
        "$s7",
        "$t8",
        "$t9",
        "",
        "",
        "$gp",
        "$sp",
        "$fp",
        "$ra",

        "$f0",
        "$f1",
        "$f2",
        "$f3",
        "$f4",
        "$f5",
        "$f6",
        "$f7",
        "$f8",
        "$f9",
        "$f10",
        "$f11",
        "$f12",
        "$f13",
        "$f14",
        "$f15",
        "$f16",
        "$f17",
        "$f18",
        "$f19",
        "$f20",
        "$f21",
        "$f22",
        "$f23",
        "$f24",
        "$f25",
        "$f26",
        "$f27",
        "$f28",
        "$f29",
        "$f30",
        "$f31",
};


class RegManager {
    static const int BEGIN_TMP = 8;
    static const int END_TMP = 23;
    static const int BEGIN_FLOAT = 32;
    static const int END_FLOAT = 63;
    int reg[32];
public:
    int getTmpReg(int isReal = 0) {
        if (isReal) {
            return getFloatReg();
        }
        for (int i = BEGIN_TMP; i <= END_TMP; i++) {
            if (reg[i] == 0) {
                reg[i] = 1;
                return i;
            }
        }
        std::cout << "reg is run out" << std::endl;
        return -1;
    }

    int getFloatReg() {
        for (int i = BEGIN_FLOAT; i <= END_FLOAT; i++) {
            if (reg[i] == 0) {
                reg[i] = 1;
                return i;
            }
        }
        std::cout << "reg is run out" << std::endl;
        return -1;
    }

    void useReg(int i) {
        if (i < 0 || i > 31) return;
        reg[i] = 1;
    }

    void freeReg(int i) {

        if (i < 0 || i > 63) return;
        std::cout << "free " << regTable[i] << std::endl;
        char c = regTable[i][1];
        reg[i] = 0;
    }


    void freeAll() {
        for (int i = BEGIN_TMP; i < END_TMP; i++) {
            reg[i] = 0;
        }
    }

};

class LabelManager {
    static int loopNumber;
    static int switchNumber;
    static int caseNumber;
    static int ifNumber;
    static int doNumber;
    static int realLabelNumber;
public:

    int getLoopLabel() { return loopNumber; }

    void addLoopLabel() { loopNumber++; }

    int getRepeatLabel() { return doNumber; }

    void addRepeatLabel() { doNumber++; }

    int getIfLabel() { return ifNumber; }

    void addIfLabel() { ifNumber++; }

    int getCaseLabel() { return caseNumber; }

    void addCaseLabel() { caseNumber++; }

    int getSwitchLabel() { return switchNumber; };

    void addSwitchLabel() { switchNumber++; };

    std::string getRealLabel() {
        char ch[32] = {0,};
        sprintf(ch, "real%d", realLabelNumber++);
        return ch;
    }


};

class CodeGenerator {
private:
    static int equal;

public:
    /**
     * R型指令
     *
     * @param op 操作符
     * @param dst 目的寄存器
     * @param src_1 源寄存器1
     * @param src_2 源寄存器2
     * @param isReal 是否是浮点数，默认为否
     */
    static void
    genRType(const std::string &op, int dst, int src_1, int src_2, int isReal = 0) {
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

    /**
     * I型指令
     *
     * @param op 操作符
     * @param dst 目的寄存器
     * @param src 源寄存器
     * @param imm 立即数
     * @param label 标签，只用于beq、bne，默认为空
     */
    static void genIType(const std::string &op, int dst, int src, int imm, const std::string &label = "") {
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

    /**
     * J型指令
     *
     * @param op 操作符，j或jal
     * @param label 要跳转的标签
     */
    static void genJType(const std::string &op, const std::string &label) {
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

    /**
     * 标签生成
     *
     * @param label 标签
     */
    static void genLabel(const std::string &label) {
        code << label << ":" << std::endl;
    }

    /**
     *
     * @param op 操作符
     * @param offset 偏移量
     * @param regAddr 源寄存器
     * @param reg 目的寄存器
     * @param isReal 是否是浮点数
     */
    static void genLoadOrStore(const std::string &op, int offset, int reg1, int reg2, int isReal = 0) {
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

    /**
     * 生成字符字面量
     * @param str 要生成的字符
     * @param label 对应的标签
     */
    static void genAsciiz(const std::string &str, const std::string &label) {
        code << label << ": .asciiz " << "\"" << str.substr(1, str.length() - 2) << "\"" << std::endl;
    }

    static void genFloat(const std::string &real, const std::string &label) {
        code << label << ": .float " << " " << real << std::endl;
    }

    static void genLa(int dst, const std::string &label) {
        code << "la " << regTable[dst] << " " << label << std::endl;
    }

    static void genSysCall(const std::string &type) {
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

};

void autoFreeReg(int beFree, int *contrain);

bool isTmpReg(int r);

#endif //COMPILER_CODEGEN_H
