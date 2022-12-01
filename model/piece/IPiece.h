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
};


#endif //TETRISCLONE_IPIECE_H
