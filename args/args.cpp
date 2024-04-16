#include "args.h"

namespace sheep_args
{
    void ArgumentParser::AddArgument(std::string name, std::string alias, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt)
    {
        this->alias_to_name[alias] = name;
        if (help.has_value())
        {
            this->help[name] = help.value();
        }
        if (default_value.has_value())
        {
            this->values[name] = default_value.value();
        }
    }
    void ArgumentParser::AddArgument(std::string name, std::vector<std::string> aliases, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt)
    {
    }
    std::string ArgumentParser::GetArgument(std::string name)
    {
    }
    std::optional<sheep_basic::Error> ArgumentParser::Parse(int argc, char **argv)
    {
    }
    void ArgumentParser::clear()
    {
        this->arguments.clear();
        this->help.clear();
    }
}
