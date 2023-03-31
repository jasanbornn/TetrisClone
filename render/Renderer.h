//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_RENDERER_H
#define TETRISCLONE_RENDERER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include "../control/GameState.h"

class Renderer
{
    sf::RenderWindow* pWindow;
    sf::Font mainFont;

    void drawTile(Tile tile);

    void drawTile(int tileType, float xPos, float yPos, float scale);

    void drawGhostTile(Tile tile);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(const GameState& gameState);

    void drawMainMenu(GameState gameState);
    void drawOnePlayerGame(GameState gameState);
    void drawTwoPlayerGame();

    void drawBoard(const Board& board);

    void drawPiece(const std::shared_ptr<Piece>& piece);

    void drawGhostPiece(const GhostPiece& ghostPiece);

    void drawUIPiece(const std::shared_ptr<Piece>& pPiece, float xPos, float yPos, float scale);

    void drawPieceHolder(const Holder& holder);

    void drawNPQ(const NextPieceQueue& NPQ);

    void drawMenu(Menu& menu);


};


#endif //TETRISCLONE_RENDERER_H
