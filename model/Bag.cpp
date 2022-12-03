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
        case 0:
            return std::make_shared<IPiece>(20, 4);
        case 1:
            return std::make_shared<SPiece>(21, 4);
        case 2:
            return std::make_shared<ZPiece>(21, 4);
        case 3:
            return std::make_shared<LPiece>(21, 4);
        case 4:
            return std::make_shared<JPiece>(21, 4);
        case 5:
            return std::make_shared<OPiece>(20, 4);
        case 6:
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

