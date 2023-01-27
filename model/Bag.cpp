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
            return std::make_shared<IPiece>(20, 4);
        case S_PIECE:
            return std::make_shared<SPiece>(21, 4);
        case Z_PIECE:
            return std::make_shared<ZPiece>(21, 4);
        case L_PIECE:
            return std::make_shared<LPiece>(21, 4);
        case J_PIECE:
            return std::make_shared<JPiece>(21, 4);
        case O_PIECE:
            return std::make_shared<OPiece>(20, 4);
        case T_PIECE:
            return std::make_shared<TPiece>(21, 4);
    }
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

