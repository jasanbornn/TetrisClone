//
// Created by jamie on 12/11/22.
//

#ifndef TETRISCLONE_HOLDER_H
#define TETRISCLONE_HOLDER_H


#include <memory>
#include "piece/Piece.h"

class Holder
{
    std::shared_ptr<Piece> pHeldPiece = nullptr;
    bool holdingEnabled;

public:

    Holder();

    std::shared_ptr<Piece> hold(const std::shared_ptr<Piece>& p);

    std::shared_ptr<Piece> getHeldPiece() const;

    bool canHold() const;
    void disableHolding();
    void enableHolding();
};


#endif //TETRISCLONE_HOLDER_H
