//
// Created by yejt on 18-5-12.
//

#ifndef COMPILER_COMMENT_H
#define COMPILER_COMMENT_H

#include <iostream>
#include <string>

class CommemtProcessor
{
private:
    std::string processLine(std::string in);
public:
    void processComment(std::istream& in, std::ostream& out);
};

#endif //COMPILER_COMMENT_H
