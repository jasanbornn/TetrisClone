//
// Created by jamie on 11/16/22.
//

#include "IPiece.h"

IPiece::IPiece(int row, int col) : Piece(row,col)
{
    /*
     * Tile number map
     *
     *  ####  1023
     *
     *
     */

    tiles[0] = Tile(TILE_CYAN, row, col);
    tiles[1] = Tile(TILE_CYAN, row, col - 1);
    tiles[2] = Tile(TILE_CYAN, row, col + 1);
    tiles[3] = Tile(TILE_CYAN, row, col + 2);
}

void IPiece::rotateLeft()
{

    Piece::rotateLeft();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_LEFT;
            tiles[0].move(1,0);
            tiles[1].move(2, 1);
            tiles[2].move(0, -1);
            tiles[3].move(-1, -2);
            break;
        case ROT_LEFT:
            rotation = ROT_TWO;
            tiles[0].move(0,1);
            tiles[1].move(-1,2);
            tiles[2].move(1,0);
            tiles[3].move(2,-1);
            break;
        case ROT_TWO:
            rotation = ROT_RIGHT;
            tiles[0].move(-1,0);
            tiles[1].move(-2,-1);
            tiles[2].move(0,1);
            tiles[3].move(1,2);
            break;
        case ROT_RIGHT:
            rotation = ROT_ZERO;
            tiles[0].move(0,-1);
            tiles[1].move(1,-2);
            tiles[2].move(-1,0);
            tiles[3].move(-2,1);
            break;
    }

}

void IPiece::rotateRight()
{
    Piece::rotateRight();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_RIGHT;
            tiles[0].move(0,1);
            tiles[1].move(-1,2);
            tiles[2].move(1,0);
            tiles[3].move(2,-1);
            break;
        case ROT_LEFT:
            rotation = ROT_ZERO;
            tiles[0].move(-1,0);
            tiles[1].move(-2, -1);
            tiles[2].move(0, 1);
            tiles[3].move(1, 2);
            break;
        case ROT_TWO:
            rotation = ROT_LEFT;
            tiles[0].move(0,-1);
            tiles[1].move(1,-2);
            tiles[2].move(-1,0);
            tiles[3].move(-2,1);
            break;
        case ROT_RIGHT:
            rotation = ROT_TWO;
            tiles[0].move(1,0);
            tiles[1].move(2,1);
            tiles[2].move(0,-1);
            tiles[3].move(-1,-2);
            break;
    }
}