#include <iostream>
#include "sheep_args.h"
using namespace std;

//g++ test_args.cpp ../../args/*.cpp -o test_args -I "../../string/include"  -I "../../args/include" -I "../../basic/include"  -std=c++17
int main(int argc,char ** argv)
{
    sheep_args::ArgumentParser args;
    args.AddArgument("dir").AddAlias("--dir","-d").SetDefaultValue(123);
    cout<<"A"<<endl;
    args.Parse(argc,argv);
    cout<<"B"<<endl;
    int dir = args.GetValue<int>("dir");
    cout<<dir<<endl;
    return 0;
}