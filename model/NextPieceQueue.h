//
// Created by jamie on 3/14/23.
//

#ifndef TETRISCLONE_NEXTPIECEQUEUE_H
#define TETRISCLONE_NEXTPIECEQUEUE_H


#include <memory>
#include "piece/Piece.h"

#define QUEUE_SIZE 3

class NextPieceQueue
{

    std::array<std::shared_ptr<Piece>,QUEUE_SIZE> pieces;

public:

    NextPieceQueue();

    void push(const std::shared_ptr<Piece>& pPiece);
    std::shared_ptr<Piece> pop();
    std::shared_ptr<Piece> peek(int index) const;

    bool isFull();
    int size() const;
};


#endif //TETRISCLONE_NEXTPIECEQUEUE_H
