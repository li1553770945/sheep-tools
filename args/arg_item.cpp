#include "sheep_args.h"
#include "sheep_string.h"
namespace sheep_args
{
    ArgItem::ArgItem(std::string name)
    {
        this->name = std::move(name);
    }

    void ArgItem::SetInputValue(std::string v)
    {
        this->input_by_user = true;
        this->has_value = true;
        this->value = v;
    }
    std::string ArgItem::GetName()
    {
        return this->name;
    }
    std::string ArgItem::GetHelp()
    {
        return this->help;
    }
    bool ArgItem::IsHasValue()
    {
        return this->has_value;
    }
    bool ArgItem::IsInputByUser()
    {
        return this->input_by_user;
    }

    ArgItem &ArgItem::AddAlias(std::string alias)
    {
        this->aliases.push_back(alias);
        return *this;
    }
    ArgItem &ArgItem::AddAlias(const char *alias)
    {
        this->AddAlias(std::string(alias));
        return *this;
    }
    ArgItem &ArgItem::AddAlias()
    {

        return *this;
    }

    ArgItem &ArgItem::SetDefaultValue(std::string value)
    {
        this->has_value = true;
        this->value = std::move(value);
        return *this;
    }

      ArgItem &ArgItem::SetDefaultValue(const char * value)
    {
        this->has_value = true;
        this->value = std::string(value);
        return *this;
    }
}
