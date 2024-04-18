#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>
#include <optional>
#include <set>
#include "sheep_basic.h"
#include <memory>
#include <variant>

namespace sheep_args
{

    using ArgType = std::variant<int, double, std::string>;

    class ArgItem
    {
        // friend class ArgumentParser;
        std::string name;
        std::vector<std::string> aliases;
        ArgType value;
        bool has_input = false;
        bool has_value = 0;

        std::string help;

    public:
        ArgItem(std::string name);
        std::string GetName();
        ArgItem &AddAlias(std::string alias);
        // ArgItem &SetValueNum(int num); // 最多接受多少个参数 -1表示接受无限个参数
        ArgItem &SetDefaultValue(ArgType value);
        ArgItem &SetValue(ArgType value);
        ArgItem &SetRequired(bool required);

        std::string GetHelp();
        ArgType GetValue();
        bool HasValue();
    };
    class ArgumentParser
    {
    public:
        ArgItem &AddArgument(std::string name);

        bool IsHasValue(std::string name);
        template <typename T>
        T GetValue(std::string name);

        std::vector<std::string> GetKeys(bool must_input = false, bool must_has_value = false);

        std::string GetHelp(std::string name);
        std::list<std::string> Parse(int argc, char **argv);
        std::list<std::string> Parse(std::list<std::string> args);
        void clear();

    private:
        template <typename T, typename U>
        T ArgumentParser::convert(const U &value) const;

        std::map<std::string, std::shared_ptr<ArgItem>> alias_to_arg;
        std::map<std::string, std::shared_ptr<ArgItem>> name_to_arg;
        std::vector<std::string> keys;
        std::vector<std::shared_ptr<ArgItem>> items;
    };
}
