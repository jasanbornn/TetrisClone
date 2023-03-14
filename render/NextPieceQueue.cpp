//
// Created by jamie on 3/14/23.
//

#include "NextPieceQueue.h"


NextPieceQueue::NextPieceQueue()
{
    for (auto & piece : pieces)
    {
        piece = nullptr;
    }
}

bool NextPieceQueue::isFull()
{
    for (unsigned long int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i] == nullptr)
        {
            return false;
        }
    }
    return true;
}

int NextPieceQueue::size()
{
    return QUEUE_SIZE;
}

std::shared_ptr<Piece> NextPieceQueue::pop()
{
    std::shared_ptr<Piece> retPiece;

    retPiece = pieces[0];

    for (unsigned long int i = 0; i < pieces.size() - 1; i++)
    {
        pieces[i] = pieces[i + 1];
    }
    pieces[pieces.size() - 1] = nullptr;

    return retPiece;
}

std::shared_ptr<Piece> NextPieceQueue::peek(int index)
{
    return pieces[index];
}

void NextPieceQueue::push(std::shared_ptr<Piece> newPiece)
{
    for (unsigned long int i = 0; i < pieces.size(); i++)
    {
        if (pieces[i] == nullptr)
        {
            pieces[i] = newPiece;
            break;
        }
    }
}

