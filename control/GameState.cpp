//
// Created by jamie on 11/13/22.
//

#include "GameState.h"


#include <utility>
#include <iostream>

#define BUTTON_A 0
#define BUTTON_B 1
#define BUTTON_X 2
#define BUTTON_Y 3
#define BUTTON_LBUMPER 4
#define BUTTON_RBUMPER 5
#define BUTTON_START 7
#define BUTTON_SELECT 8
#define LEFT_STICK_BUTTON 9
#define RIGHT_STICK_BUTTON 10


GameState::GameState(sf::RenderWindow* pWindow) : bag(), bag2()
{
    this->pWindow = pWindow;

    this->mode = MAIN_MENU;

    this->gravityTime = this->clock.getElapsedTime();

    this->board = Board();
    this->pPiece = bag.getPiece();
    this->ghostPiece = GhostPiece();
    this->holder = Holder();
    this->NPQ = NextPieceQueue();

    this->board2 = Board();
    this->pPiece2 = bag2.getPiece();
    this->ghostPiece2 = GhostPiece();
    this->holder2 = Holder();
    this->NPQ2 = NextPieceQueue();

    //Fill the Next Piece Queue
    for (int i = 0; i < NPQ.size(); i++)
    {
        NPQ.push(bag.getPiece());
    }

    //Fill 2nd player Next Piece Queue
    for (int i = 0; i < NPQ2.size(); i++)
    {
        NPQ2.push(bag2.getPiece());
    }

    //Initialize main menu
    mainMenu = Menu(500, 500);
    mainMenu.setStatus(MENU_OPEN);
    mainMenu.addButton(Button("SINGLE PLAYER", [this]() -> void
    {
        this->startOnePlayerGame();
    }));

    mainMenu.addButton(Button("TWO-PLAYER", [this]() -> void
    {
        mainMenu.setStatus(MENU_CLOSED);
        this->startTwoPlayerGame();
    }));

    mainMenu.addButton(Button("EXIT", [this]() -> void
    {
        this->pWindow->close();
    }));

    //Initialize pause menu
    pauseMenu = Menu(500, 400);
    pauseMenu.setStatus(MENU_CLOSED);
    pauseMenu.addButton(Button("RESUME", [this]() -> void
    {
        this->closeMenuAction();
    }));
    pauseMenu.addButton(Button("MAIN MENU", [this]() -> void
    {
        this->startMainMenu();
    }));

}

void GameState::update(const Input& input)
{

    if (this->mode == MAIN_MENU)
    {

    }

    if (this->mode == ONE_PLAYER_GAME)
    {
        if (pauseMenu.getStatus() == MENU_CLOSED)
        {
            gravityTime = clock.getElapsedTime();
            if (gravityTime.asSeconds() >= 1.0)
            {
                downAction(PLAYER_ONE);
            }
            updateGhostPiece(PLAYER_ONE);
        }
        else
        {
            //fix time bug
        }

    }

    if (this->mode == TWO_PLAYER_GAME)
    {
        if (pauseMenu.getStatus() == MENU_CLOSED)
        {
            gravityTime = clock.getElapsedTime();
            if (gravityTime.asSeconds() >= 1.0)
            {
                downAction(PLAYER_ONE);
            }
            updateGhostPiece(PLAYER_ONE);

            gravityTime2 = clock2.getElapsedTime();
            if (gravityTime2.asSeconds() >= 1.0)
            {
                downAction(PLAYER_TWO);
            }
            updateGhostPiece(PLAYER_TWO);
        }
    }

    processInputs(input);


}

void GameState::setMode(int newMode)
{
    this->mode = newMode;
}

int GameState::getMode() const
{
    return this->mode;
}

void GameState::startMainMenu()
{
    this->setMode(MAIN_MENU);
}

void GameState::initOnePlayerGame()
{
    this->board = Board();
    this->pPiece = bag.getPiece();
    this->ghostPiece = GhostPiece();
    this->holder = Holder();
    this->NPQ = NextPieceQueue();

    //Fill the Next Piece Queue
    for (int i = 0; i < NPQ.size(); i++)
    {
        NPQ.push(bag.getPiece());
    }

    clock.restart();
}

void GameState::startOnePlayerGame()
{
    initOnePlayerGame();
    this->setMode(ONE_PLAYER_GAME);
}

