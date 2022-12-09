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

#define NULL_PIECE (-1)
#define I_PIECE 0
#define J_PIECE 1
#define L_PIECE 2
#define S_PIECE 3
#define Z_PIECE 4
#define T_PIECE 5
#define O_PIECE 6

#include <array>
#include "Tile.h"


class Piece
{

protected:

    int rotation, type;
    std::array<Tile, TILES_PER_PIECE> tiles;

public:

    Piece(int xPos, int yPos);

    std::array<Tile, TILES_PER_PIECE>& getTiles();
    int getRotation() const;
    int getType() const;

    void move(int dRow, int dCol);

    virtual void rotateLeft();
    virtual void rotateRight();

//    bool canMoveTo(int dRow, int dCol);


};


#endif //TETRISCLONE_PIECE_H
