//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_BOARD_H
#define TETRISCLONE_BOARD_H

#include <vector>

#define BOARD_HEIGHT 40
#define BOARD_WIDTH 10



class Board
{
    int width;
    int height;

    int data[BOARD_HEIGHT][BOARD_WIDTH];

    void setData(int tile, int row, int col);

public:
    Board();
};


#endif //TETRISCLONE_BOARD_H
