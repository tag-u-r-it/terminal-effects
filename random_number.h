#include <random>
#include <chrono>

class Random_number
{
    public:

    int get() {
        typedef std::chrono::high_resolution_clock myclock;
        myclock::time_point beginning = myclock::now();
        myclock::duration d = myclock::now() - beginning;
        unsigned seed = d.count();

        static thread_local std::mt19937 generator(seed);
        std::uniform_int_distribution<int> distribution(0,7);
        return distribution(generator);
    }
};