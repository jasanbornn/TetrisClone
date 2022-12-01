//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_GAMESTATE_H
#define TETRISCLONE_GAMESTATE_H


#include "../model/board/Board.h"
#include "../model/piece/Piece.h"
#include "../model/piece/OPiece.h"
#include "../model/piece/LPiece.h"
#include "../model/piece/TPiece.h"
#include <memory>

class GameState
{
//    Board* pBoard;
//    Piece* pPiece;

    std::shared_ptr<Board> pBoard;
    std::shared_ptr<Piece> pPiece;
public:

    GameState();

    GameState(std::shared_ptr<Board> pBoard, std::shared_ptr<Piece> pPiece);

    void setBoardState(std::shared_ptr<Board> pBoard);

    std::shared_ptr<Board> getBoardState();

    void setPieceState(std::shared_ptr<Piece> pPiece);

    std::shared_ptr<Piece> getPieceState();
};


#endif //TETRISCLONE_GAMESTATE_H
