//
// Created by jamie on 11/13/22.
//

#ifndef TETRISCLONE_UPDATER_H
#define TETRISCLONE_UPDATER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "../input/Input.h"
#include "../model/board/Board.h"
#include "../model/piece/Piece.h"
#include "GameState.h"

class Updater
{

    sf::RenderWindow* pWindow;
    GameState gameState;

public:

    explicit Updater(sf::RenderWindow* pWindow);

    GameState update(const Input& input);

    bool pieceCanMove(Piece piece, int dRow, int dCol);
};


#endif //TETRISCLONE_UPDATER_H
