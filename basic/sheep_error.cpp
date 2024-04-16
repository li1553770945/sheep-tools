#include "sheep_basic.h"
namespace sheep_basic{
   
        Error::Error(int code)
        {
            this->code = code;
            this->msg = "";
        }
        Error::Error(std::string msg)
        {
            this->code = -1;
            this->msg = msg;
        }
        Error::Error(int code,std::string msg)
        {
            this->code = code;
            this->msg = msg;
        }
        int Error::GetCode()
        {
            return this->code;
        }
        std::string Error::GetMessage()
        {
            return this->msg;
        }
}