//
// Created by jamie on 11/16/22.
//

#include "ZPiece.h"

ZPiece::ZPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_RED, row, col);
    tiles[1] = Tile(TILE_RED, row + 1, col);
    tiles[2] = Tile(TILE_RED, row - 1, col);
    tiles[3] = Tile(TILE_RED, row - 1, col - 1);
}