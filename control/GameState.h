//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_GAMESTATE_H
#define TETRISCLONE_GAMESTATE_H


#include "../model/board/Board.h"
#include "../model/piece/Piece.h"
#include "../model/piece/OPiece.h"
#include "../model/piece/LPiece.h"

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
