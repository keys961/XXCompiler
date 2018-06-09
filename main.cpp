#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <exception>
#include "comment.h"
#include "lexer.h"
#include "parser.hpp"
#include "tree.h"
#include "optimizer.h"
#include "codegen.h"

#define OPT_LEX 1
#define OPT_GRAMMAR 2
#define OPT_AST 4
#define OPT_SYM 8
#define OPT_TYPE_CHECK 16

/**
 * Global variables
 */
FILE *codeIn; // Code input
std::ofstream preProcessOut; // Code output after pre-processing
FILE *lexerOut; // Lexer analysis output
std::ofstream grammarOut; // Grammar output
std::ofstream astOut; // AST output
std::ofstream symOut; // symbol output
std::ofstream checkOut; // type check output
std::ofstream code; // codegen output

RegManager *regManager;
LabelManager *labelManager;
CodeGenerator* codeGenerator;
std::map<std::string, enum myOption> opMap;

GlobalInfo globalInfo;
TreeNode *root; // ProgramBodyTreeNode

std::set<TreeNode *> printedNodes;

unsigned int getOptionCode(std::string option);
void outputToStdOut(const std::string &filename);

int main(int argc, const char *argv[]) {
    /* Format: compiler src_file_name [-options] output_file_name */
    if (argc < 3) {
        std::cerr << "Wrong input format!" << std::endl;
        std::cout << "\t compiler $src_file_name [-options] $output_file_name" << std::endl;
        std::cout << "Options: " << std::endl;
        std::cout << "\t -l: Print lexical analysis result to standard output." << std::endl;
        std::cout << "\t -g: Print grammar analysis result to standard output." << std::endl;
        std::cout << "\t -a: Print AST result to standard output." << std::endl;
        std::cout << "\t -s: Print symbol table result to standard output." << std::endl;
        std::cout << "\t -c: Print type checking result to standard output." << std::endl;
        return 1;
    }
    // Prepare
    std::string fileName = argv[1];
    std::string preProcessFileName = fileName + ".pre";
    std::string lexerFileName = fileName + ".lexer"; //-l
    std::string grammarFileName = fileName + ".grammar"; // -g
    std::string astFileName = fileName + ".ast"; // -a
    std::string symFileName = fileName + ".sym"; // -s
    std::string chkFileName = fileName + ".chk"; // -c
    std::string asmFileName;
    unsigned int optionCode = 0;

    if(argc == 3)
        asmFileName = argv[2];
    else {
        optionCode = getOptionCode(argv[2]);
        asmFileName = argv[3];
    }
    asmFileName += ".asm";
    regManager = new RegManager();
    labelManager = new LabelManager();
    codeGenerator = new CodeGenerator();
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
        if(optionCode & OPT_LEX)
            outputToStdOut(lexerFileName);
        if(optionCode & OPT_GRAMMAR)
            outputToStdOut(grammarFileName);
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
        if(optionCode & OPT_AST)
            outputToStdOut(astFileName);
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
        std::cerr << "Type check failed!" << std::endl;
        checkOut.close();
        exit(1);
    } else {
        checkOut.close();
        if(optionCode & OPT_TYPE_CHECK)
            outputToStdOut(chkFileName);
        std::cout << "Type check result : " << check_res << std::endl;
    }
    // Build symbol table
    symOut = std::ofstream(symFileName, std::ios::out);
    if (!symOut.bad()) {
        std::cout << "Print symbol table begin..." << std::endl;
        mainSymtab->printTable(symOut);
        symOut.close();
        if(optionCode & OPT_SYM)
            outputToStdOut(symFileName);
        std::cout << "End of print symbol table" << std::endl;
    } else {
        std::cerr << "Error when print symbol table!" << std::endl;
        symOut.close();
        return 1;
    }
    // Generate code
    code = std::ofstream(asmFileName, std::ios::out);
    if (!code.bad()) {
        std::cout << "Begin generating code..." << std::endl;
        root->genCode(mainSymtab);
        codeGenerator->genLabel("exit");
        code << "li $v0 10" << std::endl;
        code << "syscall" << std::endl;
        code.close();
        std::cout << "Generating target code success!" << std::endl;
    } else {
        std::cerr << "Error when generating code!" << std::endl;
        return 1;
    }

    delete regManager;
    delete labelManager;

    // finally dispose resources
    try {
        for (auto &it : printedNodes)
            delete it;
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 0;
    }

    return 0;
}

unsigned int getOptionCode(std::string option)
{
//#define OPT_LEX 1
//#define OPT_GRAMMAR 2
//#define OPT_AST 4
//#define OPT_SYM 8
//#define OPT_TYPE_CHECK 16
    std::map<char, int> opcodeMap;
    opcodeMap['l'] = 1;
    opcodeMap['g'] = 2;
    opcodeMap['a'] = 4;
    opcodeMap['s'] = 8;
    opcodeMap['c'] = 16;

    unsigned int res = 0;

    for(int i = 1; i < option.size(); i++)
        res += opcodeMap[option[i]];

    return res;
}

void outputToStdOut(const std::string &filename) {
    std::ifstream in(filename, std::ios::in);
    std::cout << "\n Filename: " << filename << std::endl;
    std::string content;
    std::string line;
    while(std::getline(in, line))
        content += line + "\n";
    std::cout << content << std::endl;
    in.close();
}
