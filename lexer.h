#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H
/**
 * Global info of a file to be parsed
 * when the program is parsing this file
 * for tracing.
 */
class GlobalInfo
{
public:
    long currentLineIndex = 1;
    long currentTokenIndex;
    std::string currentToken;
};

int getCurrentToken();

int saveTraceInfo();

#endif //COMPILER_LEXER_H
