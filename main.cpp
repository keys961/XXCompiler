#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include "comment.h"
#include "lexer.h"
#include "parser.hpp"

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

int main(int argc, const char *argv[])
{

//    CommemtProcessor processor;
//    std::fstream fin("1.txt", std::ios::in);
//    std::fstream fout("2.txt", std::ios::out);
//
//    if(!fin.bad() && !fout.bad())
//    {
//        processor.processComment(fin, fout);
//        fin.close();
//        fout.close();
//    }
    yyparse();

    return 0;
}