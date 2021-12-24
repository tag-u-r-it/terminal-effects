#include <random>

class Random_number
{
    public:

    int get_number(int seed, int min, int max)
    {
        static thread_local std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(min,max);
        return distribution(generator);
    }
};