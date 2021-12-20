#include <iostream>
#include <thread>
#include <ctime>
#include <effects.h>

int main()
{
    Effects effects;

    int x_input, y_input;
    std::cout << "Width of matrix: ";
    std::cin >> x_input;
    y_input = x_input/2;
    effects.init_matrix(x_input, y_input);

    srand(time(NULL));

    std::thread t1([&effects]{
            while(true)
            {
                effects.draw_screen();
            }
        });
        
    int threadCount = 4;
    std::thread threads[threadCount];
    for(int i = 0; i < threadCount; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % Speed + Speed * 2));
        threads[i] = std::thread([&effects]{
            while(true)
            {
                //7 possible effects
                int index = rand() % 7;
                effects.random_effect(index);
            }
        });
    }
    t1.join();

    return 0;
}