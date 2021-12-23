#include <random>
#include <chrono>

class Random_number
{
    public:

    int get_seed()
    {
        typedef std::chrono::high_resolution_clock myclock;
        myclock::time_point beginning = myclock::now();
        myclock::duration d = myclock::now() - beginning;
        unsigned seed = d.count();
        return seed;
    }

    int get_number(int seed)
    {

        static thread_local std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0,7);
        return distribution(generator);
    }
};