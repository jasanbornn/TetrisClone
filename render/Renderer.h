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

    void drawTile(Tile tile, bool isGhost, bool override);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(GameState gameState);

    void drawBackground();

    void drawBoard(const std::shared_ptr<Board>& board);

    void drawPiece(const std::shared_ptr<Piece>& piece);

    void drawPiece(const std::shared_ptr<Piece>& piece, bool override);

    void drawGhostPiece(const std::shared_ptr<GhostPiece>& ghostPiece);

    void drawUIPiece(const std::shared_ptr<Piece>& piece, float xPos, float yPos);

    void drawHeldPiece(const std::shared_ptr<Holder>& holder);


};


#endif //TETRISCLONE_RENDERER_H
