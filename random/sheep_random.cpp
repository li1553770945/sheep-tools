#include "sheep_random.h"
#include <random>
#include <algorithm>
#include <string>

namespace sheep_random
{
    int randInRange(int min, int max)
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
    std::string RandomString(int len, int flag)
    {
        std::string characters;
        std::string result;

        if (flag & UPPER)
        {
            characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }
        if (flag & LOWER)
        {
            characters += "abcdefghijklmnopqrstuvwxyz";
        }
        if (flag & NUM)
        {
            characters += "0123456789";
        }

        std::shuffle(characters.begin(), characters.end(), std::mt19937(std::random_device{}()));

        for (int i = 0; i < len; ++i)
        {
            result += characters[randInRange(0, characters.size() - 1)];
        }
        return result;
    }
}