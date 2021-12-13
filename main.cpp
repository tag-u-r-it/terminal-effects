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
    x_input = x_input+1;
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
                //2 possible effects
                int index = rand() % 2;
                effects.random_effect(index);
            }
        });
    }

    //Line 19 really wants this
    t1.join();

    return 0;
}