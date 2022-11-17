//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_RENDERER_H
#define TETRISCLONE_RENDERER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "../model/control/GameState.h"

class Renderer
{
    sf::RenderWindow* pWindow;

    void drawTile(int typeType, int row, int col);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(GameState gameState);

    void drawPiece(Piece piece);


};


#endif //TETRISCLONE_RENDERER_H
