//
// Created by jamie on 3/14/23.
//

#ifndef TETRISCLONE_NEXTPIECEQUEUE_H
#define TETRISCLONE_NEXTPIECEQUEUE_H


#include <memory>
#include "../model/piece/Piece.h"

#define QUEUE_SIZE 3

class NextPieceQueue
{

    std::array<std::shared_ptr<Piece>,QUEUE_SIZE> pieces;

public:

    NextPieceQueue();

    void push(std::shared_ptr<Piece> piece);
    std::shared_ptr<Piece> pop();
    std::shared_ptr<Piece> peek(int index);

    bool isFull();
    int size();
};


#endif //TETRISCLONE_NEXTPIECEQUEUE_H
