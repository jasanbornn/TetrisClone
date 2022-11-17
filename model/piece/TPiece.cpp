//
// Created by jamie on 11/17/22.
//

#include "TPiece.h"

TPiece::TPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_PURPLE, row, col);
    tiles[1] = Tile(TILE_PURPLE, row + 1, col);
    tiles[2] = Tile(TILE_PURPLE, row - 1, col);
    tiles[3] = Tile(TILE_PURPLE, row - 1, col - 1);
}