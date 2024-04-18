#include "sheep_args.h"
#include "sheep_string.h"
namespace sheep_args
{
    ArgItem::ArgItem(std::string name)
    {
        this->name = std::move(name);
    }
    std::string ArgItem::GetName()
    {
        return this->name;
    }
    ArgItem &ArgItem::AddAlias(std::string alias)
    {
        this->aliases.push_back(alias);
        return *this;
    }

    ArgItem &ArgItem::SetDefaultValue(ArgType value)
    {
        this->value = std::move(value);
        this->has_value = true;
        return *this;
    }
    ArgItem &ArgItem::SetValue(ArgType value)
    {
        this->value = std::move(value);
        has_value = true;
        has_input = true;
        return *this;
    }
    bool ArgItem::HasValue()
    {
        return this->has_value;
    }
    ArgItem &ArgumentParser::AddArgument(std::string name)
    {
        std::shared_ptr<ArgItem> item = std::make_shared<ArgItem>(name);
        this->items.push_back(item);
        this->name_to_arg[name] = item;
        return *item;
    }
    bool ArgumentParser::IsHasValue(std::string name)
    {
        if (this->alias_to_arg.find(name) == this->alias_to_arg.end())
        {
            return false;
        }
        return this->alias_to_arg[name]->HasValue();
    }
    template <typename T>
    T ArgumentParser::GetValue(std::string name)
    {
        ArgType value = "";
        if (this->alias_to_arg.find(name) != this->alias_to_arg.end())
        {
            value = this->name_to_arg[name]->GetValue();
        }

        return std::visit([&](auto &&value) -> T
                          { return convert<T>(value); },
                          value);
    };
    template <typename T, typename U>
    T ArgumentParser::convert(const U &value) const
    {
        if constexpr (std::is_same<T, U>::value)
        {
            return value; 
        }
        else
        {
            // Convert to string using stringstream as intermediate
            std::stringstream ss;
            ss << value;
            T convertedValue;
            ss >> convertedValue;
            if (ss.fail())
            {
                throw std::runtime_error("Conversion failed when get value");
            }
            return convertedValue;
        }
    }
    std::vector<std::string> ArgumentParser::GetKeys(bool must_input, bool must_has_value)
    {
        std::vector<std::string> res;
        for (auto item : items)
        {
            if (must_input)
            {
            }
            else if (must_has_value)
            {
            }
            else
            {
                res.push_back(item->GetName());
            }
        }
        return res;
    }
    std::string ArgumentParser::GetHelp(std::string name)
    {
        if (this->alias_to_arg.find(name) == this->alias_to_arg.end())
        {
            return "";
        }
        return this->alias_to_arg[name]->GetHelp();
    }

    std::list<std::string> ArgumentParser::Parse(int argc, char **argv)
    {
        std::list<std::string> argv_vector;
        for (int i = 0; i < argc; i++)
        {
            argv_vector.push_back(argv[i]);
        }
        return this->Parse(argv_vector);
    }
    std::list<std::string> ArgumentParser::Parse(std::list<std::string> args)
    {
        for (auto it = args.begin(); it != args.end();)
        {
            std::string &arg = *it;
            if (arg[0] == '-')
            {

                auto ky = sheep_string::SplitFirst(arg, '=');
                auto key = ky.first, value = ky.second;

                if (this->alias_to_arg.find(key) == this->alias_to_arg.end())
                {
                    it++;
                    continue;
                }

                // 如果真的有这个参数
                this->keys.push_back(key);
                auto current_it = it;
                it++;
                args.erase(current_it);

                auto item = this->alias_to_arg[key];

                if (arg.find('=') != std::string::npos) // 如果有等于号
                {

                    item->SetValue(value);
                    continue;
                }

                // 没有等于号
                if (it != args.end() && (*it)[0] != '-')
                {
                    item->SetValue(*it);
                    current_it = it;
                    it++;
                    args.erase(current_it);
                }
            }
        }
        return args;
    }
    void ArgumentParser::clear()
    {
        this->alias_to_arg.clear();
        this->name_to_arg.clear();
    }
}
