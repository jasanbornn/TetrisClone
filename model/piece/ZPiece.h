//
// Created by jamie on 11/16/22.
//

#ifndef TETRISCLONE_ZPIECE_H
#define TETRISCLONE_ZPIECE_H


#include "Piece.h"

class ZPiece : public Piece
{
public:
    ZPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
};

#endif //TETRISCLONE_ZPIECE_H
