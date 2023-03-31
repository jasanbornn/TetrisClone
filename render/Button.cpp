//
// Created by jamie on 3/25/23.
//

#include "Button.h"

#include <utility>

Button::Button(const std::string& startText, std::function<void(void)> action)
{
    this->text = startText;
    this->action = std::move(action);
    this->active = false;
}

void Button::setText(std::string newText)
{
    this->text = std::move(newText);
}

std::string Button::getText()
{
    return this->text;
}

void Button::fire()
{
    this->action();
}

void Button::setIsActive(bool isActive)
{
    this->active = isActive;
}

bool Button::isActive() const
{
    return this->active;
}