//
// Created by jamie on 11/16/22.
//

#include "JPiece.h"

JPiece::JPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_BLUE, row, col);
    tiles[1] = Tile(TILE_BLUE, row, col - 1);
    tiles[2] = Tile(TILE_BLUE, row, col + 1);
    tiles[3] = Tile(TILE_BLUE, row + 1, col + 1);
}