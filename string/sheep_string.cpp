#include "sheep_string.h"
namespace sheep_string
{
    std::pair<std::string, std::string> SplitFirst(std::string str, char spliter)
    {
        size_t pos = str.find(spliter);
        if (pos != std::string::npos)
        {
            std::string firstPart = str.substr(0, pos);
            std::string secondPart = str.substr(pos + 1);
            return {firstPart, secondPart};
        }
        else
        {
            return {str, ""};
        }
    }
}