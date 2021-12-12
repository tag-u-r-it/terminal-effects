#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>

#define X 10
#define Y 20
#define speed 250
std::vector<std::vector<int>> matrix(X, std::vector<int>(Y, 0));

class Effects
{
    public:
    void effect_sweep_horizontal()
    {
        for(int y = 0; y < matrix[0].size(); y++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
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
            std::this_thread::sleep_for(std::chrono::milliseconds(speed));
            for(int y = 0; y < matrix[0].size(); y++)
            {
                matrix[x][y] = 1;
                if(x > 0)
                {
                    matrix[x-1][y] = 0;
                }
                if(x == 0)
                {
                    matrix[x].back() = 0;
                }
            }
        }
    }

    void draw_screen()
    {
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(60));
            system("clear");
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