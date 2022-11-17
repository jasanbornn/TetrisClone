//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_INPUT_H
#define TETRISCLONE_INPUT_H


#include <vector>
#include <SFML/Window/Event.hpp>

class Input
{
    std::vector<sf::Event> events;
    std::vector<sf::Keyboard::Key> keyPresses;

public:
    Input();

    void addEvent(sf::Event event);

    std::vector<sf::Event> getEvents() const;

};


#endif //TETRISCLONE_INPUT_H
