#include <random>

class Random_number
{
    public:
    int get() {
        static thread_local std::mt19937 generator;
        std::uniform_int_distribution<int> distribution(0,7);
        return distribution(generator);
    }
};