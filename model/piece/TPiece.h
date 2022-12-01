//
// Created by jamie on 11/17/22.
//

#ifndef TETRISCLONE_TPIECE_H
#define TETRISCLONE_TPIECE_H


#include "Piece.h"

class TPiece : public Piece
{
public:
    TPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
};


#endif //TETRISCLONE_TPIECE_H
