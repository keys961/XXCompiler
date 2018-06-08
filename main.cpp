#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include "comment.h"
#include "lexer.h"
#include "parser.hpp"
#include "tree.h"
#include "optimizer.h"
#include "codegen.h"

std::map<std::string, std::string> constCharMap;
std::map<std::string, std::string> constRealMap;
std::map<std::string, enum myOption> opMap;

/**
 * Global variables
 */
FILE *codeIn; // Code input
std::ofstream preProcessOut; // Code output after pre-processing
FILE *lexerOut; // Lexer analysis output
std::ofstream grammarOut; // Grammar output
std::ofstream astOut; // AST output
std::ofstream codeOut; // Target code output
std::ofstream symOut; // symbol output
std::ofstream checkOut; // type check output
std::ofstream code; // codegen output
bool isPrint = false;//默认不打印日志
RegManager *regManager;
LabelManager *labelManager;

GlobalInfo globalInfo;
TreeNode *root; // ProgramBodyTreeNode

std::set<TreeNode *> printedNodes;

int LabelManager::loopNumber = 0;
int LabelManager::funcNumber = 0;
int LabelManager::caseNumber = 0;
int LabelManager::ifNumber = 0;
int LabelManager::doNumber = 0;
int LabelManager::stringLabelNumber = 0;
int LabelManager::realLabelNumber = 0;
int LabelManager::switchNumber = 0;
int CodeGenerator::equal = 0;

int main(int argc, const char *argv[]) {
    /* Format: compiler src_file_name output_file_name */
    if (argc != 3) {
        std::cerr << "Wrong input format!" << std::endl;
        std::cout << "\t compiler $src_file_name $output_file_name" << std::endl;
        return 1;
    }
    // Prepare
    std::string fileName = argv[1];
    std::string preProcessFileName = fileName + ".pre";
    std::string lexerFileName = fileName + ".lexer";
    std::string grammarFileName = fileName + ".grammar";
    std::string astFileName = fileName + ".ast";
    std::string codeFileName = fileName + ".s";
    std::string symFileName = fileName + ".sym";
    std::string chkFileName = fileName + ".chk";
    std::string asmFileName = fileName + ".asm";
    regManager = new RegManager();
    labelManager = new LabelManager();
    Initialize();
    // Pre-processing
    CommemtProcessor processor;
    std::fstream fin(argv[1], std::ios::in);
    preProcessOut = std::ofstream(preProcessFileName, std::ios::out);
    if (!fin.bad() && !preProcessOut.bad()) {
        std::cout << "Pre-processing code with " << fileName << "..." << std::endl;
        processor.processComment(fin, preProcessOut);
        preProcessOut.flush();
        fin.close();
        preProcessOut.close();
        std::cout << "End pre-processing." << std::endl;
    } else {
        std::cerr << "Error when pre-processing code with "
                  << fileName << "!" << std::endl;
        if (!fin.bad())
            fin.close();
        if (!preProcessOut.bad())
            preProcessOut.close();
        return 1;
    }
    // Lexical & Grammar analysis
    codeIn = fopen(preProcessFileName.c_str(), "r");
    lexerOut = fopen(lexerFileName.c_str(), "w+");
    grammarOut = std::ofstream(grammarFileName, std::ios::out);
    if (codeIn && lexerOut && !grammarOut.bad()) {
        std::cout << "Parsing code with " << fileName << "..." << std::endl;
        yyparse();
        fclose(codeIn);
        fclose(lexerOut);
        grammarOut.close();
        std::cout << "End of parsing codes." << std::endl;
    } else {
        std::cerr << "Error when parsing the code with " << fileName << "!"
                  << std::endl;
        if (codeIn)
            fclose(codeIn);
        if (lexerOut)
            fclose(lexerOut);
        if (!grammarOut.bad())
            grammarOut.close();
        return 1;
    }
    // Optimize & print the AST
    TreeOptimizer optimizer(root);
    astOut = std::ofstream(astFileName, std::ios::out);
    if (!astOut.bad() && root != nullptr) {
        std::cout << "Optimizing & printing AST with " << fileName << "..." << std::endl;
        root = optimizer.getOptimizedTree();
        root->printSelf();
        astOut.close();
        std::cout << "End of optimizing & printing AST." << std::endl;
    } else {
        std::cerr << "Error when optimizing & printing AST with " << fileName << "!"
                  << std::endl;
        if (!astOut.bad())
            astOut.close();
        return 1;
    }
    // Update system environment
    SymbolTable *mainSymtab = new SymbolTable("Main_Symbol_Table");
    root->updateEnvironment(mainSymtab);
    // Type check
    checkOut = std::ofstream(chkFileName, std::ios::out);
    std::string check_res = root->typeCheck(mainSymtab);//类型检查
    if (check_res == "failure") {
        std::cout << "type check failed!" << std::endl;
        exit(1);
    } else {
        std::cout << "type check result : " << check_res << std::endl;
    }
    // Build symbol table
    symOut = std::ofstream(symFileName, std::ios::out);
    if (!symOut.bad()) {
        std::cout << "print symbol table begin" << std::endl;
        mainSymtab->printTable(symOut);
        symOut.close();
        std::cout << "end of print symbol table" << std::endl;
    } else {
        std::cerr << "Error when print symbol table!" << std::endl;
        return 1;
    }
    // Generate code
    code = std::ofstream(asmFileName, std::ios::out);
    if (!code.bad()) {
        std::cout << "begin gencode" << std::endl;
        root->genCode(mainSymtab);
        CodeGenerator::genLabel("exit");
        code << "li $v0 10" << std::endl;
        code << "syscall" << std::endl;
        code.close();
        std::cout << "end of gencode" << std::endl;
    } else {
        std::cerr << "Error when gencode!" << std::endl;
        return 1;
    }

    delete regManager;
    delete labelManager;

    // finally dispose resources
    for (auto &it : printedNodes)
        delete it;

    return 0;
}