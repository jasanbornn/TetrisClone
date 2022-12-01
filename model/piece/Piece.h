//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_PIECE_H
#define TETRISCLONE_PIECE_H

#define TILES_PER_PIECE 4

//Rotation states
#define ROT_ZERO 0
#define ROT_RIGHT 1
#define ROT_TWO 2
#define ROT_LEFT 3

#include <array>
#include "Tile.h"


class Piece
{

protected:

    int rotation;
    std::array<Tile, TILES_PER_PIECE> tiles;

public:

    Piece(int xPos, int yPos);

    std::array<Tile, TILES_PER_PIECE>& getTiles();

    void moveDown();

    void moveLeft();

    void moveRight();

    virtual void rotateLeft();
    virtual void rotateRight();

//    bool canMoveTo(int dRow, int dCol);


};


#endif //TETRISCLONE_PIECE_H
