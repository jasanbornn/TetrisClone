//
// Created by jamie on 11/12/22.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Renderer.h"
#include "../WindowConstants.h"

#define BOARD_RENDER_HEIGHT (WINDOW_HEIGHT / 1.2)
#define BOARD_RENDER_WIDTH (BOARD_RENDER_HEIGHT / 2.0)
#define TILE_RENDER_WIDTH (BOARD_RENDER_WIDTH / BOARD_WIDTH)
#define TILE_RENDER_HEIGHT (BOARD_RENDER_HEIGHT / (BOARD_HEIGHT / 2))

Renderer::Renderer(sf::RenderWindow* pWindow)
{
    this->pWindow = pWindow;
}

void Renderer::render(GameState gameState)
{
    std::shared_ptr<Board> pBoard = gameState.getBoardState();
    std::shared_ptr<Piece> pPiece = gameState.getPieceState();
    std::shared_ptr<GhostPiece> pGhostPiece = gameState.getGhostPieceState();
    std::shared_ptr<Holder> pHolder = gameState.getHolderState();
    std::shared_ptr<Menu> pMenu = gameState.getMenuState();

    //Clear the window with white color
    pWindow->clear(sf::Color::White);

    //Draw background
//    drawBackground();

    //Draw board pieces
    drawBoard(pBoard);

    //Draw ghost piece
    drawGhostPiece(pGhostPiece);

    //Draw active piece
    drawPiece(pPiece);

    //Draw piece holder
    drawPieceHolder(pHolder);

    //Draw the menu
    drawMenu(pMenu);


    //End the current frame
    pWindow->display();
}

void Renderer::drawTile(Tile tile)
{
    int row = tile.getRow();
    int col = tile.getCol();
    int tileType = tile.getTileType();

    float xPos = (WINDOW_WIDTH / 2.f) - (BOARD_RENDER_WIDTH / 2.f) + (TILE_RENDER_WIDTH * col);
    float yPos = (WINDOW_HEIGHT / 2.f) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * (row - 20));

    drawTile(tileType, xPos, yPos, 1.0);
}

void Renderer::drawTile(int tileType, float xPos, float yPos, float scale)
{
    sf::Vector2f tileRenderV(TILE_RENDER_WIDTH * scale, TILE_RENDER_HEIGHT * scale);
    sf::RectangleShape tileRender(tileRenderV);
    tileRender.setPosition(xPos, yPos);

    switch (tileType)
    {
        case TILE_NULL:
            tileRender.setFillColor(sf::Color::Transparent);
            break;
        case TILE_BLUE:
            tileRender.setFillColor(sf::Color::Blue);
            break;
        case TILE_CYAN:
            tileRender.setFillColor(sf::Color::Cyan);
            break;
        case TILE_GREEN:
            tileRender.setFillColor(sf::Color::Green);
            break;
        case TILE_ORANGE:
            tileRender.setFillColor(sf::Color(0xff9b00ff));
            break;
        case TILE_PURPLE:
            tileRender.setFillColor(sf::Color::Magenta);
            break;
        case TILE_RED:
            tileRender.setFillColor(sf::Color::Red);
            break;
        case TILE_YELLOW:
            tileRender.setFillColor(sf::Color::Yellow);
            break;
        default:
            tileRender.setFillColor(sf::Color::Transparent);
    }

    if (tileType != TILE_NULL)
    {
        tileRender.setOutlineThickness(1.f);
        tileRender.setOutlineColor(sf::Color(0x999999));
    }

    pWindow->draw(tileRender);
}

void Renderer::drawGhostTile(Tile tile)
{
    int col = tile.getCol();
    int row = tile.getRow();

    sf::RectangleShape tileRender(sf::Vector2f(TILE_RENDER_WIDTH, TILE_RENDER_HEIGHT));

    float tileX = (WINDOW_WIDTH / 2.f) - (BOARD_RENDER_WIDTH / 2.f) + (TILE_RENDER_WIDTH * col);
    float tileY = (WINDOW_HEIGHT / 2.f) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * (row - 20));

    tileRender.setPosition(tileX, tileY);
    tileRender.setFillColor(sf::Color(0xCCCCCCCC));
    tileRender.setOutlineThickness(1.f);
    tileRender.setOutlineColor(sf::Color(0x999999));
    pWindow->draw(tileRender);

}

void Renderer::drawPiece(const std::shared_ptr<Piece>& piece)
{
    std::array<Tile, TILES_PER_PIECE> tiles = piece->getTiles();

    for (auto& tile: tiles)
    {
        drawTile(tile);
    }
}

