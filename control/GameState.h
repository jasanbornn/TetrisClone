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

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define MAIN_MENU 0
#define ONE_PLAYER_GAME 1
#define TWO_PLAYER_GAME 2

#define PLAYER_ONE 1
#define PLAYER_TWO 2

class GameState
{

    sf::RenderWindow* pWindow;
    int mode;

    Menu pauseMenu;
    Menu mainMenu;

    sf::Clock clock;
    sf::Clock clock2;
    sf::Time gravityTime;
    sf::Time gravityTime2;
    Bag bag;
    Bag bag2;

    GhostPiece ghostPiece;
    GhostPiece ghostPiece2;
    Board board;
    Board board2;
    std::shared_ptr<Piece> pPiece;
    std::shared_ptr<Piece> pPiece2;
    Holder holder;
    Holder holder2;
    NextPieceQueue NPQ;
    NextPieceQueue NPQ2;


    void tryRotateIPieceLeft(int player);
    void tryRotateIPieceRight(int player);

    void initOnePlayerGame();

public:

    explicit GameState(sf::RenderWindow* pWindow);

    void update(const Input& input);

    void setMode(int newMode);
    int getMode() const;

    void startMainMenu();
    void startOnePlayerGame();
    void startTwoPlayerGame();

    void processInputs(const Input& input);

    Board& getBoardState();
    Board& getBoard2State();
    std::shared_ptr<Piece> getPieceState();
    std::shared_ptr<Piece> getPiece2State();
    GhostPiece& getGhostPieceState();
    GhostPiece& getGhostPiece2State();
    Holder& getHolderState();
    Holder& getHolder2State();
    NextPieceQueue& getNPQState();
    NextPieceQueue& getNPQ2State();
    Menu& getMenuState();

    void upAction(int player);
    void downAction(int player);
    void leftAction(int player);
    void rightAction(int player);
    void selectAction(int player);
    void rotateLeftAction(int player);
    void rotateRightAction(int player);
    void dropAction(int player);
    void holdAction(int player);
    void toggleMenuAction();
    void closeMenuAction();

    void spawnNewPiece(int player);

    bool pieceCanMove(int player, int dRow, int dCol);

    void movePieceLeft(int player);
    void movePieceRight(int player);
    void movePieceUp(int player);
    void movePieceDown(int player);

    void placePiece(int player);
    void dropPiece(int player);

    bool pieceCollides(int player);

    void tryRotatePieceLeft(int player);
    void tryRotatePieceRight(int player);

    void updateGhostPiece(int player);

    void holdPiece(int player);

};


#endif //TETRISCLONE_GAMESTATE_H
