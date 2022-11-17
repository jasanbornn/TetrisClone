//
// Created by jamie on 11/12/22.
//

#include <SFML/Window/Event.hpp>
#include "InputHandler.h"

InputHandler::InputHandler(sf::RenderWindow* pWindow)
{
    this->pWindow = pWindow;
}

Input InputHandler::poll()
{
    Input input;

    sf::Event event;
    while (pWindow->pollEvent(event))
    {
        input.addEvent(event);
    }

    return input;
}
