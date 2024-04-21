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
#include <typeinfo>
#include <iostream>

namespace sheep_args
{
    template <typename T>
    T parse_value(std::string value)
    {
        // static_assert(std::is_same_v<T, void>, "parse_value is not implemented for this type");
        std::cout << value << std::endl;
        // must impletemnt
        return T(value);
    }
    template <>
    inline int parse_value<int>(std::string value)
    {
        return atoi(value.data());
    }
    template <>
    inline std::string parse_value<std::string>(std::string value)
    {
        return value;
    }
    template <>
    inline float parse_value<float>(std::string value)
    {
        return atof(value.data());
    }

    class ArgItem
    {
        friend class ArgumentParser;
        std::string name;
        std::vector<std::string> aliases;

        std::string value;

        bool input_by_user = false;
        bool has_value = false;

        std::string help;

        void SetInputValue(std::string v);

        template <typename T>
        void SetInputValue(T v)
        {
            this->input_by_user = true;
            this->has_value = true;
            this->value = std::to_string(v);
        }

    public:
        ArgItem(std::string name);
        std::string GetName();
        std::string GetHelp();
        bool IsHasValue();
        bool IsInputByUser();

        template <typename FirstAlias, typename... RemainingAlias>
        ArgItem &AddAlias(FirstAlias alias, RemainingAlias... aliases)
        {
            this->AddAlias(alias);
            return this->AddAlias(aliases...);
        }

        ArgItem &AddAlias(std::string);
        ArgItem &AddAlias(const char *);
        ArgItem &AddAlias();

        template <typename T>
        ArgItem &SetDefaultValue(T value)
        {
            this->SetDefaultValue(std::to_string(value));
            return *this;
        }
        ArgItem &SetDefaultValue(std::string value);
        ArgItem &SetDefaultValue(const char *value);

        template <typename T>
        T GetValue()
        {
            return parse_value<T>(this->value);
        }
    };

    class ArgumentParser
    {
    public:
        ArgItem &AddArgument(const std::string &name);
        bool IsHasValue(std::string name);
        template <typename T>
        T GetValue(std::string name)
        {
            auto it = this->name_to_arg.find(name);
            if (it == this->name_to_arg.end())
            {
                return parse_value<T>("");
            }
            else
            {
                return it->second->GetValue<T>();
            }
        }

        std::vector<std::string> GetKeys(bool must_input = false, bool must_has_value = false);

        std::string GetHelp(std::string name);
        std::list<std::string> Parse(int argc, char **argv);
        std::list<std::string> Parse(std::list<std::string> args);
        void clear();

    private:
        std::map<std::string, std::shared_ptr<ArgItem>> alias_to_arg;
        std::map<std::string, std::shared_ptr<ArgItem>> name_to_arg;
        std::vector<std::string> keys;
        std::vector<std::shared_ptr<ArgItem>> items;
    };
}
