//
// Created by jamie on 12/11/22.
//

#include "Holder.h"

Holder::Holder()
{

}

std::shared_ptr<Piece> Holder::hold(const std::shared_ptr<Piece>& pNewPiece)
{
    if (pHeldPiece != nullptr)
    {
        pHeldPiece->resetTiles();
    }
    std::shared_ptr<Piece> temp = pHeldPiece;
    pHeldPiece = pNewPiece;
    //Positions the held piece relative to the board so that it renders in the correct location.
    //Eventually this will be handled better and will be the Renderer's job.
    pHeldPiece->setPos(25,-5);
    return temp;
}

std::shared_ptr<Piece> Holder::getHeldPiece() const
{
    return this->pHeldPiece;
}
