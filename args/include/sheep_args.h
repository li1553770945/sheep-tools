#pragma once
#include <string>
#include <map>
#include <vector>
#include <optional>
#include <set>

namespace sheep_args
{
    class ArgumentParser
    {
    public:
        void AddArgument(std::string name, std::string alias, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt);
        void AddArgument(std::string name, std::vector<std::string> aliases, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt);

        std::string GetValue(std::string name);
        std::optional<std::string> GetValueWithError(std::string name);
        std::vector <std::string> GetKeys();
        std::string GetHelp(std::string name);
        void Parse(int argc, char **argv);
        void clear();

    private:
        std::map<std::string, std::string> alias_to_name;
        std::map<std::string, std::string> help;

        std::vector<std::string> keys;
        std::map<std::string, std::string> values;
    };
}
