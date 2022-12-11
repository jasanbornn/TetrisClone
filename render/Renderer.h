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
    void drawTile(Tile tile, bool isGhost);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(GameState gameState);

    void drawBoard(const std::shared_ptr<Board>& board);
    void drawPiece(const std::shared_ptr<Piece>& piece);
    void drawGhostPiece(const std::shared_ptr<GhostPiece>& ghostPiece);


};


#endif //TETRISCLONE_RENDERER_H
