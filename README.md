# terminal-effects
Practicing c++, matrices and threading. Tested on Linux and Windows (version 1511 or higher required for ANSI escape code). This program runs much smoother on Linux terminal compared to Windows cmd.

## Linux
Maximum number of threads are working on this program. Maximum thread count - 1 is altering the matrix, the last thread is drawing the matrix.

Size of the matrix will be defined by the size of the terminal.

## Windows
4 cpu threads are altering the matrix, creating the "effects", while the 5th thread is drawing the matrix.

Size of the matrix will be defined by the user.

## TODO
* Bounce reverse doesn't go all the way up
* Create draw_matrix.h