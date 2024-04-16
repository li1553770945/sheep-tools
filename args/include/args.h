#include <string>
#include <map>
#include <vector>
#include "basic.h"
#include <optional>
#include <set>

namespace sheep_args
{
    class ArgumentParser
    {
    public:
        void AddArgument(std::string name, std::string alias, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt);
        void AddArgument(std::string name, std::vector<std::string> aliases, std::optional<std::string> help = std::nullopt, std::optional<std::string> default_value = std::nullopt);

        std::optional<std::string> GetFirstValue(std::string name);
        std::vector<std::string> GetValues(std::string name);
        std::optional<sheep_basic::Error> Parse(int argc, char **argv);
        void clear();

    private:
        std::map<std::string, std::string> alias_to_name;
        std::map<std::string, std::string> help;

        std::set<std::string> keys;
        std::map<std::string, std::vector<std::string>> values;
    };
}
