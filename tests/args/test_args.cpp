#include <iostream>
#include "args.h"
using namespace std;

//g++ test_args.cpp ../../args/args.cpp -o test_args -I "../../args/include" -I "../../basic/include" -std=c++17
int main(int argc,char ** argv)
{
    sheep_args::ArgumentParser args;
    args.AddArgument("dir","-d","diretory of the container");
    args.Parse(argc,argv);

    auto keys = args.GetKeys();
    for(auto key:keys)
    {
        cout<<key<<endl;
        auto value = args.GetValue(key);
        cout<<value.value()<<endl;
    }
    return 0;
}