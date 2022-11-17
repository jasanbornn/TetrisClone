//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_GAMESTATE_H
#define TETRISCLONE_GAMESTATE_H


#include "../board/Board.h"
#include "../piece/Piece.h"
#include "../piece/OPiece.h"
#include "../piece/LPiece.h"

class GameState
{
    Board board;
    Piece piece = LPiece(20,5);

public:

    GameState();

    GameState(Board board, Piece piece);

    void setBoardState(Board newBoard);

    Board getBoardState();

    void setPieceState(Piece newPiece);

    Piece getPieceState();
};


#endif //TETRISCLONE_GAMESTATE_H
