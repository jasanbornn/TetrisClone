//
// Created by jamie on 11/16/22.
//

#ifndef TETRISCLONE_SPIECE_H
#define TETRISCLONE_SPIECE_H


#include "Piece.h"

class SPiece : public Piece
{
public:
    SPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
};


#endif //TETRISCLONE_SPIECE_H
