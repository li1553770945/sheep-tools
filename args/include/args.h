namespace sheep_args
{
#include <string>
#include <iostream>
#include <map
    class ArgumentParser
    {
    public:
        ArgumentParser(int argc, char *argv[]);
        void Parse();
        void AddArgument(std::string name,  std::string default_value="",std::string help="",);

    private:
        std::map<std::string, std::string> arguments;
        std::map<std::string, std::string> help;
        std::map<std::string, std::string> defaults;
        int argc;
        char **argv;
    };
}
