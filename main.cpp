#include <cstdio>
#include <string>

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
    printf("%d\n", 123);

    return 0;
}