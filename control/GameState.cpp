//
// Created by jamie on 11/13/22.
//

#include "GameState.h"
#include "../WindowConstants.h"


#include <utility>
#include <iostream>
#include <valarray>

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


GameState::GameState(sf::RenderWindow* pWindow) : player1(PLAYER_ONE), player2(PLAYER_TWO)
{
    this->pWindow = pWindow;

    this->mode = MAIN_MENU;

    this->keyPressed = false;
    this->buttonPressed = false;
    this->joystickEngaged = false;

    this->gameOver = false;

    //Initialize main menu
    mainMenu = Menu((WINDOW_WIDTH / 4.0), (WINDOW_HEIGHT / 3.0));
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
    if (!gameOver)
    {

        if (this->mode == MAIN_MENU)
        {

        }

        if (this->mode == ONE_PLAYER_GAME)
        {
            if (pauseMenu.getStatus() == MENU_CLOSED)
            {
                if (pieceCanMove(player1, 1, 0))
                {
                    player1.restartGroundedClock();
                }
                else
                {
                    if (player1.getGroundedTime().asMilliseconds() > 500 && !player1.isDonePlaying())
                    {
                        placePiece(player1);
                    }
                }

                if (player1.getGravityTime().asMilliseconds() > player1.getGravityDelay())
                {
                    if (pieceCanMove(player1, 1, 0))
                    {
                        movePieceDown(player1.getPPiece());
                        player1.restartGravityClock();
                    }
                }
                updateGhostPiece(player1);
            }

            if (player1.isDonePlaying())
            {
                this->gameOver = true;
                this->gameOverDelayClock.restart();
            }

        }

        if (this->mode == TWO_PLAYER_GAME)
        {
            if (pauseMenu.getStatus() == MENU_CLOSED)
            {
                if (pieceCanMove(player1, 1, 0))
                {
                    player1.restartGroundedClock();
                }
                else
                {
                    if (player1.getGroundedTime().asMilliseconds() > 500 && !player1.isDonePlaying())
                    {
                        placePiece(player1);
                    }
                }

                if (player1.getGravityTime().asMilliseconds() > player1.getGravityDelay())
                {
                    if (pieceCanMove(player1, 1, 0))
                    {
                        movePieceDown(player1.getPPiece());
                        player1.restartGravityClock();
                    }
                }
                updateGhostPiece(player1);


                if (pieceCanMove(player2, 1, 0))
                {
                    player2.restartGroundedClock();
                }
                else
                {
                    if (player2.getGroundedTime().asMilliseconds() > 500 && !player2.isDonePlaying())
                    {
                        placePiece(player2);
                    }
                }

                if (player2.getGravityTime().asMilliseconds() > player2.getGravityDelay())
                {
                    if (pieceCanMove(player2, 1, 0))
                    {
                        movePieceDown(player2.getPPiece());
                        player2.restartGravityClock();
                    }
                }
                updateGhostPiece(player2);
            }

            if (player1.isDonePlaying() && player2.isDonePlaying())
            {
                this->gameOver = true;
                this->gameOverDelayClock.restart();
            }
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

sf::Time GameState::getGameOverDelayTime()
{
    this->gameOverDelayTime = gameOverDelayClock.getElapsedTime();
    return this->gameOverDelayTime;
}

bool GameState::isGameOver()
{
    return this->gameOver;
}

void GameState::startMainMenu()
{
    this->gameOver = false;
    mainMenu.setStatus(MENU_OPEN);
    pauseMenu.setStatus(MENU_CLOSED);
    this->setMode(MAIN_MENU);
}

void GameState::initOnePlayerGame()
{

    this->gameOver = false;

    player1 = Player(PLAYER_ONE);

    player1.restartGravityClock();
}

void GameState::startOnePlayerGame()
{
    initOnePlayerGame();
    this->setMode(ONE_PLAYER_GAME);
}

void GameState::startTwoPlayerGame()
{
    initOnePlayerGame();

    player2 = Player(PLAYER_TWO);

    player2.restartGravityClock();

    this->setMode(TWO_PLAYER_GAME);
}

void GameState::processInputs(const Input& input)
{
    std::vector<sf::Event> events = input.getEvents();
    bool singleInput = true;

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

                //Check for previously engaged joystick to avoid duplicate movement
                if (joystickEngaged)
                {
                    if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 0 &&
                        sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 0)
                    {
                        joystickEngaged = false;
                    }
                    else
                    {
                        break;
                    }
                }

                if (sf::Joystick::getAxisPosition(0, sf::Joystick::PovX) == 0 &&
                    sf::Joystick::getAxisPosition(0, sf::Joystick::PovY) == 0)
                {
                    joystickEngaged = false;
                }
                else
                {
                    joystickEngaged = true;
                }

                if (mode == ONE_PLAYER_GAME || mode == MAIN_MENU)
                {
                    runJoystickInputs(player1);
                }
                else if (mode == TWO_PLAYER_GAME)
                {
                    runJoystickInputs(player2);
                }


                break;
            case sf::Event::KeyPressed:

                if (gameOver)
                {
                    this->gameOverDelayTime = gameOverDelayClock.getElapsedTime();
                    if (gameOverDelayTime.asMilliseconds() > GAME_OVER_DELAY)
                    {
                        startMainMenu();
                        return;
                    }
                }

                if (!keyPressed)
                {
                    runKeyInputs(player1);
                    keyPressed = true;
                }
                break;

            case sf::Event::KeyReleased:
                keyPressed = false;
                break;

            case sf::Event::JoystickButtonPressed:

                if (gameOver)
                {
                    this->gameOverDelayTime = gameOverDelayClock.getElapsedTime();
                    if (gameOverDelayTime.asMilliseconds() > GAME_OVER_DELAY)
                    {
                        startMainMenu();
                        return;
                    }
                }

                if (mode == ONE_PLAYER_GAME || mode == MAIN_MENU)
                {
                    if (!buttonPressed)
                    {
                        runButtonInputs(player1);
                        buttonPressed = true;
                    }
                }
                else if (mode == TWO_PLAYER_GAME)
                {
                    if (!buttonPressed)
                    {
                        runButtonInputs(player2);
                        buttonPressed = true;
                    }
                }

                break;
            case sf::Event::JoystickButtonReleased:
                buttonPressed = false;
                break;
//            case sf::Event::JoystickMoved:
//                break;
//            case sf::Event::JoystickConnected:
//                break;
//            case sf::Event::JoystickDisconnected:
//                break;
//            case sf::Event::Count:
//                break;
        }
    }

    if (mode == ONE_PLAYER_GAME || mode == MAIN_MENU)
    {
        if (!this->keyPressed && !this->joystickEngaged)
        {
            player1.restartInputDelayClock();
        }
        else
        {
            sf::Time inputDelayTime = player1.getInputDelayTime();
            sf::Time inputRepeatTime = player1.getInputRepeatTime();

            if (inputDelayTime.asMilliseconds() > 200)
            {
                if (inputRepeatTime.asMilliseconds() > 50)
                {
                    runRepeatableKeyInputs(player1);
                    runRepeatableJoystickInputs(player1);
                    player1.restartInputRepeatClock();
                }
            }
        }
    }
    else if (mode == TWO_PLAYER_GAME)
    {
        if (!this->keyPressed)
        {
            player1.restartInputDelayClock();
        }
        else
        {
            sf::Time inputDelayTime = player1.getInputDelayTime();
            sf::Time inputRepeatTime = player1.getInputRepeatTime();

            if (inputDelayTime.asMilliseconds() > 200)
            {
                if (inputRepeatTime.asMilliseconds() > 50)
                {
                    runRepeatableKeyInputs(player1);
                    player1.restartInputRepeatClock();
                }
            }
        }

        if (!this->joystickEngaged)
        {
            player2.restartInputDelayClock();
        }
        else
        {
            sf::Time inputDelayTime = player2.getInputDelayTime();
            sf::Time inputRepeatTime = player2.getInputRepeatTime();

            if (inputDelayTime.asMilliseconds() > 200)
            {
                if (inputRepeatTime.asMilliseconds() > 50)
                {
                    runRepeatableJoystickInputs(player2);
                    player2.restartInputRepeatClock();
                }
            }
        }
    }
}

