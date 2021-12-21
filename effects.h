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

    void effect_spiral()
    {
        bool pos_left = true;
        bool pos_top = true;
        for(int x = 0; x < matrix.size(); x++)
        {
            //top-left -> top-right
            if(pos_left && pos_top)
            {
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    matrix[x][y] = 1;
                }
                pos_left = false;
                pos_top = true;
            }
            //top-right -> bottom-right
            if(!pos_left && pos_top)
            {
                for(int x2 = 0; x2 < matrix.size(); x2++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/5));
                    for(int y = 0; y < matrix[0].size()-x; y++)
                    {
                        if(x2+x < matrix.size()-1) matrix[x2+x].end()[-1-x] = 1;
                    }
                }
                pos_left = false;
                pos_top = false;
            }
            //bottom-right -> bottom-left
            if(!pos_left && !pos_top)
            {
                int pos_x = matrix.size()-x-1;
                for(int y = 0; y < matrix[0].size(); y++)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/10));
                    matrix[pos_x].end()[-y-1] = 1;
                }
                pos_left = true;
                pos_top = false;
            }
            //bottom-left -> top-left
            if(pos_left && !pos_top)
            {
                for(int x2 = matrix.size()-1; x2 > 0; x2--)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(Speed/5));
                    for(int y = 0; y < matrix[0].size(); y++)
                    {
                        matrix[x2][x] = 1;
                    }
                }
                pos_left = true;
                pos_top = true;
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
            for(int y = 0; y < matrix[0].size(); y++) std::cout << matrix[x][y];
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
        if(index == 6) effect_spiral();
    }
};