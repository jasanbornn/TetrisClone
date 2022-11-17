//
// Created by jamie on 11/12/22.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Renderer.h"
#include "../WindowConstants.h"

#define BOARD_RENDER_WIDTH WINDOW_WIDTH / 3.f
#define TILE_RENDER_WIDTH (BOARD_RENDER_WIDTH / BOARD_WIDTH)

Renderer::Renderer(sf::RenderWindow* pWindow)
{
    this->pWindow = pWindow;
}

void Renderer::render(GameState gameState)
{
    Board board = gameState.getBoardState();
    Piece piece = gameState.getPieceState();

    // clear the window with black color
    pWindow->clear(sf::Color::White);

    // draw everything here...
    // window.draw(...);

    //Left border
    sf::RectangleShape leftBorder(sf::Vector2f(2.f, WINDOW_HEIGHT));
    leftBorder.setPosition(WINDOW_WIDTH / 2.f - BOARD_RENDER_WIDTH / 2, 0.f);
    leftBorder.setFillColor(sf::Color::Red);


    //Right border
    sf::RectangleShape rightBorder(sf::Vector2f(2.f, WINDOW_HEIGHT));
    rightBorder.setPosition(WINDOW_WIDTH / 2.f + BOARD_RENDER_WIDTH / 2, 0.f);
    rightBorder.setFillColor(sf::Color::Red);

    //Draw vertical grid lines
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(1.f, WINDOW_HEIGHT));
        gridLine.setPosition(WINDOW_WIDTH / 2.f - BOARD_RENDER_WIDTH / 2 + TILE_RENDER_WIDTH * i, 0.f);
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }

    //Draw horizontal grid lines
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(BOARD_RENDER_WIDTH, 1.f));
        gridLine.setPosition(WINDOW_WIDTH / 2.f - BOARD_RENDER_WIDTH / 2, TILE_RENDER_WIDTH * i);
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }


    pWindow->draw(leftBorder);
    pWindow->draw(rightBorder);


    //Draw active piece
    drawPiece(piece);

    // end the current frame
    pWindow->display();
}

void Renderer::drawTile(int tileType, int row, int col)
{
    if (row >= BOARD_HEIGHT || col >= BOARD_WIDTH || row < 0 || col < 0)
    {
        return;
    }

    sf::RectangleShape tile(sf::Vector2f(TILE_RENDER_WIDTH, TILE_RENDER_WIDTH));

    tile.setPosition((WINDOW_WIDTH / 2.f - BOARD_RENDER_WIDTH / 2.f) + TILE_RENDER_WIDTH * col,
                     TILE_RENDER_WIDTH * (row - BOARD_HEIGHT / 2.f));
    if (tileType == TILE_NULL)
    {
        tile.setFillColor(sf::Color::Transparent);
    } else
    {
        tile.setFillColor(sf::Color::Blue);
    }

    pWindow->draw(tile);
}

void Renderer::drawPiece(Piece piece)
{

    std::array<Tile, TILES_PER_PIECE> tiles = piece.getTiles();

    for (auto& tile: tiles)
    {
        drawTile(tile.getTileType(), tile.getRow(), tile.getCol());
    }

}




//    std::array<std::array<int,BOARD_WIDTH>,BOARD_HEIGHT> pieceData = piece.getData();
//
//    for (int row = BOARD_HEIGHT/2; row < BOARD_HEIGHT; row++)
//    {
//        for (int col = 0; col < BOARD_WIDTH; col++)
//        {
//            drawTile(pieceData.at(row).at(col),row,col);
//        }
//    }
//}