//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_GAMESTATE_H
#define TETRISCLONE_GAMESTATE_H


#include "../model/Board.h"
#include "../model/piece/Piece.h"
#include "../model/piece/OPiece.h"
#include "../model/piece/LPiece.h"
#include "../model/piece/TPiece.h"
#include "../model/piece/JPiece.h"
#include "../model/piece/IPiece.h"
#include "../model/piece/SPiece.h"
#include "../model/piece/ZPiece.h"
#include "../model/Bag.h"
#include "GhostPiece.h"

#include <memory>

class GameState
{
//    Board board;
//    Piece piece;

    Bag bag;
//    GhostPiece ghostPiece;

    std::shared_ptr<GhostPiece> pGhostPiece;
    std::shared_ptr<Board> pBoard;
    std::shared_ptr<Piece> pPiece;

    void tryRotateIPieceLeft();
    void tryRotateIPieceRight();

public:

    GameState();

    void setBoardState(std::shared_ptr<Board> pBoard);
    void setBoardState(Board board);

    std::shared_ptr<Board> getBoardState();
    std::shared_ptr<Piece> getPieceState();
    std::shared_ptr<GhostPiece> getGhostPieceState();

    void setPieceState(std::shared_ptr<Piece> pPiece);
    void newPieceState();

    bool pieceCanMove(int dRow, int dCol);

    void movePieceLeft();
    void movePieceRight();
    void movePieceUp();
    void movePieceDown();

    void placePiece();
    void dropPiece();

    bool pieceCollides();

    void tryRotatePieceLeft();
    void tryRotatePieceRight();

    void updateGhostPiece();

};


#endif //TETRISCLONE_GAMESTATE_H
