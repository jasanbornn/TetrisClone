//
// Created by jamie on 11/15/22.
//

#include "LPiece.h"

LPiece::LPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_ORANGE, row, col);
    tiles[1] = Tile(TILE_ORANGE, row, col - 1);
    tiles[2] = Tile(TILE_ORANGE, row, col + 1);
    tiles[3] = Tile(TILE_ORANGE, row - 1, col + 1);
}