#include <iostream>
#include <chrono>
#include <vector>

int Speed = 250;

#ifdef _WIN32
#define OS "windows"
#include <windows.h>
#endif

#ifdef __linux__
#define OS "linux"
#endif

class Effects
{
    std::vector<std::vector<int>> matrix;

    void effect_horizontal()
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

    void effect_horizontal_reverse()
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

    void effect_vertical()
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

    void effect_vertical_reverse()
    {
        for(int x = matrix.size() -1; x >= 0; x--)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
            for(int y = 0; y < matrix[0].size(); y++)
            {
                matrix[x][y] = 1;
                if(x < matrix.size()-1) matrix[x+1][y] = 0;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
        for(int x = matrix.size() -1; x >= 0; x--)
        {
            for(int y = 0; y < matrix[0].size(); y++)
            {
                matrix.front()[y] = 0;
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
                    if(matrix[x][y] == 0) matrix[x][y] = 1;
                    else matrix[x][y] = 0;
                }
                pos_left = false;
            }
            else
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    if(matrix[x].end()[-y-1] == 0) matrix[x].end()[-y-1] = 1;
                    else matrix[x].end()[-y-1] = 0;
                }
                pos_left = true;                
            }
        }
    }

    void effect_snake_reverse()
    {
        bool pos_left = true;
        for(int x = matrix.size() -1 ; x >= 0; x--)
        {
            if(pos_left)
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    if(matrix[x][y] == 0) matrix[x][y] = 1;
                    else matrix[x][y] = 0;
                }
                pos_left = false;
            }
            else
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    if(matrix[x].end()[-y-1] == 0) matrix[x].end()[-y-1] = 1;
                    else matrix[x].end()[-y-1] = 0;
                }
                pos_left = true;                
            }
        }  
    }

    void effect_bounce()
    {
        bool direction_down = true;
        int x_pos = 0;
        int y_pos = 0;
        while(y_pos < matrix[0].size()-1)
        {
            if(direction_down)
            {
                for(int x = 0; x < matrix.size(); x++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
                    if(x+x_pos < matrix.size())
                    {
                        if(matrix[x+x_pos][y_pos] == 0) matrix[x+x_pos][y_pos] = 1;
                        else matrix[x+x_pos][y_pos] = 0;
                    }
                    y_pos += 1;
                }
                direction_down = false;
            }
            else
            {
                x_pos += 1;
                for(int x = matrix.size()-1; x > 0; x--)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
                    if(x < matrix.size())
                    {
                        if(matrix[x][y_pos] == 0) matrix[x][y_pos] = 1;
                        else matrix[x][y_pos] = 0;
                    }
                    y_pos += 1;
                }
                direction_down = true;
            }
        }
    }

    void effect_bounce_reverse()
    {
        bool direction_down = false;
        int x_pos = 0;
        int y_pos = 0;
        while(y_pos < matrix[0].size()-1)
        {
            if(direction_down)
            {
                for(int x = 0; x < matrix.size(); x++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
                    if(x+x_pos < matrix.size())
                    {
                        if(matrix[x+x_pos][y_pos] == 0) matrix[x+x_pos][y_pos] = 1;
                        else matrix[x+x_pos][y_pos] = 0;
                    }
                    y_pos += 1;
                }
                direction_down = false;
            }
            else
            {
                x_pos += 1;
                for(int x = matrix.size()-1; x > 0; x--)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed));
                    if(x < matrix.size())
                    {
                        if(matrix[x][y_pos] == 0) matrix[x][y_pos] = 1;
                        else matrix[x][y_pos] = 0;
                    }
                    y_pos += 1;
                }
                direction_down = true;
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
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        if(OS == "linux") system("clear");
        else if(OS == "windows") system("cls");
        for(int x = 0; x < matrix.size(); x++)
        {
            for(int y = 0; y < matrix[0].size(); y++)
            {
                if (matrix[x][y] == 1) std::cout << "\x1B[31m" << matrix[x][y] << "\033[0m";
                else std::cout << matrix[x][y];
            }
            std::cout << std::endl;
        }
    }

    void random_effect(int index)
    {
        if(index == 0) effect_horizontal();
        if(index == 1) effect_horizontal_reverse();
        if(index == 2) effect_vertical();
        if(index == 3) effect_vertical_reverse();
        if(index == 4) effect_snake();
        if(index == 5) effect_snake_reverse();
        if(index == 6) effect_bounce();
        if(index == 7) effect_bounce_reverse();
    }
};