void GameState::startTwoPlayerGame()
{
    initOnePlayerGame();

    this->gravityTime2 = clock2.getElapsedTime();

    this->board2 = Board();
    this->pPiece2 = bag2.getPiece();
    this->ghostPiece2 = GhostPiece();
    this->holder2 = Holder();
    this->NPQ2 = NextPieceQueue();

    //Fill 2nd player Next Piece Queue
    for (int i = 0; i < NPQ2.size(); i++)
    {
        NPQ2.push(bag2.getPiece());
    }

    clock2.restart();

    this->setMode(TWO_PLAYER_GAME);
}

void GameState::processInputs(const Input& input)
{
    std::vector<sf::Event> events = input.getEvents();
    int player = PLAYER_ONE;

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

            case sf::Event::JoystickMoved:
                //Joystick axis events

                player = PLAYER_ONE;

                if (mode == TWO_PLAYER_GAME)
                {
                    player = PLAYER_TWO;
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) < 0)
                {
                    upAction(player);
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) > 0)
                {
                    downAction(player);
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) < 0)
                {
                    leftAction(player);
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) > 0)
                {
                    rightAction(player);
                }
                break;
            case sf::Event::KeyPressed:

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    pWindow->close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                {
                    toggleMenuAction();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    upAction(PLAYER_ONE);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    downAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    leftAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    rightAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    selectAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
                {
                    rotateLeftAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                {
                    rotateRightAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    dropAction(PLAYER_ONE);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                {
                    holdAction(PLAYER_ONE);
                }

                break;
//            case sf::Event::KeyReleased:
//                break;
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
            case sf::Event::JoystickButtonPressed:
//                if (sf::Joystick::isButtonPressed(0,0))
//                {
//                    pWindow->close();
//                }

                player = PLAYER_ONE;

                if (mode == TWO_PLAYER_GAME)
                {
                    player = PLAYER_TWO;
                }

                if (sf::Joystick::isButtonPressed(0, BUTTON_X))
                {
                    rotateLeftAction(player);
                }

                if (sf::Joystick::isButtonPressed(0, BUTTON_Y))
                {
                    rotateRightAction(player);
                }

                if (sf::Joystick::isButtonPressed(0, BUTTON_A))
                {
                    dropAction(player);
                    selectAction(player);
                }

                if (sf::Joystick::isButtonPressed(0, BUTTON_B))
                {
                    holdAction(player);
                }

                if (sf::Joystick::isButtonPressed(0, BUTTON_START))
                {
                    toggleMenuAction();
                }

                break;
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

void GameState::upAction(int player)
{
    if (mode == MAIN_MENU)
    {
        mainMenu.moveSelectionUp();
    }

    if (pauseMenu.getStatus() == MENU_OPEN)
    {
        pauseMenu.moveSelectionUp();
    }

}

void GameState::downAction(int player)
{
    if (mode == MAIN_MENU)
    {
        mainMenu.moveSelectionDown();
    }
    else //if in game
    {
        if (pauseMenu.getStatus() == MENU_OPEN)
        {
            pauseMenu.moveSelectionDown();
        }
        else //if in game and not paused
        {
            if (pieceCanMove(player, 1, 0))
            {
                movePieceDown(player);
            }

            if (player == PLAYER_ONE)
            {
                clock.restart();
            }
            else
            {
                clock2.restart();
            }
        }
    }
}

void GameState::leftAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (pieceCanMove(player, 0, -1))
        {
            movePieceLeft(player);
        }
    }
}

void GameState::rightAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (pieceCanMove(player, 0, 1))
        {
            movePieceRight(player);
        }
    }
}

void GameState::selectAction(int player)
{
    if (mode == MAIN_MENU)
    {
        if (mainMenu.getStatus() == MENU_OPEN)
        {
            mainMenu.fireActiveButton();
        }
    }

    if (mode == ONE_PLAYER_GAME)
    {
        if (pauseMenu.getStatus() == MENU_OPEN)
        {
            pauseMenu.fireActiveButton();
        }
    }

}

void GameState::rotateLeftAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (!pieceCanMove(player, 1, 0))
        {
            tryRotatePieceLeft(player);
            if (pieceCanMove(player, 1, 0))
            {
                clock.restart();
            }
        }
        else
        {
            tryRotatePieceLeft(player);
        }
    }
}

