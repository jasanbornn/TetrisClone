//
// Created by jamie on 11/15/22.
//

#ifndef TETRISCLONE_OPIECE_H
#define TETRISCLONE_OPIECE_H


#include "Piece.h"

class OPiece : public Piece
{
public:

    OPiece(int row, int col);
    void setPos(int row, int col) override;
    void resetTiles() override;
};


#endif //TETRISCLONE_OPIECE_H
