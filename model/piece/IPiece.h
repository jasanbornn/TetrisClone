//
// Created by jamie on 11/16/22.
//

#ifndef TETRISCLONE_IPIECE_H
#define TETRISCLONE_IPIECE_H


#include "Piece.h"

class IPiece : public Piece
{
public:
    IPiece(int row, int col);

    void rotateLeft() override;
    void rotateRight() override;
    void setPos(int row, int col) override;
    void resetTiles() override;
};


#endif //TETRISCLONE_IPIECE_H
