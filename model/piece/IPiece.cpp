//
// Created by jamie on 11/16/22.
//

#include "IPiece.h"

IPiece::IPiece(int row, int col) : Piece(row,col)
{
    tiles[0] = Tile(TILE_CYAN, row, col);
    tiles[1] = Tile(TILE_CYAN, row, col - 1);
    tiles[2] = Tile(TILE_CYAN, row, col + 1);
    tiles[3] = Tile(TILE_CYAN, row, col + 2);
}