void GameState::rotateRightAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (!pieceCanMove(player, 1, 0))
        {
            tryRotatePieceRight(player);
            if (pieceCanMove(player, 1, 0))
            {
                clock.restart();
            }
        }
        else
        {
            tryRotatePieceRight(player);
        }
    }
}

void GameState::dropAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        dropPiece(player);
    }
}

void GameState::holdAction(int player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        holdPiece(player);
    }
}

void GameState::toggleMenuAction()
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        pauseMenu.setStatus(MENU_OPEN);
    }
    else
    {
        pauseMenu.setStatus(MENU_CLOSED);
    }
}

void GameState::closeMenuAction()
{
    pauseMenu.setStatus(MENU_CLOSED);
}

Board& GameState::getBoardState()
{
    return this->board;
}

Board& GameState::getBoard2State()
{
    return this->board2;
}

std::shared_ptr<Piece> GameState::getPieceState()
{
    return this->pPiece;
}

std::shared_ptr<Piece> GameState::getPiece2State()
{
    return this->pPiece2;
}

GhostPiece& GameState::getGhostPieceState()
{
    return this->ghostPiece;
}

GhostPiece& GameState::getGhostPiece2State()
{
    return this->ghostPiece2;
}

Holder& GameState::getHolderState()
{
    return this->holder;
}

Holder& GameState::getHolder2State()
{
    return this->holder2;
}

NextPieceQueue& GameState::getNPQState()
{
    return NPQ;
}

NextPieceQueue& GameState::getNPQ2State()
{
    return NPQ2;
}

Menu& GameState::getMenuState()
{
    if (mode == MAIN_MENU)
    {
        return this->mainMenu;
    }

    if (mode == ONE_PLAYER_GAME)
    {
        return this->pauseMenu;
    }

    return this->mainMenu;
}

void GameState::spawnNewPiece(int player)
{
    if (player == PLAYER_ONE)
    {
        pPiece = NPQ.pop();
        NPQ.push(bag.getPiece());
        holder.enableHolding();
    }
    else
    {
        pPiece2 = NPQ2.pop();
        NPQ2.push(bag2.getPiece());
        holder2.enableHolding();
    }

}

