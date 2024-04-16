#pragma once
#include <string>
namespace sheep_random
{
    int UPPER = 1;
    int LOWER = 1 << 1;
    int NUM = 1 << 2;
    int ALPHA = UPPER | LOWER;
    int ALL = NUM|ALPHA;
    std::string RandomString(int len, int flag);
}