
#include "sheep_log.h"
#include <string>
#include <iostream>
namespace sheep_log
{
    Logger::Logger(std::string name)
    {
        this->name = std::move(name);
    }
    void Logger::AddHandler(std::shared_ptr<Handler> handler)
    {
        this->handlers.push_back(handler);
    }
    Logger &Logger::operator[](LogLevel level)
    {

        temp_level = std::move(level);
        return *this;
    }

}