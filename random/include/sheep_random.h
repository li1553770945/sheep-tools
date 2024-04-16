#pragma once
#include <string>
namespace sheep_random
{
    extern int UPPER;
    extern int LOWER;
    extern int NUM;
    extern int ALPHA;
    extern int ALL;
    std::string RandomString(int len, int flag);
}