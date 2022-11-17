//
// Created by jamie on 11/15/22.
//

#include "OPiece.h"

OPiece::OPiece(int row, int col) : Piece(row, col)
{
    tiles[0] = Tile(TILE_YELLOW, row, col);
    tiles[1] = Tile(TILE_YELLOW, row, col + 1);
    tiles[2] = Tile(TILE_YELLOW, row + 1, col);
    tiles[3] = Tile(TILE_YELLOW, row + 1, col + 1);
}
