#include "sheep_args.h"

namespace sheep_args
{
    void ArgumentParser::AddArgument(std::string name, std::string alias, std::optional<std::string> help, std::optional<std::string> default_value)
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
    void ArgumentParser::AddArgument(std::string name, std::vector<std::string> aliases, std::optional<std::string> help, std::optional<std::string> default_value)
    {
        for (auto alias : aliases)
        {
            this->alias_to_name[alias] = name;
        }
        if (help.has_value())
        {
            this->help[name] = help.value();
        }
        if (default_value.has_value())
        {
            this->values[name] = default_value.value();
        }
    }
    std::optional<std::string> ArgumentParser::GetValue(std::string name)
    {
        if (this->values.find(name) != this->values.end())
        {
            return this->values[name];
        }
        else
        {
            return std::nullopt;
        }
    }
    std::vector<std::string> ArgumentParser::GetKeys()
    {
        return this->keys;
    }
    void ArgumentParser::Parse(int argc, char **argv)
    {
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            if (this->alias_to_name.find(arg) != this->alias_to_name.end())
            {
                std::string name = this->alias_to_name[arg];
                this->keys.push_back(name);
                if (i < argc - 1 && alias_to_name.find(argv[i + 1]) == this->alias_to_name.end()) // 如果后面还有参数，并且不在alias里面，认为是值
                {
                    values[name] = argv[i + 1];
                    i++;
                }
            }
        }
    }
    std::string ArgumentParser::GetHelp(std::string name)
    {
        if (this->help.find(name) != this->help.end())
        {
            return this->help[name];
        }
        else
        {
            return "";
        }
    }
    void ArgumentParser::clear()
    {
        this->alias_to_name.clear();
        this->help.clear();
        this->keys.clear();
        this->values.clear();
    }
}
