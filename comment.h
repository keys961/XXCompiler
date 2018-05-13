//
// Created by yejt on 18-5-12.
//

#ifndef COMPILER_COMMENT_H
#define COMPILER_COMMENT_H

#include <iostream>
#include <string>

/**
 * Referenced from https://www.cnblogs.com/mq0036/p/7942878.html
 */

enum State
{
    CODE,
    SLASH,
    COMMENT_MULTILINE,
    COMMENT_MULTILINE_STAR,
    COMMENT_SINGLE_LINE,
    BACKSLASH,
    CODE_CHAR,
    CHAR_ESCAPE_SEQUENCE,
    CODE_STRING,
    STRING_ESCAPE_SEQUENCE
};

class CommemtProcessor
{
private:
    std::string deleteComment(const std::string& in);
    std::string readContent(std::istream& in);
    void writeContent(std::ostream& out, const std::string& content);
public:
    void processComment(std::istream& in, std::ostream& out);
};

#endif //COMPILER_COMMENT_H
