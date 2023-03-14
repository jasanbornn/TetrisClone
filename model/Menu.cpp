//
// Created by jamie on 3/10/23.
//

#include "Menu.h"


Menu::Menu()
{
    this->status = MENU_CLOSED;
}

bool Menu::getStatus() const
{
    return this->status;
}

void Menu::setStatus(bool b)
{
    this->status = b;
}