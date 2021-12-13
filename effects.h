#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>

#define Speed 250

#ifdef _WIN32
#define OS "windows"
#endif

#ifdef __linux__
#define OS "linux"
#endif

class Effects
{
    std::vector<std::vector<int>> matrix;

    void effect_sweep_horizontal()
    {
        for(int y = 0; y < matrix[0].size(); y++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
            for(int x = 0; x < matrix.size(); x++)
            {
                matrix[x][y] = 1;
                matrix[x][y-1] = 0;
                if(y == 0)
                {
                    matrix[x][-1] = 0;
                }
            }
        }
    }

    void effect_sweep_vertical()
    {
        for(int x = 0; x < matrix.size(); x++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
            for(int y = 0; y < matrix[0].size(); y++)
            {
                matrix[x][y] = 1;
                if(x > 0)
                {
                    matrix[x-1][y] = 0;
                }
                if(x == 0)
                {
                    //matrix[0].back or matrix[0][-1]? I can't decide
                    //Benchmark, anyone?
                    matrix[x].back() = 0;
                }
            }
        }
    }

    public:

    void init_matrix(int x, int y)
    {
        for (int i = 0; i < y; i++)
        {
            std::vector<int> chunk;
            for (int j = 0; j < x; j++)
            {
                chunk.push_back(0);
            }
            matrix.push_back(chunk);
        }
    }

    void draw_screen()
    {
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
            if(OS == "linux") system("clear");
            else if(OS == "windows") system("cls");

            //Last numbers in row and in line will be always 1.
            //That's why they need to be clipped out with matrix.size()-1
            for(int x = 0; x < matrix.size()-1; x++)
            {
                for(int y = 0; y < matrix[0].size()-1; y++) std::cout << matrix[x][y];
                std::cout << std::endl;
            }
        }
    }

    void random_effect(int index)
    {
        if(index == 0) effect_sweep_horizontal();
        if(index == 1) effect_sweep_vertical();
    }
};