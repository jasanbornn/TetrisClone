//
// Created by jamie on 3/10/23.
//

#include <vector>
#include "Menu.h"

Menu::Menu()
{
    this->status = MENU_CLOSED;

    this->activeButton = -1;

    this->width = 0;
    this->height = 0;
}

Menu::Menu(unsigned int newWidth, unsigned int newHeight)
{
    this->status = MENU_CLOSED;

    this->activeButton = -1;

    this->width = newWidth;
    this->height = newHeight;
}

bool Menu::getStatus() const
{
    return this->status;
}

void Menu::setStatus(bool b)
{
    this->status = b;

    if (activeButton != -1)
    {
        resetActiveButton();
    }
}

void Menu::addButton(const Button& button)
{
    this->buttons.push_back(button);

    this->activeButton = 0;
    buttons[activeButton].setIsActive(true);
}

Button& Menu::getButton(int i)
{
    return buttons.at(i);
}

int Menu::getNumButtons() const
{
    return buttons.size();
}

unsigned int Menu::getWidth() const
{
    return this->width;
}

unsigned int Menu::getHeight() const
{
    return this->height;
}

void Menu::moveSelectionUp()
{
    buttons[activeButton].setIsActive(false);
    activeButton--;
    if (activeButton < 0)
    {
        activeButton = getNumButtons() - 1;
    }
    buttons[activeButton].setIsActive(true);
}

void Menu::moveSelectionDown()
{
    buttons[activeButton].setIsActive(false);
    activeButton++;
    if (activeButton > getNumButtons() - 1)
    {
        activeButton = 0;
    }
    buttons[activeButton].setIsActive(true);
}

void Menu::resetActiveButton()
{
    buttons[activeButton].setIsActive(false);
    activeButton = 0;
    buttons[activeButton].setIsActive(true);
}

void Menu::fireActiveButton()
{
    buttons[activeButton].fire();
}