//
// Created by jamie on 3/25/23.
//

#ifndef TETRISCLONE_BUTTON_H
#define TETRISCLONE_BUTTON_H


#include <string>
#include <functional>

class Button
{

    std::string text;
    std::function<void(void)> action;
    bool active;

public:

    explicit Button(const std::string& startText,std::function<void(void)> action);

    void setText(std::string text);
    std::string getText();
    void fire();
    void setIsActive(bool isActive);
    bool isActive() const;
};


#endif //TETRISCLONE_BUTTON_H
