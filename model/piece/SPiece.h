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
    void setPos(int row, int col) override;
    void resetTiles() override;
};


#endif //TETRISCLONE_SPIECE_H