void Renderer::drawBoard(const std::shared_ptr<Board>& board)
{

    //Board background
    sf::Vector2f boardBgV(BOARD_RENDER_WIDTH, BOARD_RENDER_HEIGHT);
    sf::RectangleShape boardBg(boardBgV);
    boardBg.setOrigin(boardBgV.x / 2.0, boardBgV.y / 2.0);
    boardBg.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    boardBg.setFillColor(sf::Color::White);
    boardBg.setOutlineColor(sf::Color::Blue);
    boardBg.setOutlineThickness(2.0);
    pWindow->draw(boardBg);

    //Vertical grid lines
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(1.0, BOARD_RENDER_HEIGHT));
        gridLine.setPosition(WINDOW_WIDTH / 2.0 - BOARD_RENDER_WIDTH / 2 + TILE_RENDER_WIDTH * i,
                             (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0));
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }

    //Draw horizontal grid lines
    for (int i = 0; i < BOARD_HEIGHT / 2; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(BOARD_RENDER_WIDTH, 1.0));
        gridLine.setPosition((WINDOW_WIDTH / 2.0) - (BOARD_RENDER_WIDTH / 2.0),
                             (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * i));
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }

    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> tiles = board->getTiles();

    for (int i = (BOARD_HEIGHT / 2); i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            drawTile(tiles[i][j]);
        }
    }
}

void Renderer::drawGhostPiece(const std::shared_ptr<GhostPiece>& pGhostPiece)
{
    std::array<Tile, TILES_PER_PIECE> tiles = pGhostPiece->getTiles();

    for (auto& tile: tiles)
    {
        drawGhostTile(tile);
    }
}

void Renderer::drawPieceHolder(const std::shared_ptr<Holder>& holder)
{
    //Holder
    sf::Vector2f holderRenderV(TILE_RENDER_WIDTH * 4.0, TILE_RENDER_HEIGHT * 4.0);
    sf::RectangleShape holderRender(holderRenderV);
    holderRender.setOrigin(holderRenderV.x / 2.0, holderRenderV.y / 2.0);
    // 1 tile away from left edge of board
    float holderRenderX = (WINDOW_WIDTH / 2.0) - (BOARD_RENDER_WIDTH / 2.0) - (TILE_RENDER_WIDTH * 3.0);
    // 2 tiles away from top edge of board
    float holderRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 4.0);
    holderRender.setPosition(holderRenderX, holderRenderY);
    holderRender.setFillColor(sf::Color(0xCCCCCCAA));
    holderRender.setOutlineColor(sf::Color::Blue);
    holderRender.setOutlineThickness(2.0);
    pWindow->draw(holderRender);

    if (holder->getHeldPiece() != nullptr)
    {
        drawUIPiece(holder->getHeldPiece(), holderRenderX, holderRenderY, 0.8);
    }
}

//Draw a piece on a give spot on the screen
void Renderer::drawUIPiece(const std::shared_ptr<Piece>& piece, float pieceX, float pieceY, float scale)
{
    std::array<Tile, TILES_PER_PIECE> relativePieceTiles = piece->getRelativeTiles();


    //Offset the pieces so they render with their position in the center of their shape.
    float xOffset, yOffset;
    switch (piece->getType())
    {
        case O_PIECE:
            xOffset = TILE_RENDER_WIDTH * scale;
            yOffset = TILE_RENDER_HEIGHT * scale;
            break;
        case L_PIECE:
        case J_PIECE:
        case T_PIECE:
            xOffset = TILE_RENDER_WIDTH * scale / 2.0;
            yOffset = 0.0;
            break;
        case S_PIECE:
        case Z_PIECE:
            xOffset = TILE_RENDER_WIDTH * scale / 2.0;
            yOffset = 0.0;
            break;
        case I_PIECE:
            xOffset = TILE_RENDER_WIDTH * scale;
            yOffset = TILE_RENDER_HEIGHT * scale / 2.0;
            break;
        default:
            xOffset = 0.0;
            yOffset = 0.0;
    }

    for (Tile relPieceTile: relativePieceTiles)
    {
        int pieceCol = relPieceTile.getCol();
        int pieceRow = relPieceTile.getRow();

        float tileX = pieceX + (pieceCol * TILE_RENDER_WIDTH * scale) - xOffset;
        float tileY = pieceY + (pieceRow * TILE_RENDER_WIDTH * scale) - yOffset;

        drawTile(relPieceTile.getTileType(), tileX, tileY, scale);
    }
}

void Renderer::drawMenu(const std::shared_ptr<Menu>& menu)
{
    if (menu->getStatus() == MENU_OPEN)
    {
        //Large rectangle used to give the screen a dimmed effect
        sf::RectangleShape dimBackground(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        dimBackground.setPosition(0, 0);
        dimBackground.setFillColor(sf::Color(50, 50, 50, 200));

        //Background of menu
        sf::Vector2f menuBgV(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 1.5); //Menu's vector (shape)
        sf::RectangleShape menuBg(menuBgV);
        menuBg.setOrigin(menuBgV.x / 2.0, menuBgV.y / 2.0);
        menuBg.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
        menuBg.setFillColor(sf::Color(0xCCCCCCAA));
        menuBg.setOutlineColor(sf::Color::Green);
        menuBg.setOutlineThickness(2.0);

        pWindow->draw(dimBackground);
        pWindow->draw(menuBg);
    }
}

