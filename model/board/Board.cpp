//
// Created by jamie on 11/13/22.
//

#include "Board.h"
#include "../piece/Tile.h"

Board::Board()
{
    this->width = BOARD_WIDTH;
    this->height = BOARD_HEIGHT;

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            setData(TILE_NULL,i,j);
        }
    }
}

void Board::setData(int tile, int row, int col)
{
    this->data[row][col] = tile;
}
