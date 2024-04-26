#include "sheep_log.h"
namespace sheep_log
{

    FileHandler::FileHandler(const std::string filename)
    {
        this->filename = std::move(filename);
        file.open(filename, std::ios::app);
    }

    void FileHandler::Print(int msg)
    {
        file<<msg;
    }
    void FileHandler::Print(unsigned msg)
    {
        file<<msg;
    }
    void FileHandler::Print(long long msg)
    {
        file<<msg;
    }
    void FileHandler::Print(unsigned long long msg)
    {
        file<<msg;
    }

    void FileHandler::Print(float msg)
    {
        file<<msg;
    }
    void FileHandler::Print(double msg)
    {
        file<<msg;
    }

    void FileHandler::Print(std::string msg)
    {
        file<<msg;
    }
    void FileHandler::Print(char *msg)
    {
        file<<msg;
    }
    void FileHandler::Print(const char *msg)
    {
        file<<msg;
    }
    void FileHandler::Flush()
    {
        file.flush();
    }

    FileHandler::~FileHandler()
    {
        file.close();
    }
}