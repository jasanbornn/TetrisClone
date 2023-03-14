//
// Created by jamie on 3/10/23.
//

#ifndef TETRISCLONE_MENU_H
#define TETRISCLONE_MENU_H

#define MENU_CLOSED 0
#define MENU_OPEN 1


class Menu
{
    bool status;

public:

    Menu();

    bool getStatus() const;
    void setStatus(bool status);
};


#endif //TETRISCLONE_MENU_H
