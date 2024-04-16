#include <string>

namespace sheep_basic
{
    class Error
    {
        int code;
        std::string msg;
    public:
        Error(int code);
        Error(std::string msg);
        Error(int code,std::string msg);
        int GetCode();
        std::string GetMessage();
    };
}