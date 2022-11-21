//
// Created by jamie on 11/13/22.
//

#include "GameState.h"


GameState::GameState()
{
    this->board = Board();
    this->piece = TPiece(20, 4);

//    Piece p = TPiece(30, 5);
//
//    board.addPiece(p);
//    board.addTile(Tile(TILE_RED, 35, 5));
}

GameState::GameState(Board board, Piece piece)
{
    this->board = board;
    this->piece = piece;

};

void GameState::setBoardState(Board newBoard)
{
    this->board = newBoard;
}

Board GameState::getBoardState()
{
    return this->board;
}

void GameState::setPieceState(Piece newPiece)
{
    this->piece = newPiece;
}

Piece GameState::getPieceState()
{
    return this->piece;
}


