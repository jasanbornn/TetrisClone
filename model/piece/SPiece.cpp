//
// Created by jamie on 11/16/22.
//

#include "SPiece.h"

SPiece::SPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_GREEN, row, col);
    tiles[1] = Tile(TILE_GREEN, row, col - 1);
    tiles[2] = Tile(TILE_GREEN, row - 1, col);
    tiles[3] = Tile(TILE_GREEN, row - 1, col + 1);
}