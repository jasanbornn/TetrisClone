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
#include "../board/Board.h"
#include "Tile.h"


class Piece
{


protected:

    int rotation;

    //Each piece will be made of 4 tiles (called tetrominos)
    std::array<Tile,TILES_PER_PIECE> tiles;


public:

    Piece(int xPos, int yPos);

    std::array<Tile,TILES_PER_PIECE>& getTiles();


    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    bool canMoveTo(int dRow, int dCol);


};


#endif //TETRISCLONE_PIECE_H
