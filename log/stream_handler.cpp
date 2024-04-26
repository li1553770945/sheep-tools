#include "sheep_log.h"
#include <iostream>
namespace sheep_log
{

    void StreamHandler::Print(int msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(unsigned msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(long long msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(unsigned long long msg)
    {
        std::cout << msg;
    }

    void StreamHandler::Print(float msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(double msg)
    {
        std::cout << msg;
    }

    void StreamHandler::Print(std::string msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(char *msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Print(const char *msg)
    {
        std::cout << msg;
    }
    void StreamHandler::Flush()
    {
        std::cout.flush();
    }

}