//
// Created by jamie on 5/5/23.
//

#include "Player.h"

#include <utility>

Player::Player(int playerNumber)
{
    this->playerNumber = playerNumber;
    this->bag = Bag();
    this->board = Board();
    this->pPiece = bag.getPiece();
    this->ghostPiece = GhostPiece();
    this->holder = Holder();
    this->NPQ = NextPieceQueue();
    this->score = 0;
    this->donePlaying = false;

    for (int i = 0; i < NPQ.size(); i++)
    {
        NPQ.push(bag.getPiece());
    }
}

void Player::addToScore(unsigned long int dScore)
{
    this->score += dScore;
}

void Player::restartGravityClock()
{
    this->gravityClock.restart();
}

void Player::restartInputDelayClock()
{
    this->inputDelayClock.restart();
}

void Player::restartInputRepeatClock()
{
    this->inputRepeatClock.restart();
}

sf::Time& Player::getGravityTime()
{
    this->gravityTime = this->gravityClock.getElapsedTime();
    return gravityTime;
}

sf::Time& Player::getInputDelayTime()
{
    this->inputDelayTime = this->inputDelayClock.getElapsedTime();
    return inputDelayTime;
}

sf::Time& Player::getInputRepeatTime()
{
    this->inputRepeatTime = this->inputRepeatClock.getElapsedTime();
    return inputRepeatTime;
}

GhostPiece& Player::getGhostPiece()
{
    return ghostPiece;
}

Bag& Player::getBag()
{
    return this->bag;
}

Board& Player::getBoard()
{
    return board;
}

std::shared_ptr<Piece>& Player::getPPiece()
{
    return pPiece;
}

Holder& Player::getHolder()
{
    return holder;
}

NextPieceQueue& Player::getNPQ()
{
    return NPQ;
}

int Player::getPlayerNumber() const
{
    return playerNumber;
}

unsigned long int Player::getScore()
{
    return this->score;
}

bool Player::isDonePlaying()
{
    return this->donePlaying;
}

void Player::setPPiece(std::shared_ptr<Piece> newPPiece)
{
    this->pPiece = std::move(newPPiece);
}

void Player::setDonePlaying(bool b)
{
    this->donePlaying = b;
}
