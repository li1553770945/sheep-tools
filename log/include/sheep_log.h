#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>

namespace sheep_log
{
    using LogLevel = int;
    const int Debug = 0;
    const int Info = 1;
    const int Warn = 2;
    const int Error = 3;
    const int Fatal = 4;

    class Handler
    {
    private:
        bool new_line = true;
        void PrintHeader();

    protected:
        LogLevel level = Info;
        virtual void Print(int msg) = 0;
        virtual void Print(unsigned msg) = 0;
        virtual void Print(long long msg) = 0;
        virtual void Print(unsigned long long msg) = 0;

        virtual void Print(float msg) = 0;
        virtual void Print(double msg) = 0;

        virtual void Print(std::string msg) = 0;
        virtual void Print(char *msg) = 0;
        virtual void Print(const char *msg) = 0;

        void StartNewLine();

    public:
        template <typename T>
        void Log(const T &message, const LogLevel &level)
        {
            if (level < this->level)
            {
                return;
            }
            if (this->new_line)
            {
                this->PrintHeader();
                this->new_line = false;
            }

            this->Print(message);
        }
        void SetLevel(LogLevel level);
        void SetFormat(std::string format);

        friend std::shared_ptr<Handler> endl(std::shared_ptr<Handler> handler);
    };

    std::shared_ptr<Handler> endl(std::shared_ptr<Handler> handler);
    
    class Logger
    {
        std::string name;
        std::vector<std::shared_ptr<Handler>> handlers;
        LogLevel temp_level = Info;

    public:
        Logger(std::string name);
        void AddHandler(std::shared_ptr<Handler> handler);
        Logger &operator[](LogLevel level);

        template <typename T>
        Logger &operator<<(const T &msg)
        {

            for (auto &handler : handlers)
            {
                handler->Log(msg, this->temp_level);
            }
            return *this;
        }

        Logger &operator<<(std::shared_ptr<Handler> (*func)(std::shared_ptr<Handler>))
        {

            for (auto &handler : handlers)
            {
                handler = func(handler);
            }
            return *this;
        }
    };

    class StreamHandler : public Handler
    {

    public:
        void Print(int msg) override;
        void Print(unsigned msg) override;
        void Print(long long msg) override;
        void Print(unsigned long long msg) override;

        void Print(float msg) override;
        void Print(double msg) override;

        void Print(std::string msg) override;
        void Print(char *msg) override;
        void Print(const char *msg) override;
    };

    class FileHandler : public Handler
    {
        std::string filename;
        std::ofstream file;

    public:
        FileHandler(const std::string filename);
        void Print(int msg) override;
        void Print(unsigned msg) override;
        void Print(long long msg) override;
        void Print(unsigned long long msg) override;

        void Print(float msg) override;
        void Print(double msg) override;

        void Print(std::string msg) override;
        void Print(char *msg) override;
        void Print(const char *msg) override;
        ~FileHandler();
    };

}
