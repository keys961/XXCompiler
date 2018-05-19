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
                    state = SLASH;  // -> /
                else
                {
                    result += c;
                    if(c == '\'')
                        state = CODE_CHAR; // -> '
                    else if(c == '\"')
                        state = CODE_STRING; // -> "
                }
                break;
            case SLASH:
                if(c == '*')
                    state = COMMENT_MULTILINE; // / -> /*
                else if (c == '/')
                    state = COMMENT_SINGLE_LINE; // / -> //
                else
                {
                    result += '/';
                    result += c;
                    state = CODE; // /[content] -> return to code
                }
                break;
            case COMMENT_MULTILINE:
                if(c == '*')
                    state = COMMENT_MULTILINE_STAR; // /*[content]*
                else
                {
                    if(c == '\n')
                        result += "\r\n"; // add a new line
                }
                break;
            case COMMENT_MULTILINE_STAR: // /*/ -> as code
                if(c == '/')
                    state = CODE;
                else if(c == '*') // /** -> may end of comment but stay unchanged
                    state = COMMENT_MULTILINE_STAR;
                else // Still in comment_multiline
                    state = COMMENT_MULTILINE;
                break;
            case COMMENT_SINGLE_LINE:
                if (c == '\\')
                    state = BACKSLASH; // backslash comment
                else if (c == '\n')
                {
                    result += "\r\n";
                    state = CODE; // new line, restore state
                }
                break;
            case BACKSLASH:
                if(c == '\\' || c == '\r' || c == '\n')
                {
                    if(c == '\n')
                        result += "\r\n";
                }
                else
                    state = COMMENT_SINGLE_LINE; // in new line return to state single_line
                break;
            case CODE_CHAR:
                result += c;
                if(c == '\\')
                    state = CHAR_ESCAPE_SEQUENCE; // escaped char
                else if (c == '\'')
                    state = CODE; // end of char, return to code
                break;
            case CHAR_ESCAPE_SEQUENCE:
                result += c; // only to get the next char
                state = CODE_CHAR;
                break;
            case CODE_STRING:
                result += c;
                if(c == '\\')
                    state = STRING_ESCAPE_SEQUENCE; // escaped char in str
                else if(c == '\"')
                    state = CODE; // end of str, return to code
                break;
            case STRING_ESCAPE_SEQUENCE:
                result += c;
                state = CODE_STRING; // same as char_escape
                break;
        }
    }

    return result; // processed string, keep the original line number
}

std::string CommemtProcessor::readContent(std::istream &in)
{
    std::string content;
    std::string line;
    while(std::getline(in, line))
        content += line + "\n";
    return content;
}

void CommemtProcessor::writeContent(const std::ostream &out, const std::string &content)
{
    out << content << std::endl; // write it to output stream
}

