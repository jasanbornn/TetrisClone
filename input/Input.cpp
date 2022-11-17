//
// Created by jamie on 11/12/22.
//

#include "Input.h"

Input::Input() = default;

void Input::addEvent(sf::Event event)
{
    this->events.push_back(event);
}

std::vector<sf::Event> Input::getEvents() const
{
    return this->events;
}
