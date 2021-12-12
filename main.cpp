#include <iostream>
#include <thread>
#include <ctime>
#include <effects.h>

int main()
{
    Effects effects;
    srand(time(NULL));

    std::thread t1([&effects]{
            effects.draw_screen();
        });
    int threadCount = 4;
    std::thread threads[threadCount];
    for(int i = 0; i < threadCount; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(speed + 500));
        threads[i] = std::thread([&effects]{
            while(true)
            {
                int index = rand() % 2;
                effects.random_effect(index);
            }
        });
    }

    t1.join();

    return 0;
}