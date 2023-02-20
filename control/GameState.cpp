//
// Created by jamie on 11/13/22.
//

#include "GameState.h"


#include <utility>


GameState::GameState(sf::RenderWindow* pWindow) : bag()
{
    this->pWindow = pWindow;

    this->time = this->clock.getElapsedTime();

    this->pBoard = std::make_shared<Board>();
    this->pPiece = bag.getPiece();
    this->pGhostPiece = std::make_shared<GhostPiece>();
    this->pHolder = std::make_shared<Holder>();

    this->canHoldPiece = true;
}

void GameState::update(Input input)
{
    time = clock.getElapsedTime();
    if (time.asSeconds() >= 1.0)
    {
        if (pieceCanMove(1, 0))
        {
            movePieceDown();
        }
        clock.restart();
    }

    processInputs(input);

    updateGhostPiece();

}

void GameState::processInputs(const Input& input)
{
    std::vector<sf::Event> events = input.getEvents();

    for (int i = 0; i < events.size(); i++)
    {
        switch (events.at(i).type)
        {
            case sf::Event::Closed:
                pWindow->close();
                break;
//            case sf::Event::Resized:
//                break;
//            case sf::Event::LostFocus:
//                break;
//            case sf::Event::GainedFocus:
//                break;
//            case sf::Event::TextEntered:
//                break;
            case sf::Event::KeyPressed:

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    pWindow->close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    if (pieceCanMove(1, 0))
                    {
                        movePieceDown();
                    }
                    clock.restart();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if (pieceCanMove(0, -1))
                    {
                        movePieceLeft();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if (pieceCanMove(0, 1))
                    {
                        movePieceRight();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    if (!pieceCanMove(1, 0))
                    {
                        tryRotatePieceLeft();
                        if (pieceCanMove(1, 0))
                        {
                            clock.restart();
                        }
                    }
                    else
                    {
                        tryRotatePieceLeft();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                {
                    if (!pieceCanMove(1, 0))
                    {
                        tryRotatePieceRight();
                        if (pieceCanMove(1, 0))
                        {
                            clock.restart();
                        }
                    }
                    else
                    {
                        tryRotatePieceRight();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    dropPiece();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    holdPiece();
                }

                break;
            case sf::Event::KeyReleased:
                break;
//            case sf::Event::MouseWheelMoved:
//                break;
//            case sf::Event::MouseWheelScrolled:
//                break;
//            case sf::Event::MouseButtonPressed:
//                break;
//            case sf::Event::MouseButtonReleased:
//                break;
//            case sf::Event::MouseMoved:
//                break;
//            case sf::Event::MouseEntered:
//                break;
//            case sf::Event::MouseLeft:
//                break;
//            case sf::Event::JoystickButtonPressed:
//                break;
//            case sf::Event::JoystickButtonReleased:
//                break;
//            case sf::Event::JoystickMoved:
//                break;
//            case sf::Event::JoystickConnected:
//                break;
//            case sf::Event::JoystickDisconnected:
//                break;
//            case sf::Event::TouchBegan:
//                break;
//            case sf::Event::TouchMoved:
//                break;
//            case sf::Event::TouchEnded:
//                break;
//            case sf::Event::SensorChanged:
//                break;
//            case sf::Event::Count:
//                break;
        }
    }
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

std::shared_ptr<Holder> GameState::getHolderState()
{
    return this->pHolder;
}

void GameState::spawnNewPiece()
{
    this->pPiece = bag.getPiece();
    canHoldPiece = true;
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
    spawnNewPiece();
    pBoard->clearLines();
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

void GameState::holdPiece()
{
    if (canHoldPiece)
    {
        pPiece = pHolder->hold(pPiece);

        if (pPiece == nullptr)
        {
            spawnNewPiece();
        }

        canHoldPiece = false;
    }
}


void GameState::tryRotatePieceLeft()
{
    if (pPiece->getType() == I_PIECE)
    {
        tryRotateIPieceLeft();
        return;
    }

    int dRow = 0;
    int dCol = 0;

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = -1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 3;
                        dCol = -1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = 1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = -1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = -1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = -1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -3;
                        dCol = -1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = 1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
    }

    if (dRow != 0)
    {
        clock.restart();
    }
}

void GameState::tryRotatePieceRight()
{
    if (pPiece->getType() == I_PIECE)
    {
        tryRotateIPieceRight();
        return;
    }

    int dRow = 0;
    int dCol = 0;

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = -1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = -1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = -1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = -1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 3;
                        dCol = -1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = 1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 1;
                    dCol = 0;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -3;
                        dCol = -1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 0;
                            dCol = 1;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
    }

    if (dRow != 0)
    {
        clock.restart();
    }

}

void GameState::tryRotateIPieceLeft()
{

    int dRow = 0;
    int dCol = 0;

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateLeft();
            if (pieceCollides())
            {
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 3;
                        dCol = -1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = -2;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -1;
                                dCol = 2;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = -2;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 1;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = -3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 2;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = -3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 1;
                                dCol = 2;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 2;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -1;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
                                pPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
    }

    if (dRow != 0)
    {
        clock.restart();
    }
}

void GameState::tryRotateIPieceRight()
{

    int dRow = 0;
    int dCol = 0;

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateRight();
            if (pieceCollides())
            {
                dRow = 0;
                dCol = -2;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = 1;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = -3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = -1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 2;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 1;
                                dCol = -2;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = 2;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -1;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = 2;
                                dCol = 1;
                                pPiece->move(dRow, dCol);
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
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides())
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides())
                    {
                        dRow = -2;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides())
                        {
                            dRow = 3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides())
                            {
                                dRow = -1;
                                dCol = -2;
                                pPiece->move(dRow, dCol);
                                pPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
    }

    if (dRow != 0)
    {
        clock.restart();
    }

}
