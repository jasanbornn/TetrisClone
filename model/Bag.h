//
// Created by jamie on 12/1/22.
//

#ifndef TETRISCLONE_BAG_H
#define TETRISCLONE_BAG_H

#include <array>
#include <memory>
#include "piece/Piece.h"
#include "piece/OPiece.h"
#include "piece/LPiece.h"
#include "piece/TPiece.h"
#include "piece/JPiece.h"
#include "piece/IPiece.h"
#include "piece/SPiece.h"
#include "piece/ZPiece.h"

#define BAG_SIZE 7


class Bag
{
    std::array<bool,BAG_SIZE> pieces = {true, true, true, true, true, true, true}; // One bool for each type of piece. true = piece exists; false = piece is gone

    int choosePiece();

public:
    Bag();
    std::shared_ptr<Piece> getPiece();
};


#endif //TETRISCLONE_BAG_H
