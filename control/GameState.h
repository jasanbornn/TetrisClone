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
#include "../model/GhostPiece.h"
#include "../model/Holder.h"
#include "../input/Input.h"
#include "../render/Menu.h"
#include "../model/NextPieceQueue.h"
#include "../model/Player.h"

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define MAIN_MENU 0
#define ONE_PLAYER_GAME 1
#define TWO_PLAYER_GAME 2

#define GAME_OVER_DELAY 3000 //milliseconds



class GameState
{

    sf::RenderWindow* pWindow;
    int mode;

    Player player1;
    Player player2;

    Menu pauseMenu;
    Menu mainMenu;

    bool keyPressed;
    bool buttonPressed;
    bool joystickEngaged;

    bool gameOver;
    sf::Clock gameOverDelayClock;
    sf::Time gameOverDelayTime;


    void tryRotateIPieceLeft(Player& player);

    void tryRotateIPieceRight(Player& player);

    void initOnePlayerGame();

    void runRepeatableKeyInputs(Player& player);

    void runRepeatableJoystickInputs(Player& player);

    void runKeyInputs(Player& player);

    void runButtonInputs(Player& player);

    void runJoystickInputs(Player& player);

public:

    explicit GameState(sf::RenderWindow* pWindow);

    void update(const Input& input);

    void setMode(int newMode);

    int getMode() const;

    sf::Time getGameOverDelayTime();

    bool isGameOver();

    void startMainMenu();

    void startOnePlayerGame();

    void startTwoPlayerGame();

    void processInputs(const Input& input);

    Menu& getMenuState();

    Player& getPlayer1State();

    Player& getPlayer2State();

    void upAction(Player& player);

    void downAction(Player& player);

    void leftAction(Player& player);

    void rightAction(Player& player);

    void selectAction(Player& player);

    void rotateLeftAction(Player& player);

    void rotateRightAction(Player& player);

    void dropAction(Player& player);

    void holdAction(Player& player);

    void toggleMenuAction();

    void closeMenuAction();

    void spawnNewPiece(Player& player);

    bool pieceCanMove(Player& player, int dRow, int dCol);

    void movePieceLeft(const std::shared_ptr<Piece>& pPiece);

    void movePieceRight(const std::shared_ptr<Piece>& pPiece);

    void movePieceUp(const std::shared_ptr<Piece>& pPiece);

    void movePieceDown(const std::shared_ptr<Piece>& pPiece);

    void placePiece(Player& player);

    void dropPiece(Player& player);

    bool pieceCollides(Player& player);

    void tryRotatePieceLeft(Player& player);

    void tryRotatePieceRight(Player& player);

    void updateGhostPiece(Player& player);

    void holdPiece(Player& player);

};


#endif //TETRISCLONE_GAMESTATE_H
