#include <random>

class Random_number
{
    public:

    int get_number(int seed)
    {
        static thread_local std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0,7);
        return distribution(generator);
    }
};