#include <iostream>
#include <thread>
#include <ctime>
#include <effects.h>
#include <random_number.h>

#ifdef __linux__
#include <sys/ioctl.h>
#include <unistd.h>
#endif

int main()
{
    Effects effects;

    int matrix_width, matrix_height;
    int threadCount;
    //OS defined in effects.h
    if(OS == "windows")
    {
        std::cout << "Width of matrix: ";
        std::cin >> matrix_width;
        matrix_height = matrix_width/2;
        threadCount = 4;
    }
    else if(OS == "linux")
    {
        try
        {
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        matrix_width = size.ws_col;
        matrix_height = size.ws_row;
        threadCount = std::thread::hardware_concurrency()-1;
        }
        catch(int myNum)
        {
            std::cout << "Windows" << std::endl;
        }
        
    }
    effects.init_matrix(matrix_width, matrix_height);

    std::thread t1([&effects]{
            while(true)
            {
                effects.draw_screen();
            }
        });
        
    //int threadCount = 4;
    Random_number rnd[threadCount];
    std::thread threads[threadCount];
    for(int i = 0; i < threadCount; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % Speed + Speed * 2));
        threads[i] = std::thread([&effects, &rnd, &i]{
            int thread_id = i;
            while(true)
            {
                int index = rnd[thread_id].get_number(thread_id, 0, 7);
                effects.random_effect(index);
            }
        });
    }
    t1.join();

    return 0;
}