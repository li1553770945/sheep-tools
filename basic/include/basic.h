namespace sheep_basic
{
    #include <string>
    class Error
    {
        int code;
        std::string msg;
    public:
        Error(int code);
        Error(std::string msg);
        Error(int code,std::string msg);
        int GetCode();
        std::string GetMessage();
    };
}