void GameState::runKeyInputs(Player& player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        pWindow->close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
    {
        toggleMenuAction();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        selectAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        rotateLeftAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        rotateRightAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        dropAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        holdAction(player);
    }

    runRepeatableKeyInputs(player);
}

void GameState::runRepeatableKeyInputs(Player& player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        upAction(player);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        downAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        leftAction(player);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        rightAction(player);
    }
}

void GameState::runButtonInputs(Player& player)
{
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
}

void GameState::runJoystickInputs(Player& player)
{
    runRepeatableJoystickInputs(player);
}

void GameState::runRepeatableJoystickInputs(Player& player)
{
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
}

void GameState::upAction(Player& player)
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

void GameState::downAction(Player& player)
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
            if (!player.isDonePlaying())
            {
                if (pieceCanMove(player, 1, 0))
                {
                    movePieceDown(player.getPPiece());
                    player.addToScore(10);
                }
                player.restartGravityClock();
            }
        }
    }
}

void GameState::leftAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (!player.isDonePlaying())
        {
            if (pieceCanMove(player, 0, -1))
            {
                movePieceLeft(player.getPPiece());
            }
        }
    }
}

void GameState::rightAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED)
    {
        if (!player.isDonePlaying())
        {
            if (pieceCanMove(player, 0, 1))
            {
                movePieceRight(player.getPPiece());
            }
        }
    }
}

