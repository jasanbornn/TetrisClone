//
// Created by jamie on 5/5/23.
//

#ifndef TETRISCLONE_PLAYER_H
#define TETRISCLONE_PLAYER_H

#define PLAYER_ONE 1
#define PLAYER_TWO 2

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "NextPieceQueue.h"
#include "GhostPiece.h"
#include "Board.h"
#include "Holder.h"
#include "Bag.h"

class Player
{
    sf::Clock gravityClock;
    sf::Clock inputDelayClock;
    sf::Clock inputRepeatClock;
    sf::Time gravityTime;
    sf::Time inputDelayTime;
    sf::Time inputRepeatTime;

    unsigned long int score;
    unsigned long int linesCleared;
    unsigned long int level;
    unsigned long int gravityDelay;
    int playerNumber;
    bool donePlaying;
    Bag bag;
    GhostPiece ghostPiece;
    Board board;
    std::shared_ptr<Piece> pPiece;
    Holder holder;
    NextPieceQueue NPQ;

public:

    Player(int playerNumber);

    void addToScore(unsigned long int dScore);

    void addToLinesCleared(unsigned long int dLines);

    void restartGravityClock();

    void restartInputDelayClock();

    void restartInputRepeatClock();

    GhostPiece& getGhostPiece();

    Bag& getBag();

    Board& getBoard();

    std::shared_ptr<Piece>& getPPiece();

    Holder& getHolder();

    NextPieceQueue& getNPQ();

    unsigned long int getScore();

    unsigned long int getLevel();
    unsigned long int getLinesCleared();
    unsigned long int getGravityDelay();

    int getPlayerNumber() const;

    sf::Time& getGravityTime();

    sf::Time& getInputDelayTime();

    sf::Time& getInputRepeatTime();

    bool isDonePlaying();

    void setPPiece(std::shared_ptr<Piece> newPPiece);

    void setDonePlaying(bool b);
};


#endif //TETRISCLONE_PLAYER_H
