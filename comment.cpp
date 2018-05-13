//
// Created by yejt on 18-5-12.
//

#include "comment.h"

void CommemtProcessor::processComment(std::istream &in, std::ostream &out)
{
    writeContent(out, deleteComment(readContent(in)));
}

std::string CommemtProcessor::deleteComment(const std::string& in)
{
    std::string result;
    State state = CODE;

    for (char c : in) {
        switch (state)
        {
            case CODE:
                if(c == '/')
                    state = SLASH;
                else
                {
                    result += c;
                    if(c == '\'')
                        state = CODE_CHAR;
                    else if(c == '\"')
                        state = CODE_STRING;
                }
                break;
            case SLASH:
                if(c == '*')
                    state = COMMENT_MULTILINE;
                else if (c == '/')
                    state = COMMENT_SINGLE_LINE;
                else
                {
                    result += '/';
                    result += c;
                    state = CODE;
                }
                break;
            case COMMENT_MULTILINE:
                if(c == '*')
                    state = COMMENT_MULTILINE_STAR;
                else
                {
                    if(c == '\n')
                        result += "\r\n";
                }
                break;
            case COMMENT_MULTILINE_STAR:
                if(c == '/')
                    state = CODE;
                else if(c == '*')
                    state = COMMENT_MULTILINE_STAR;
                else
                    state = COMMENT_MULTILINE;
                break;
            case COMMENT_SINGLE_LINE:
                if (c == '\\')
                    state = BACKSLASH;
                else if (c == '\n')
                {
                    result += "\r\n";
                    state = CODE;
                }
                break;
            case BACKSLASH:
                if(c == '\\' || c == '\r' || c == '\n')
                {
                    if(c == '\n')
                        result += "\r\n";
                }
                else
                    state = COMMENT_SINGLE_LINE;
                break;
            case CODE_CHAR:
                result += c;
                if(c == '\\')
                    state = CHAR_ESCAPE_SEQUENCE;
                else if (c == '\'')
                    state = CODE;
                break;
            case CHAR_ESCAPE_SEQUENCE:
                result += c;
                state = CODE_CHAR;
                break;
            case CODE_STRING:
                result += c;
                if(c == '\\')
                    state = STRING_ESCAPE_SEQUENCE;
                else if(c == '\"')
                    state = CODE;
                break;
            case STRING_ESCAPE_SEQUENCE:
                result += c;
                state = CODE_STRING;
                break;
            default:
                break;

        }
    }

    return result;
}

std::string CommemtProcessor::readContent(std::istream &in)
{
    std::string content;
    std::string line;
    while(std::getline(in, line))
        content += line + "\n";
    return content;
}

void CommemtProcessor::writeContent(std::ostream &out, const std::string &content)
{
    out << content << std::endl;
}