void GameState::selectAction(Player& player)
{
    if (mode == MAIN_MENU)
    {
        if (mainMenu.getStatus() == MENU_OPEN)
        {
            mainMenu.fireActiveButton();
        }
    }

    if (mode == ONE_PLAYER_GAME || mode == TWO_PLAYER_GAME)
    {
        if (pauseMenu.getStatus() == MENU_OPEN)
        {
            pauseMenu.fireActiveButton();
        }
    }

}

void GameState::rotateLeftAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED && !player.isDonePlaying())
    {
        player.restartGroundedClock();
        if (!pieceCanMove(player, 1, 0))
        {
            tryRotatePieceLeft(player);
            if (pieceCanMove(player, 1, 0))
            {
                player.restartGravityClock();
            }
        }
        else
        {
            tryRotatePieceLeft(player);
        }
    }
}

void GameState::rotateRightAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED && !player.isDonePlaying())
    {
        player.restartGroundedClock();
        if (!pieceCanMove(player, 1, 0))
        {
            tryRotatePieceRight(player);
            if (pieceCanMove(player, 1, 0))
            {
                player.restartGravityClock();
            }
        }
        else
        {
            tryRotatePieceRight(player);
        }
    }
}

void GameState::dropAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED && !player.isDonePlaying())
    {
        dropPiece(player);
    }
}

