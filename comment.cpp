//
// Created by yejt on 18-5-12.
//

#include "comment.h"

std::string CommemtProcessor::processLine(std::string in)
{
    unsigned int index = in.find("//");
    return in.substr(0, index);
}

void CommemtProcessor::processComment(std::istream &in, std::ostream &out)
{
    std::string line;
    while(std::getline(in, line))
        out << processLine(line) << std::endl;
    out.flush();
}

