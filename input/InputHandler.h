//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_INPUTHANDLER_H
#define TETRISCLONE_INPUTHANDLER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "Input.h"

class InputHandler
{

    sf::RenderWindow* pWindow;

public:
    explicit InputHandler(sf::RenderWindow* pWindow);

    Input poll();
};


#endif //TETRISCLONE_INPUTHANDLER_H
