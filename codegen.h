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
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5","$t6", "$t7",
        "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "", "", "$gp", "$sp", "$fp", "$ra",
        "$f0", "$f1", "$f2", "$f3", "$f4", "$f5", "$f6", "$f7",
        "$f8", "$f9", "$f10", "$f11", "$f12", "$f13", "$f14", "$f15",
        "$f16", "$f17", "$f18", "$f19", "$f20", "$f21", "$f22", "$f23",
        "$f24", "$f25", "$f26", "$f27", "$f28", "$f29", "$f30", "$f31",
};

class RegManager {
private:
    int reg[32];
public:
    int getTmpReg(int isReal = 0) {
        if (isReal) {
            return getFloatReg();
        }
        for (int i = 8; i <= 23; i++) {
            if (reg[i] == 0) {
                reg[i] = 1;
                return i;
            }
        }
        return -1;
    }

    int getFloatReg() {
        for (int i = 32; i <= 63; i++) {
            if (reg[i] == 0) {
                reg[i] = 1;
                return i;
            }
        }
        return -1;
    }

    void freeReg(int i) {

        if (i < 0 || i > 63)
            return;
        char c = regTable[i][1];
        reg[i] = 0;
    }

    void autoFreeReg(int beFree, const int *contrain) {
        if (this->isTmpReg(beFree)) {
            if (contrain != nullptr && *contrain != beFree) {
                regManager->freeReg(beFree);
            }
        }
    }

    bool isTmpReg(int r) {
        return r >= 8 && r <= 15;
    }

};

class LabelManager {
private:
    int loopNumber;
    int switchNumber;
    int caseNumber;
    int ifNumber;
    int doNumber;
    int realLabelNumber;
    std::map<std::string, std::string> constCharMap;
    std::map<std::string, std::string> constRealMap;
public:

    LabelManager() : loopNumber(0), switchNumber(0), caseNumber(0), ifNumber(0), doNumber(0), realLabelNumber(0)
    {
        constCharMap = std::map<std::string, std::string>();
        constRealMap = std::map<std::string, std::string>();
    }

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
        char ch[64] = {0, };
        sprintf(ch, "real%d", realLabelNumber++);
        return std::string(ch);
    }

    const std::map<std::string, std::string> &getConstCharMap() const {
        return constCharMap;
    }

    const std::map<std::string, std::string> &getConstRealMap() const {
        return constRealMap;
    }

    void insertIntoCharMap(const std::string &key, std::string value) {
        constCharMap[key] = value;
    }

    void insertIntoRealMap(const std::string &key, std::string value) {
        constRealMap[key] = value;
    }
};

class CodeGenerator {
private:
    int equal;

public:
    CodeGenerator() : equal(0) { }
    /**
     * R型指令
     *
     * @param op 操作符
     * @param dst 目的寄存器
     * @param src_1 源寄存器1
     * @param src_2 源寄存器2
     * @param isReal 是否是浮点数，默认为否
     */
    void genRType(const std::string &op, int dst, int src_1, int src_2, int isReal = 0);

    /**
     * I型指令
     *
     * @param op 操作符
     * @param dst 目的寄存器
     * @param src 源寄存器
     * @param imm 立即数
     * @param label 标签，只用于beq、bne，默认为空
     */
    void genIType(const std::string &op, int dst, int src, int imm, const std::string &label = "");

    /**
     * J型指令
     *
     * @param op 操作符，j或jal
     * @param label 要跳转的标签
     */
    void genJType(const std::string &op, const std::string &label);

    /**
     * 标签生成
     *
     * @param label 标签
     */
    void genLabel(const std::string &label) {
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
    void genLoadOrStore(const std::string &op, int offset, int reg1, int reg2, int isReal = 0);

    /**
     * 生成字符字面量
     * @param str 要生成的字符
     * @param label 对应的标签
     */
    void genAsciiz(const std::string &str, const std::string &label) {
        code << label << ": .asciiz " << "\"" << str.substr(1, str.length() - 2) << "\"" << std::endl;
    }

    void genFloat(const std::string &real, const std::string &label) {
        code << label << ": .float " << " " << real << std::endl;
    }

    void genLa(int dst, const std::string &label) {
        code << "la " << regTable[dst] << " " << label << std::endl;
    }

    void genSysCall(const std::string &type);

};

#endif //COMPILER_CODEGEN_H