void GameState::holdAction(Player& player)
{
    if (pauseMenu.getStatus() == MENU_CLOSED && !player.isDonePlaying())
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

Player& GameState::getPlayer1State()
{
    return this->player1;
}

Player& GameState::getPlayer2State()
{
    return this->player2;
}

Menu& GameState::getMenuState()
{
    if (mode == MAIN_MENU)
    {
        return this->mainMenu;
    }

    if (mode == ONE_PLAYER_GAME || mode == TWO_PLAYER_GAME)
    {
        return this->pauseMenu;
    }

    return this->mainMenu;
}

//unsigned long int GameState::getScoreState()
//{
//    return this->score;
//}
//
//unsigned long int GameState::getScore2State()
//{
//    return this->score2;
//}

void GameState::spawnNewPiece(Player& player)
{
    player.setPPiece(player.getNPQ().pop());
    player.getNPQ().push(player.getBag().getPiece());
    player.getHolder().enableHolding();

    if (pieceCollides(player))
    {
        player.setDonePlaying(true);
    }
}

bool GameState::pieceCanMove(Player& player, int dRow, int dCol)
{
    std::array<Tile, TILES_PER_PIECE> pieceTiles = player.getPPiece()->getTiles();
    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> boardTiles = player.getBoard().getTiles();

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

void GameState::movePieceLeft(const std::shared_ptr<Piece>& pPiece)
{
    pPiece->move(0, -1);
}

void GameState::movePieceRight(const std::shared_ptr<Piece>& pPiece)
{
    pPiece->move(0, 1);
}

void GameState::movePieceUp(const std::shared_ptr<Piece>& pPiece)
{
    pPiece->move(-1, 0);
}

void GameState::movePieceDown(const std::shared_ptr<Piece>& pPiece)
{
    pPiece->move(1, 0);
}

bool GameState::pieceCollides(Player& player)
{

    for (Tile& tile: player.getPPiece()->getTiles())
    {
        if (tile.getCol() < 0 || tile.getCol() >= BOARD_WIDTH || tile.getRow() < 0 || tile.getRow() >= BOARD_HEIGHT)
        {
            return true;
        }
        else if (player.getBoard().getTile(tile.getRow(), tile.getCol()).getTileType() != TILE_NULL)
        {
            return true;
        }
    }
    return false;
}

void GameState::placePiece(Player& player)
{

    for (Tile& tile: player.getPPiece()->getTiles())
    {
        player.getBoard().addTile(tile);
    }
    spawnNewPiece(player);
    int numLines = player.getBoard().clearLines();
    if (numLines > 0)
    {
        int addedScore = 500;
        for (int i = 0; i < numLines; i++)
        {
            addedScore = addedScore * 2;
        }
        player.addToScore(addedScore);
        player.addToLinesCleared(numLines);
    }
}

void GameState::dropPiece(Player& player)
{
    while (!pieceCollides(player))
    {
        movePieceDown(player.getPPiece());
        player.addToScore(25);
    }
    movePieceUp(player.getPPiece());
    placePiece(player);
}

void GameState::updateGhostPiece(Player& player)
{

    int dRow = 0;

    while (!pieceCollides(player))
    {
        player.getPPiece()->move(1, 0);
        dRow++;
    }
    player.getPPiece()->move(-1, 0);
    player.getGhostPiece().update(player.getPPiece()->getTiles());
    player.getPPiece()->move(-dRow + 1, 0);
}

void GameState::holdPiece(Player& player)
{
    if (player.getHolder().canHold())
    {
        player.setPPiece(player.getHolder().hold(player.getPPiece()));

        if (player.getPPiece() == nullptr)
        {
            spawnNewPiece(player);
        }

        player.getHolder().disableHolding();
    }
}


void GameState::tryRotatePieceLeft(Player& player)
{
    std::shared_ptr<Piece>& targetPiece = player.getPPiece();

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
        player.restartGravityClock();
    }
}

void GameState::tryRotatePieceRight(Player& player)
{
    std::shared_ptr<Piece>& targetPiece = player.getPPiece();

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
        player.restartGravityClock();
    }

}

void GameState::tryRotateIPieceLeft(Player& player)
{

    std::shared_ptr<Piece>& targetPiece = player.getPPiece();

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
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 1;
                        dCol = -3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = 3;
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
        case ROT_TWO:
            targetPiece->rotateLeft();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 2;
                        dCol = 3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = -3;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 1;
                                dCol = 2;
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
                dCol = 2;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -1;
                        dCol = 3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = -3;
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
    }

    if (dRow != 0)
    {
        player.restartGravityClock();
    }
}

void GameState::tryRotateIPieceRight(Player& player)
{
    std::shared_ptr<Piece>& targetPiece = player.getPPiece();

    int dRow = 0;
    int dCol = 0;

    switch (targetPiece->getRotation())
    {
        case ROT_ZERO:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = -2;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = 3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = 1;
                        dCol = -3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = -3;
                            dCol = 3;
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
        case ROT_LEFT:
            targetPiece->rotateRight();
            if (pieceCollides(player))
            {
                dRow = 0;
                dCol = 1;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -3;
                        dCol = 1;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 2;
                            dCol = 3;
                            targetPiece->move(dRow, dCol);
                            if (pieceCollides(player))
                            {
                                dRow = 1;
                                dCol = -2;
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
                dCol = 2;
                targetPiece->move(dRow, dCol);
                if (pieceCollides(player))
                {
                    dRow = 0;
                    dCol = -3;
                    targetPiece->move(dRow, dCol);
                    if (pieceCollides(player))
                    {
                        dRow = -1;
                        dCol = 3;
                        targetPiece->move(dRow, dCol);
                        if (pieceCollides(player))
                        {
                            dRow = 3;
                            dCol = -3;
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
        case ROT_RIGHT:
            targetPiece->rotateRight();
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
                                dRow = -1;
                                dCol = -2;
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
        player.restartGravityClock();
    }

}
