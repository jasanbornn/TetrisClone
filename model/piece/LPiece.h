//
// Created by jamie on 11/15/22.
//

#ifndef TETRISCLONE_LPIECE_H
#define TETRISCLONE_LPIECE_H


#include "Piece.h"

class LPiece : public Piece
{
public:
    LPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
    void setPos(int row, int col) override;
    void resetTiles() override;
};


#endif //TETRISCLONE_LPIECE_H
