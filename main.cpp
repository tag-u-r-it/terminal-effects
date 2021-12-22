#include <iostream>
#include <thread>
#include <ctime>
#include <effects.h>
#include <random_number.h>


int main()
{
    Effects effects;

    int x_input, y_input;
    std::cout << "Width of matrix: ";
    std::cin >> x_input;
    y_input = x_input/2;
    effects.init_matrix(x_input, y_input);

    std::thread t1([&effects]{
            while(true)
            {
                effects.draw_screen();
            }
        });
        
    int threadCount = 4;
    Random_number rnd[threadCount];
    std::thread threads[threadCount];
    for(int i = 0; i < threadCount; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % Speed + Speed * 2));
        srand(time(NULL));
        threads[i] = std::thread([&effects, &rnd, &i]{
            while(true)
            {
                //8 possible effects
                int index = rand() % 8;
                //int index = rnd[i].get();
                effects.random_effect(index);
            }
        });
    }
    t1.join();

    return 0;
}