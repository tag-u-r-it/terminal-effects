#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <ctime>

#define speed 250

class Effects
{
    std::vector<std::vector<int>> matrix;
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

    private:

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

    public:

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