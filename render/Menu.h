//
// Created by jamie on 3/10/23.
//

#ifndef TETRISCLONE_MENU_H
#define TETRISCLONE_MENU_H

#include "Button.h"

#define MENU_CLOSED 0
#define MENU_OPEN 1


class Menu
{
    bool status;
    std::vector<Button> buttons;
    int activeButton;
    unsigned int width, height;

    void resetActiveButton();


public:

    Menu();

    Menu(unsigned int width, unsigned int height);

    bool getStatus() const;

    void setStatus(bool status);

    void addButton(const Button& button);

    Button& getButton(int i);

    int getNumButtons() const;

    unsigned int getWidth() const;

    unsigned int getHeight() const;

    void moveSelectionUp();

    void moveSelectionDown();

    void fireActiveButton();


};


#endif //TETRISCLONE_MENU_H
