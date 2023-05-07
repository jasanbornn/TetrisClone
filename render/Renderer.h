//
// Created by jamie on 11/12/22.
//

#ifndef TETRISCLONE_RENDERER_H
#define TETRISCLONE_RENDERER_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../control/GameState.h"

class Renderer
{
    sf::RenderWindow* pWindow;
    sf::Font mainFont;

    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::IntRect logoBounds;

    void drawTile(Tile tile, float boardX);

    void drawTile(int tileType, float xPos, float yPos, float scale);

    void drawGhostTile(Tile tile, float boardX);

public:
    explicit Renderer(sf::RenderWindow* pWindow);

    void render(const GameState& gameState);

    void drawMainMenu(GameState gameState);

    void drawOnePlayerGame(GameState gameState);

    void drawTwoPlayerGame(GameState gameState);

    void drawBoard(const Board& board, float xPos, float yPos);

    void drawPiece(const std::shared_ptr<Piece>& piece, float boardX);

    void drawGhostPiece(const GhostPiece& ghostPiece, float boardX);

    void drawUIPiece(const std::shared_ptr<Piece>& pPiece, float pieceX, float pieceY, float scale);

    void drawPieceHolder(const Holder& holder, float boardX, int player);

    void drawNPQ(const NextPieceQueue& NPQ, float boardX, int mode, int player);

    void drawMenu(Menu& menu, float xPos, float yPos);

    void drawMenu(Menu& menu, float xPos, float yPos, bool drawBackground);

    void drawMainLogo(sf::IntRect logoBounds);

    void drawScore(unsigned long int score, float boardX, float boardBottomY);

    void drawLevelInfo(int mode, float board1X, Player& player);

    void drawGameOverSplash(GameState gameState, Player& player1, Player& player2);




};


#endif //TETRISCLONE_RENDERER_H
