#ifndef COMPILER_CODEGEN_H
#define COMPILER_CODEGEN_H

#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdio>
#include <map>
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
    int getTmpReg(int isFloat = 0) {
        if (isFloat) {
            return getFloatReg();
        }
        for (int i = BEGIN_TMP; i <= END_TMP; i++) {
            if (reg[i] == 0) {
                reg[i] = 1;
                std::cout << "use reg " << regTable[i] << std::endl;
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
                std::cout << "use reg " << regTable[i] << std::endl;
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
    static int loop_number;
    static int func_number;
    static int case_number;
    static int goto_number;
    static int if_number;
    static int do_number;
    static int string_label_number;
    static int real_label_number;
    static int equal_number;
public:

    int getLoopLabel() { return loop_number; }

    void addLoopLabel() { loop_number++; }

    int getRepeatLabel() { return do_number; }

    void addRepeatLabel() { do_number++; }

    int getEqualLabel() { return equal_number; }

    void addEqualLabel() { equal_number++; }

    int getIfLabel() { return if_number; }

    void addIfLabel() { if_number++; }

    int getgotoLabel() { return goto_number; }

    void addgotoLabel() { goto_number++; }

    int getCaseLabel() { return case_number; }

    void addCaseLabel() { case_number++; }

    int getFuncLabel() { return func_number; }

    void addFuncLabel(std::string &label) {
        char labelNum[10] = {0,};
        sprintf(labelNum, "%d", func_number++);
        label = label + labelNum;
    }

    std::string getStringLabel() {
        char ch[32] = {0,};
        sprintf(ch, "string%d", string_label_number++);
        return ch;
    }

    std::string getRealLabel() {
        char ch[32] = {0,};
        sprintf(ch, "real%d", real_label_number++);
        return ch;
    }


};

class CodeGenerator {
private:
    static int equal;

public:
    static std::string intTostring(int x) {
        char t[256];
        std::string s;

        sprintf(t, "%d", x);
        s = t;
        return s;
    }

    /**
     * R型指令
     *
     * @param op 操作符
     * @param dst 目的寄存器
     * @param src_1 源寄存器1
     * @param src_2 源寄存器2
     * @param isFloat 是否是浮点数，默认为否
     */
    static void
    genRType(const std::string op, int dst, int src_1, int src_2, int isFloat = 0) {
        std::cout << "emit R : " << op << " " << dst << " " << src_1 << " " << src_2 << std::endl;
        std::string c;
        std::string temp = " " + regTable[dst] + "," + regTable[src_1] + "," + regTable[src_2];
        std::string temp2 = " " + regTable[dst] + "," + regTable[src_2] + "," + regTable[src_1];
        enum myOption opEnum = opMap[op];
        std::string s = "equal" + intTostring(equal);
        switch (opEnum) {
            case PLUS1:
            case ASSIGN1:
                if (!isFloat) {
                    c = "add" + temp;
                } else {
                    c = "add.s" + temp;
                }
                break;
            case SUB1:
                if (!isFloat) {
                    c = "sub" + temp;
                } else {
                    c = "sub.s" + temp;
                }
                break;
            case MUL1:
                if (!isFloat) {
                    c = "mul" + temp;
                } else {
                    c = "mul.s" + temp;
                }
                break;
            case DIV1:
                if (!isFloat) {
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
    static void genIType(const std::string op, int dst, int src, int imm, const std::string label = "") {
        std::cout << "emit I op = " << op << " dst = " << dst << " src = " << src << std::endl;
        char ch[16] = {0,};
        sprintf(ch, "%d", imm);
        std::string c;
        std::string temp = " " + regTable[dst] + "," + regTable[src] + ",";
        enum myOption option1 = opMap[op];
        int tmp = regManager->getTmpReg();
        std::string s = "equal" + intTostring(equal);
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
                c = "beq" + temp + label;
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
    static void genJType(const std::string op, const std::string label) {
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

    static void addLabel(const std::string label) {
        code << label << ":" << std::endl;
    }

//    /**
//     * 寻找最顶层的帧指针
//     *
//     * @param op 操作符
//     * @param localOP “-”前面的原始操作符
//     * @param tmpAC 找到的帧指针
//     */
//    static void findFP(string op, string &localOP, int &tmpAC) {
//        if (op.find("-") != string::npos) {
//            tmpAC = regManager->getTmpReg();
//            int pos = op.find('-');
//            int level = atoi(op.substr(pos + 1, op.length()).c_str());
//            CodeGenerator::emitCodeM(4, "load", -4, FP, tmpAC);            //应为fp在ac上面，所有ac所在的地址高于当前fp的地址
//            //根据level的差值向上获取level - 1次ac，最后一次获取到的ac就是fp
//            //fp指向栈的最后一个位置，ac指向栈的第一个位置，因此fp - 4指向ac
//            for (int i = 1; i < level; i++) {
//                CodeGenerator::emitCodeM(4, "load", 0, tmpAC, tmpAC);
//            }
//            CodeGenerator::emitCodeI("+", tmpAC, tmpAC, -4);
//            localOP = op.substr(0, pos);
//        }
//    }

    /**
     *
     * @param op 操作符
     * @param offset 偏移量
     * @param regAddr 源寄存器
     * @param reg 目的寄存器
     * @param isFloat 是否是浮点数
     */
    static void emitCodeM(const std::string op, int offset, int regAddr, int reg, int isFloat = 0) {
        std::cout << "emit M " << "op = " << op << " offset = " << offset << std::endl;
        if (op.find("reg") != std::string::npos)
            offset = -offset;
        std::string c;
//        char loadInstr[][4] = {"", "lb", "lh", "", "lw"};
//        char storeInstr[][4] = {"", "sb", "sh", "", "sw"};
//        string ls = "l.s";
//        string ss = "s.s";
        char ch[16] = {0,};
        std::string instr;
        std::string localOP = op;
//        findFP(op, localOP, regAddr);
        if (localOP == "load" || localOP == "load_reg") {
            if (!isFloat)
                instr = "lw";
            else instr = "l.s";
        } else {
            if (!isFloat)
                instr = "sw";
            else
                instr = "s.s";
        }
        if (localOP == "load" || localOP == "store") {
            sprintf(ch, "%d", offset);
            c = instr + " " + regTable[reg] + ", " + ch + "(" + regTable[regAddr] + ")";
            code << c << std::endl;
        } else if (localOP == "load_reg" || localOP == "store_reg") {
            std::cout << offset << " " << regAddr << std::endl;
            ch[0] = '\0';
            sprintf(ch, "0");
            std::string c1 = "add " + regTable[offset] + ", " + regTable[offset] + ", " + regTable[regAddr];
            c = instr + " " + regTable[reg] + ", " + ch + "(" + regTable[offset] + ")";
            code << c1 << std::endl << c << std::endl;
        }
    }

//    static void
//    emitCodeB(const std::string loadOP, const std::string storeOP, int size, int dstOffset, int srcOffset, int addrReg,
//              int copysize) {
//        int loopTime = size / copysize;
//
//        std::string s = "copy";
//        labelManager->addLoopLabel();
//        int loopNum = labelManager->getLoopLabel();
//        char ch[8] = {0,};
//        sprintf(ch, "%d", loopNum);
//        s += ch;
//        int loop = regManager->getTmpReg();
//        int tmp = regManager->getTmpReg();
//        std::string localLoadOP = loadOP, localStoreOP = storeOP;
//        //int tmpAddr = regManager->getTmpReg();
//        int addrRegSrc = addrReg;
//        int addrRegDst = addrReg;
////        findFP(loadOP, localLoadOP, addrRegSrc);
////        findFP(storeOP, localStoreOP, addrRegDst);
//        if (addrRegSrc == addrReg) {
//            addrRegSrc = regManager->getTmpReg();
//            CodeGenerator::emitCodeR("+", addrRegSrc, addrReg, 0);
//        }
//        if (addrRegDst == addrReg) {
//            addrRegDst = regManager->getTmpReg();
//            CodeGenerator::emitCodeR("+", addrRegDst, addrReg, 0);
//        }
//        if (loadOP.find("reg") != string::npos) {
//            CodeGenerator::emitCodeR("+", addrRegSrc, addrRegSrc, srcOffset);
//        } else {
//            CodeGenerator::emitCodeI("+", addrRegSrc, addrRegSrc, -srcOffset);
//        }
//        if (storeOP.find("reg") != string::npos) {
//            CodeGenerator::emitCodeR("+", addrRegDst, addrRegDst, dstOffset);
//        } else {
//            CodeGenerator::emitCodeI("+", addrRegDst, addrRegDst, -dstOffset);
//        }
//        CodeGenerator::emitCodeR("+", loop, 0, 0);
//        CodeGenerator::addLabel(s);
//        CodeGenerator::emitCodeM(copysize, "load", 0, addrRegSrc, tmp);
//        CodeGenerator::emitCodeM(copysize, "store", 0, addrRegDst, tmp);
//        CodeGenerator::emitCodeI("+", addrRegSrc, addrRegSrc, -copysize);
//        CodeGenerator::emitCodeI("+", addrRegDst, addrRegDst, -copysize);
//        CodeGenerator::emitCodeI("+", loop, loop, 1);
//        int tmp2 = regManager->getTmpReg();
//        CodeGenerator::emitCodeI("<", tmp2, loop, loopTime);
//        CodeGenerator::emitCodeJ("bne", tmp2, 0, 0, s);
//        regManager->freeReg(addrRegSrc);
//        regManager->freeReg(addrRegDst);
//        regManager->freeReg(tmp);
//        regManager->freeReg(tmp2);
//        regManager->freeReg(loop);
//        cout << "yyyy" << endl;
//    }

    static void emitCodeConstStr(std::string constStr, std::string label) {
        code << label << ": .asciiz " << "\"" << constStr.substr(1, constStr.length() - 2) << "\"" << std::endl;
    }

    static void emitCodeConstReal(std::string constReal, std::string label) {
        code << label << ": .float " << " " << constReal << std::endl;
    }

    static void emitCodeLA(std::string label, int regDst) {
        code << "la " << regTable[regDst] << " " << label << std::endl;
    }

    static void emitSysCall(std::string type) {
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

//    static void emitGetAccessLink(int levelDiff) {
//        cout << "========== levelDiff = " << levelDiff << endl;
//        int tmpAC = regManager->getTmpReg();
//        if (levelDiff == 1) {
//            CodeGenerator::emitCodeI("+", tmpAC, FP, 4);
//        } else if (levelDiff <= 0) {
//            CodeGenerator::emitCodeM(4, "load", -4, FP, tmpAC);
//            for (int i = 0; i < -levelDiff; i++) {
//                CodeGenerator::emitCodeM(4, "load", 0, tmpAC, tmpAC);
//            }
//        } else if (levelDiff > 0) {
//            cout << "error : can not call inner function !!" << endl;
//        }
//        //SP - 4得到AC的位置（地址），然后把tmpAC代表的寄存器的值存到该地址处
//        CodeGenerator::emitCodeM(4, "store", -4, SP, tmpAC);
//        regManager->freeReg(tmpAC);
//    }
};

void autoFreeReg(int beFree, int *contrain);

bool isTmpReg(int r);

#endif //COMPILER_CODEGEN_H
