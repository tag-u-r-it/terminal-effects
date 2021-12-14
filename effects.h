#include <iostream>
#include <chrono>
#include <vector>

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
            }
            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
        for(int y = 0; y < matrix[0].size(); y++)
        {
            for(int x = 0; x < matrix.size(); x++)
            {
                matrix[x].back() = 0;
            }
        }
    }

    void effect_sweep_horizontal_reverse()
    {
        for(int y = 0; y < matrix[0].size(); y++)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
            for(int x = 0; x < matrix.size(); x++)
            {
                matrix[x].end()[-y-1] = 1;
                matrix[x].end()[-y] = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
        for(int y = 0; y < matrix[0].size(); y++)
        {
            for(int x = 0; x < matrix.size(); x++)
            {
                matrix[x].front() = 0;
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
                if(x > 0) matrix[x-1][y] = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
        for(int x = 0; x < matrix.size(); x++)
        {
            for(int y = 0; y < matrix[0].size(); y++)
            {
                matrix.back()[y] = 0;
            }
        }
    }

    void effect_snake()
    {
        bool pos_left = true;
        for(int x = 0; x < matrix.size(); x++)
        {
            if(pos_left)
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    matrix[x][y] = 1;
                }
                pos_left = false;
            }
            else
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    matrix[x].end()[-y-1] = 1;
                }
                pos_left = true;                
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
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
        if(OS == "linux") system("clear");
        else if(OS == "windows") system("cls");

        for(int x = 0; x < matrix.size(); x++)
        {
            for(int y = 0; y < matrix[0].size(); y++) std::cout << matrix[x][y];
            std::cout << std::endl;
        }
    }

    void random_effect(int index)
    {
        if(index == 0) effect_sweep_horizontal();
        if(index == 1) effect_sweep_horizontal_reverse();
        if(index == 2) effect_sweep_vertical();
        if(index == 3) effect_snake();        
    }
};