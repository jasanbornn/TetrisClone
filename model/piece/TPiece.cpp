//
// Created by jamie on 11/17/22.
//

#include "TPiece.h"

TPiece::TPiece(int row, int col) : Piece(row, col)
{

    /*
     * Tile number map
     *
     *  #    3
     *  ###  102
     */
    tiles[0] = Tile(TILE_PURPLE, row, col);
    tiles[1] = Tile(TILE_PURPLE, row, col - 1);
    tiles[2] = Tile(TILE_PURPLE, row, col + 1);
    tiles[3] = Tile(TILE_PURPLE, row - 1, col);

    type = T_PIECE;
}

void TPiece::rotateLeft()
{

    Piece::rotateLeft();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_LEFT;
            tiles[1].move(1, 1);
            tiles[2].move(-1, -1);
            tiles[3].move(1, -1);
            break;
        case ROT_LEFT:
            rotation = ROT_TWO;
            tiles[1].move(-1, 1);
            tiles[2].move(1, -1);
            tiles[3].move(1, 1);
            break;
        case ROT_TWO:
            rotation = ROT_RIGHT;
            tiles[1].move(-1, -1);
            tiles[2].move(1, 1);
            tiles[3].move(-1, 1);
            break;
        case ROT_RIGHT:
            rotation = ROT_ZERO;
            tiles[1].move(1, -1);
            tiles[2].move(-1, 1);
            tiles[3].move(-1, -1);
            break;
    }

}

void TPiece::rotateRight()
{
    Piece::rotateRight();

    switch (rotation)
    {
        case ROT_ZERO:
            rotation = ROT_RIGHT;
            tiles[1].move(-1, 1);
            tiles[2].move(1, -1);
            tiles[3].move(1, 1);
            break;
        case ROT_LEFT:
            rotation = ROT_ZERO;
            tiles[1].move(-1, -1);
            tiles[2].move(1, 1);
            tiles[3].move(-1, 1);
            break;
        case ROT_TWO:
            rotation = ROT_LEFT;
            tiles[1].move(1, -1);
            tiles[2].move(-1, 1);
            tiles[3].move(-1, -1);
            break;
        case ROT_RIGHT:
            rotation = ROT_TWO;
            tiles[1].move(1, 1);
            tiles[2].move(-1, -1);
            tiles[3].move(1, -1);
            break;
    }
}

void TPiece::setPos(int row, int col)
{
    Piece::setPos(row, col);
    tiles[0] = Tile(TILE_PURPLE, row, col);
    tiles[1] = Tile(TILE_PURPLE, row, col - 1);
    tiles[2] = Tile(TILE_PURPLE, row, col + 1);
    tiles[3] = Tile(TILE_PURPLE, row - 1, col);
}

void TPiece::resetTiles()
{
    Piece::resetTiles();
    setPos(21,4);
}



