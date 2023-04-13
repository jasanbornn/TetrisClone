//
// Created by jamie on 12/11/22.
//

#include "Holder.h"

Holder::Holder()
{
    holdingEnabled = true;
}

std::shared_ptr<Piece> Holder::hold(const std::shared_ptr<Piece>& pNewPiece)
{
    pNewPiece->resetTiles();
    std::shared_ptr<Piece> temp = pHeldPiece;
    pHeldPiece = pNewPiece;
    return temp;
}

std::shared_ptr<Piece> Holder::getHeldPiece() const
{
    return this->pHeldPiece;
}

bool Holder::canHold() const
{
    return holdingEnabled;
}

void Holder::disableHolding()
{
    this->holdingEnabled = false;
}

void Holder::enableHolding()
{
    this->holdingEnabled = true;
}