//
// Created by jamie on 11/13/22.
//

#include "GameState.h"


#include <utility>


GameState::GameState() : bag()
{
    this->pBoard = std::make_shared<Board>();
    this->pPiece = bag.getPiece();
    this->pGhostPiece = std::make_shared<GhostPiece>();
}

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

std::shared_ptr<GhostPiece> GameState::getGhostPieceState()
{
    return this->pGhostPiece;
}

void GameState::newPieceState()
{
    this->pPiece = bag.getPiece();
}

bool GameState::pieceCanMove(int dRow, int dCol)
{
    std::array<Tile, TILES_PER_PIECE> pieceTiles = pPiece->getTiles();
    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> boardTiles = pBoard->getTiles();
    for (int i = 0; i < TILES_PER_PIECE; i++)
    {
        if (pieceTiles[i].getCol() + dCol > BOARD_WIDTH - 1 || pieceTiles[i].getCol() + dCol < 0)
        {
            return false;
        }

        if (pieceTiles[i].getRow() + dRow > BOARD_HEIGHT - 1 || pieceTiles[i].getRow() + dRow < 0)
        {
            return false;
        }

        if (boardTiles[pieceTiles[i].getRow() + dRow][pieceTiles[i].getCol() + dCol].getTileType() != TILE_NULL)
        {
            return false;
        }

    }
    return true;
}

void GameState::movePieceLeft()
{
    pPiece->move(0, -1);
}

void GameState::movePieceRight()
{
    pPiece->move(0, 1);
}

void GameState::movePieceUp()
{
    pPiece->move(-1, 0);
}

void GameState::movePieceDown()
{
    pPiece->move(1, 0);
}

bool GameState::pieceCollides()
{
    for (Tile& tile: pPiece->getTiles())
    {
        if (tile.getCol() < 0 || tile.getCol() >= BOARD_WIDTH || tile.getRow() < 0 || tile.getRow() >= BOARD_HEIGHT)
        {
            return true;
        }
        else if (pBoard->getTile(tile.getRow(), tile.getCol()).getTileType() != TILE_NULL)
        {
            return true;
        }
    }
    return false;
}

void GameState::placePiece()
{
    for (Tile& tile: pPiece->getTiles())
    {
        pBoard->addTile(tile);
    }
    newPieceState();
}

void GameState::dropPiece()
{
    while (!pieceCollides())
    {
        movePieceDown();
    }
    movePieceUp();
    placePiece();
}

void GameState::updateGhostPiece()
{
    int dRow = 0;

    while (!pieceCollides())
    {
        pPiece->move(1, 0);
        dRow++;
    }
    pPiece->move(-1, 0);
    pGhostPiece->update(pPiece->getTiles());
    pPiece->move(-dRow + 1, 0);
}


void GameState::tryRotatePieceLeft()
{
    if (pPiece->getType() == I_PIECE)
    {
        tryRotateIPieceLeft();
        return;
    }

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(-1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(3, -1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, 1);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, -1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(-3, 1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, -1);
                            if (pieceCollides())
                            {
                                pPiece->move(2, 1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(-1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(3, 1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, -1);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, 1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(-3, -1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, 1);
                            if (pieceCollides())
                            {
                                pPiece->move(2, -1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
    }
}

void GameState::tryRotatePieceRight()
{
    if (pPiece->getType() == I_PIECE)
    {
        tryRotateIPieceRight();
        return;
    }

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(-1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(3, 1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, -1);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, 1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(-3, 1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, -1);
                            if (pieceCollides())
                            {
                                pPiece->move(2, 1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(-1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(3, -1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, 1);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, -1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(1, 0);
                    if (pieceCollides())
                    {
                        pPiece->move(-3, -1);
                        if (pieceCollides())
                        {
                            pPiece->move(0, 1);
                            if (pieceCollides())
                            {
                                pPiece->move(2, -1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
    }
}

void GameState::tryRotateIPieceLeft()
{
    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(0, 3);
                    if (pieceCollides())
                    {
                        pPiece->move(3, -1);
                        if (pieceCollides())
                        {
                            pPiece->move(-2, -3);
                            if (pieceCollides())
                            {
                                pPiece->move(-1, 2);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, -2);
                if (pieceCollides())
                {
                    pPiece->move(0, 3);
                    if (pieceCollides())
                    {
                        pPiece->move(1, -3);
                        if (pieceCollides())
                        {
                            pPiece->move(-3, 3);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, -1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(0, -3);
                    if (pieceCollides())
                    {
                        pPiece->move(2, 3);
                        if (pieceCollides())
                        {
                            pPiece->move(-3, -3);
                            if (pieceCollides())
                            {
                                pPiece->move(1, 2);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                pPiece->move(0, 2);
                if (pieceCollides())
                {
                    pPiece->move(0, -3);
                    if (pieceCollides())
                    {
                        pPiece->move(-1, 3);
                        if (pieceCollides())
                        {
                            pPiece->move(3, -3);
                            if (pieceCollides())
                            {
                                pPiece->move(-2, 1);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
    }
}

void GameState::tryRotateIPieceRight()
{
    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, -2);
                if (pieceCollides())
                {
                    pPiece->move(0, 3);
                    if (pieceCollides())
                    {
                        pPiece->move(1, -3);
                        if (pieceCollides())
                        {
                            pPiece->move(-3, 3);
                            if (pieceCollides())
                            {
                                pPiece->move(2, -1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, 1);
                if (pieceCollides())
                {
                    pPiece->move(0, -3);
                    if (pieceCollides())
                    {
                        pPiece->move(-3, 1);
                        if (pieceCollides())
                        {
                            pPiece->move(2, 3);
                            if (pieceCollides())
                            {
                                pPiece->move(1, -2);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, 2);
                if (pieceCollides())
                {
                    pPiece->move(0, -3);
                    if (pieceCollides())
                    {
                        pPiece->move(-1, 3);
                        if (pieceCollides())
                        {
                            pPiece->move(3, -3);
                            if (pieceCollides())
                            {
                                pPiece->move(2, 1);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                pPiece->move(0, -1);
                if (pieceCollides())
                {
                    pPiece->move(0, 3);
                    if (pieceCollides())
                    {
                        pPiece->move(-2, -3);
                        if (pieceCollides())
                        {
                            pPiece->move(3, 3);
                            if (pieceCollides())
                            {
                                pPiece->move(-1, -2);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
    }
}
