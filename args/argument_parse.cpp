#include "sheep_args.h"
#include "sheep_string.h"
namespace sheep_args
{
    ArgItem &ArgumentParser::AddArgument(const std::string &name)
    {
        std::shared_ptr<ArgItem> item = std::make_shared<ArgItem>(name);
        this->items.push_back(item);
        this->name_to_arg[name] = item;
        return *item;
    }

    bool ArgumentParser::IsHasValue(const std::string &name)
    {
        if (this->name_to_arg.find(name) == this->name_to_arg.end())
        {
            return false;
        }
        return this->name_to_arg[name]->IsHasValue();
    }
    std::shared_ptr<ArgItem> ArgumentParser::operator[](const std::string &name)
    {
         if (this->name_to_arg.find(name) == this->name_to_arg.end())
        {
            return nullptr;
        }
        return this->name_to_arg[name];
    }
    std::vector<std::string> ArgumentParser::GetKeys(bool must_input, bool must_has_value)
    {
        std::vector<std::string> res;
        for (auto item : items)
        {
            if (must_input)
            {
                if (!item->IsInputByUser())
                {
                    continue;
                }
            }
            if (must_has_value)
            {
                if (!item->IsHasValue())
                {
                    continue;
                }
            }
            res.push_back(item->GetName());
        }
        return res;
    }
    std::string ArgumentParser::GetHelp(std::string name)
    {
        if (this->name_to_arg.find(name) == this->name_to_arg.end())
        {
            return "";
        }
        return this->name_to_arg[name]->GetHelp();
    }

    std::list<std::string> ArgumentParser::Parse(int argc, char **argv)
    {
        std::list<std::string> argv_vector;
        for (int i = 1; i < argc; i++)
        {
            argv_vector.push_back(argv[i]);
        }
        this->Parse(argv_vector);
        return argv_vector;
    }
    void ArgumentParser::Parse(std::list<std::string> &args)
    {
        this->alias_to_arg.clear();
        for (auto &item : items)
        {
            for (auto &alias : item->aliases)
            {
                this->alias_to_arg[alias] = item;
            }
        }
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
                bool has_equal = (arg.find('=') != std::string::npos);
                // 如果真的有这个参数
                this->keys.push_back(key);
                auto current_it = it;
                it++;
                args.erase(current_it);
                auto item = this->alias_to_arg[key];
                if (has_equal) // 如果有等于号
                {

                    item->SetInputValue(value);
                    continue;
                }

                // 没有等于号
                if (it != args.end() && (*it)[0] != '-')
                {
                    item->SetInputValue(*it);
                    current_it = it;
                    it++;
                    args.erase(current_it);
                }
            }
            else
            {
                it++;
            }
        }
        return;
    }
    void ArgumentParser::clear()
    {
        this->alias_to_arg.clear();
        this->name_to_arg.clear();
        this->keys.clear();
        this->items.clear();
    }
}
