//
// Created by yejt on 18-5-12.
//

#ifndef COMPILER_COMMENT_H
#define COMPILER_COMMENT_H

#include <iostream>
#include <string>

enum State
{
    CODE, // Initial state
    SLASH, // Input with single slash: /
    COMMENT_MULTILINE, // Input with /*[content]
    COMMENT_MULTILINE_STAR, // Input with /*[content]*
    COMMENT_SINGLE_LINE, // Input with //[content]
    BACKSLASH, // Input with //[content]\ ..
    CODE_CHAR, // Input with '
    CHAR_ESCAPE_SEQUENCE, // Input with '\.
    CODE_STRING, // Input with "
    STRING_ESCAPE_SEQUENCE // Input with "\.
};

class CommemtProcessor
{
private:
    std::string deleteComment(const std::string& in);
    std::string readContent(std::istream& in);
    void writeContent(const std::ostream& out, const std::string& content);
public:
    void processComment(std::istream& in, std::ostream& out);
};

#endif //COMPILER_COMMENT_H
