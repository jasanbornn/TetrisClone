//
// Created by jamie on 11/16/22.
//

#include "JPiece.h"

JPiece::JPiece(int row, int col) : Piece(row,col)
{

    /*
     * Tile number map
     *
     *   #    3
     *   ###  102
     *
     */

    tiles[0] = Tile(TILE_BLUE, row, col);
    tiles[1] = Tile(TILE_BLUE, row, col - 1);
    tiles[2] = Tile(TILE_BLUE, row, col + 1);
    tiles[3] = Tile(TILE_BLUE, row - 1, col - 1);

    type = J_PIECE;
}

void JPiece::rotateLeft()
{

    Piece::rotateLeft();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_LEFT;
            tiles[1].move(1, 1);
            tiles[2].move(-1, -1);
            tiles[3].move(2, 0);
            break;
        case ROT_LEFT:
            rotation = ROT_TWO;
            tiles[1].move(-1, 1);
            tiles[2].move(1, -1);
            tiles[3].move(0, 2);
            break;
        case ROT_TWO:
            rotation = ROT_RIGHT;
            tiles[1].move(-1, -1);
            tiles[2].move(1, 1);
            tiles[3].move(-2, 0);
            break;
        case ROT_RIGHT:
            rotation = ROT_ZERO;
            tiles[1].move(1, -1);
            tiles[2].move(-1, 1);
            tiles[3].move(0, -2);
            break;
    }

}

void JPiece::rotateRight()
{
    Piece::rotateRight();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_RIGHT;
            tiles[1].move(-1, 1);
            tiles[2].move(1, -1);
            tiles[3].move(0, 2);
            break;
        case ROT_LEFT:
            rotation = ROT_ZERO;
            tiles[1].move(-1, -1);
            tiles[2].move(1, 1);
            tiles[3].move(-2, 0);
            break;
        case ROT_TWO:
            rotation = ROT_LEFT;
            tiles[1].move(1, -1);
            tiles[2].move(-1, 1);
            tiles[3].move(0, -2);
            break;
        case ROT_RIGHT:
            rotation = ROT_TWO;
            tiles[1].move(1, 1);
            tiles[2].move(-1, -1);
            tiles[3].move(2, 0);
            break;
    }
}