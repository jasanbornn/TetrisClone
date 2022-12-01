//
// Created by jamie on 11/16/22.
//

#ifndef TETRISCLONE_JPIECE_H
#define TETRISCLONE_JPIECE_H


#include "Piece.h"

class JPiece : public Piece
{
public:
    JPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
};


#endif //TETRISCLONE_JPIECE_H
