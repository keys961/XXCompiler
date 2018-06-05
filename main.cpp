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

/**
 * Global variables
 */
FILE* codeIn; // Code input
std::ofstream preProcessOut; // Code output after pre-processing
FILE* lexerOut; // Lexer analysis output
std::ofstream grammarOut; // Grammar output
std::ofstream astOut; // AST output
std::ofstream codeOut; // Target code output

GlobalInfo globalInfo;
TreeNode* root; // ProgramBodyTreeNode

std::set<TreeNode*> printedNodes;

int main(int argc, const char *argv[])
{
    /* Format: compiler src_file_name output_file_name */
    if(argc != 3)
    {
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
    // Pre-processing
    CommemtProcessor processor;
    std::fstream fin(argv[1], std::ios::in);
    preProcessOut = std::ofstream(preProcessFileName, std::ios::out);
    if(!fin.bad() && !preProcessOut.bad())
    {
        std::cout << "Pre-processing code with " << fileName << "..." << std::endl;
        processor.processComment(fin, preProcessOut);
        preProcessOut.flush();
        fin.close();
        preProcessOut.close();
        std::cout << "End pre-processing." << std::endl;
    }
    else
    {
        std::cerr << "Error when pre-processing code with "
                  << fileName << "!" << std::endl;
        if(!fin.bad())
            fin.close();
        if(!preProcessOut.bad())
            preProcessOut.close();
        return 1;
    }
    // Lexical & Grammar analysis
    codeIn = fopen(preProcessFileName.c_str(), "r");
    lexerOut = fopen(lexerFileName.c_str(), "w+");
    grammarOut = std::ofstream(grammarFileName, std::ios::out);
    if(codeIn && lexerOut && !grammarOut.bad())
    {
        std::cout << "Parsing code with " << fileName << "..." << std::endl;
        yyparse();
        fclose(codeIn);
        fclose(lexerOut);
        grammarOut.close();
        std::cout << "End of parsing codes." << std::endl;
    }
    else
    {
        std::cerr << "Error when parsing the code with " << fileName << "!"
                  << std::endl;
        if(codeIn)
            fclose(codeIn);
        if(lexerOut)
            fclose(lexerOut);
        if(!grammarOut.bad())
            grammarOut.close();
        return 1;
    }
    // Optimize & print the AST
    TreeOptimizer optimizer(root);
    astOut = std::ofstream(astFileName, std::ios::out);
    if(!astOut.bad() && astOut != nullptr)
    {
        std::cout << "Optimizing & printing AST with " << fileName << "..." << std::endl;
        root = optimizer.getOptimizedTree();
        root->printSelf();
        astOut.close();
        std::cout << "End of optimizing & printing AST." << std::endl;
    }
    else
    {
        std::cerr << "Error when optimizing & printing AST with " << fileName << "!"
                  << std::endl;
        if(!astOut.bad())
            astOut.close();
        return 1;
    }
    // Update symbol table

    // Type check

    // Generate code


    // finally dispose resources
    for(auto& it : printedNodes)
        delete it;

    return 0;
}