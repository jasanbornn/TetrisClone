//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_RENDERER_H
#define TETRISCLONE_RENDERER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include "../control/GameState.h"

class Renderer
{
    sf::RenderWindow* pWindow;

    void drawTile(Tile tile);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(GameState gameState);

    void drawPiece(Piece piece);

    void drawBoard(Board board);
};


#endif //TETRISCLONE_RENDERER_H