bool GameState::pieceCanMove(int player, int dRow, int dCol)
{
    std::array<Tile, TILES_PER_PIECE> pieceTiles = pPiece->getTiles();
    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> boardTiles = board.getTiles();
    if (player == PLAYER_TWO)
    {
        pieceTiles = pPiece2->getTiles();
        boardTiles = board2.getTiles();
    }

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

void GameState::movePieceLeft(int player)
{
    if (player == PLAYER_ONE)
    {
        pPiece->move(0, -1);
    }
    else
    {
        pPiece2->move(0, -1);
    }
}

void GameState::movePieceRight(int player)
{
    if (player == PLAYER_ONE)
    {
        pPiece->move(0, 1);
    }
    else
    {
        pPiece2->move(0, 1);
    }
}

void GameState::movePieceUp(int player)
{
    if (player == PLAYER_ONE)
    {
        pPiece->move(-1, 0);
    }
    else
    {
        pPiece2->move(-1, 0);
    }
}

void GameState::movePieceDown(int player)
{
    if (player == PLAYER_ONE)
    {
        pPiece->move(1, 0);
    }
    else
    {
        pPiece2->move(1, 0);
    }
}

bool GameState::pieceCollides(int player)
{
    std::shared_ptr<Piece> targetPiece = pPiece;
    Board targetBoard = board;
    if (player == PLAYER_TWO)
    {
        targetPiece = pPiece2;
        targetBoard = board2;
    }

    for (Tile& tile: targetPiece->getTiles())
    {
        if (tile.getCol() < 0 || tile.getCol() >= BOARD_WIDTH || tile.getRow() < 0 || tile.getRow() >= BOARD_HEIGHT)
        {
            return true;
        }
        else if (targetBoard.getTile(tile.getRow(), tile.getCol()).getTileType() != TILE_NULL)
        {
            return true;
        }
    }
    return false;
}

void GameState::placePiece(int player)
{
    std::shared_ptr<Piece>* targetPiece = &pPiece;
    Board* targetBoard = &board;
    if (player == PLAYER_TWO)
    {
        targetPiece = &pPiece2;
        targetBoard = &board2;
    }

    for (Tile& tile: targetPiece->get()->getTiles())
    {
        targetBoard->addTile(tile);
    }
    spawnNewPiece(player);
    targetBoard->clearLines();
}

void GameState::dropPiece(int player)
{
    while (!pieceCollides(player))
    {
        movePieceDown(player);
    }
    movePieceUp(player);
    placePiece(player);
}

void GameState::updateGhostPiece(int player)
{
    std::shared_ptr<Piece>* targetPiece = &pPiece;
    GhostPiece* targetGhostPiece = &ghostPiece;
    if (player == PLAYER_TWO)
    {
        targetPiece = &pPiece2;
        targetGhostPiece = &ghostPiece2;
    }

    int dRow = 0;

    while (!pieceCollides(player))
    {
        targetPiece->get()->move(1, 0);
        dRow++;
    }
    targetPiece->get()->move(-1, 0);
    targetGhostPiece->update(targetPiece->get()->getTiles());
    targetPiece->get()->move(-dRow + 1, 0);
}

void GameState::holdPiece(int player)
{
    std::shared_ptr<Piece>* targetPiece = &pPiece;
    Holder* targetHolder = &holder;

    if (player == PLAYER_TWO)
    {
        targetPiece = &pPiece2;
        targetHolder = &holder2;
    }

    if (targetHolder->canHold())
    {
        *targetPiece = targetHolder->hold(*targetPiece);

        if (*targetPiece == nullptr)
        {
            spawnNewPiece(player);
        }

        targetHolder->disableHolding();
    }
}


void GameState::tryRotatePieceLeft(int player)
{
    std::shared_ptr<Piece> targetPiece = pPiece;
    if (player == PLAYER_TWO)
    {
        targetPiece = pPiece2;
    }

    if (targetPiece->getType() == I_PIECE)
    {
        tryRotateIPieceLeft(player);
        return;
    }

    int dRow = 0;
    int dCol = 0;

    switch (targetPiece->getRotation())
    {
        case ROT_ZERO:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = -1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 3;
                        dCol = -1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = 1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = -2;
                                dCol = -1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = 1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = -1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 2;
                                dCol = 1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = -1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 3;
                        dCol = 1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = -1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = -2;
                                dCol = 1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = -1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = 1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 2;
                                dCol = -1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateRight();
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

void GameState::tryRotatePieceRight(int player)
{
    std::shared_ptr<Piece> targetPiece = pPiece;
    if (player == PLAYER_TWO)
    {
        targetPiece = pPiece2;
    }

    if (targetPiece->getType() == I_PIECE)
    {
        tryRotateIPieceRight(player);
        return;
    }

    int dRow = 0;
    int dCol = 0;

    switch (targetPiece->getRotation())
    {
        case ROT_ZERO:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = -1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 3;
                        dCol = 1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = -1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = -2;
                                dCol = 1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = 1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = -1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 2;
                                dCol = 1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_TWO:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = -1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 3;
                        dCol = -1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = 1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = -2;
                                dCol = -1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateLeft();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_RIGHT:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 1;
                    dCol = 0;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = -1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 0;
                            dCol = 1;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 2;
                                dCol = -1;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateLeft();
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

void GameState::tryRotateIPieceLeft(int player)
{

    std::shared_ptr<Piece> targetPiece = pPiece;
    if (player == PLAYER_TWO)
    {
        targetPiece = pPiece2;
    }

    int dRow = 0;
    int dCol = 0;

    switch (targetPiece->getRotation())
    {
        case ROT_ZERO:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = 3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -2;
                        dCol = -3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = 3;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 1;
                                dCol = -2;
                                targetPiece->move(dRow, dCol);
                                targetPiece->rotateRight();
                            }
                        }
                    }
                }
            }
            break;
        case ROT_LEFT:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -2;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 1;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 2;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 2;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -1;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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

void GameState::tryRotateIPieceRight(int player)
{
    std::shared_ptr<Piece> targetPiece = pPiece;
    if (player == PLAYER_TWO)
    {
        targetPiece = pPiece2;
    }

    int dRow = 0;
    int dCol = 0;

    switch (pPiece->getRotation())
    {
        case ROT_ZERO:
            pPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -2;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 1;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = 1;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 2;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 2;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -1;
                        dCol = 3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = -3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -1;
                pPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = 3;
                    pPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -2;
                        dCol = -3;
                        pPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = 3;
                            pPiece->move(dRow, dCol);
                            if (pieceCollides(player))
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
