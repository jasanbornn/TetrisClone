//
// Created by jamie on 11/13/22.
//

#include "GameState.h"

#include <utility>


GameState::GameState()
{
    this->pBoard = std::make_shared<Board>();
    this->pPiece = std::make_shared<TPiece>(25,5);

}

GameState::GameState(std::shared_ptr<Board> pBoard, std::shared_ptr<Piece> pPiece)
{
    this->pBoard = std::move(pBoard);
    this->pPiece = std::move(pPiece);

};

void GameState::setBoardState(std::shared_ptr<Board> b)
{
    this->pBoard = std::move(b);
}

std::shared_ptr<Board> GameState::getBoardState()
{
    return this->pBoard;
}

void GameState::setPieceState(std::shared_ptr<Piece> p)
{
    this->pPiece = std::move(p);
}

std::shared_ptr<Piece> GameState::getPieceState()
{
    return this->pPiece;
}


