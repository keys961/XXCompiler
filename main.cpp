#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include "comment.h"

/**
 * Global info of a file to be parsed
 * when the program is parsing this file
 * for tracing.
 */
typedef struct GlobalInfo
{
    long currentLineCount;
    std::string currentToken;
}GlobalInfo;

/**
 * Global variables
 */
FILE* in = NULL;
FILE* out = NULL;
GlobalInfo globalInfo;

int main()
{
    //？？？？？？？？？？？？？？？
    CommemtProcessor processor;
    std::fstream fin("1.txt", std::ios::in);
    std::fstream fout("2.txt", std::ios::out);

    if(!fin.bad() && !fout.bad())
    {
        processor.processComment(fin, fout);
        fin.close();
        fout.close();
    }

    return 0;
}