#include "sheep_log.h"
namespace sheep_log
{
    std::shared_ptr<Handler> endl(std::shared_ptr<Handler> handler)
    {
        handler->Print("\n");
        handler->Flush();
        handler->StartNewLine();
        return handler;
    }

    void Handler::PrintHeader()
    {
        // TODO: 根据format生成header
        std::string header = "this is header:";
        Print(header);
    }
    void Handler::SetLevel(LogLevel level)
    {
        this->level = level;
    }

    void Handler::SetFormat(std::string format)
    {
        // TODO:未实现
    }
    void Handler::StartNewLine()
    {
        this->new_line = true;
    }

}
