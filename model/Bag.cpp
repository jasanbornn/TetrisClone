//
// Created by jamie on 12/1/22.
//

#include <cstdlib>
#include "Bag.h"


Bag::Bag()
{
    for (bool& b: pieces)
    {
        b = true;
    }
}

std::shared_ptr<Piece> Bag::getPiece()
{
    switch (choosePiece())
    {
        case I_PIECE:
            pPiece = std::shared_ptr<Piece>(new IPiece(20, 4));
            break;
        case J_PIECE:
            pPiece = std::shared_ptr<Piece>(new JPiece(21, 4));
            break;
        case L_PIECE:
            pPiece = std::shared_ptr<Piece>(new LPiece(21, 4));
            break;
        case S_PIECE:
            pPiece = std::shared_ptr<Piece>(new SPiece(21, 4));
            break;
        case Z_PIECE:
            pPiece = std::shared_ptr<Piece>(new ZPiece(21, 4));
            break;
        case T_PIECE:
            pPiece = std::shared_ptr<Piece>(new TPiece(21, 4));
            break;
        case O_PIECE:
            pPiece = std::shared_ptr<Piece>(new OPiece(20, 4));
            break;
    }
    return pPiece;
}

int Bag::choosePiece()
{
    {
        int allFalse = true;
        for (bool b: pieces)
        {
            if (b)
            {
                allFalse = false;
            }
        }

        if (allFalse)
        {
            for (bool& b: pieces)
            {
                b = true;
            }
        }
    }

    while (true)
    {
        int choice = rand() % BAG_SIZE;

        if (pieces[choice])
        {
            pieces[choice] = false;
            return choice;
        }
    }

}

