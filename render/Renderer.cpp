//
// Created by jamie on 11/12/22.
//

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include "Renderer.h"
#include "../WindowConstants.h"

#define BOARD_RENDER_HEIGHT (WINDOW_HEIGHT / 1.2)
#define BOARD_RENDER_WIDTH (BOARD_RENDER_HEIGHT / 2.0)
#define TILE_RENDER_WIDTH (BOARD_RENDER_WIDTH / BOARD_WIDTH)
#define TILE_RENDER_HEIGHT (BOARD_RENDER_HEIGHT / (BOARD_HEIGHT / 2))
#define TEXT_SIZE (WINDOW_HEIGHT / 25.0)

Renderer::Renderer(sf::RenderWindow* pWindow)
{
    this->pWindow = pWindow;

    if (!mainFont.loadFromFile("../NotoSansCJK-Black.ttc"))
    {

        std::cout << "Error loading font..." << "\n";
        pWindow->close();
    }

    if (!logoTexture.loadFromFile("../images/mainLogo.png"))
    {
        std::cout << "Error loading mainLogo.png..." << "\n";
        pWindow->close();
    }
    logoSprite.setTexture(logoTexture);
}

void Renderer::render(const GameState& gameState)
{
    //Clear the window with white color
    pWindow->clear(sf::Color::White);

    switch (gameState.getMode())
    {
        case MAIN_MENU:
            drawMainMenu(gameState);
            break;
        case ONE_PLAYER_GAME:
            drawOnePlayerGame(gameState);
            break;
        case TWO_PLAYER_GAME:
            drawTwoPlayerGame(gameState);
            break;
    }

    //End the current frame
    pWindow->display();
}

void Renderer::drawMainMenu(GameState gameState)
{
//    drawMainLogo();

    Menu& menu = gameState.getMenuState();
    drawMenu(menu, (WINDOW_WIDTH / 2.0), (WINDOW_HEIGHT * 2.0 / 3.0), false);
}

void Renderer::drawOnePlayerGame(GameState gameState)
{

    Player& player1 = gameState.getPlayer1State();
    Board& board = player1.getBoard();
    std::shared_ptr<Piece> pPiece = player1.getPPiece();
    GhostPiece& ghostPiece = player1.getGhostPiece();
    Holder& holder = player1.getHolder();
    NextPieceQueue& NPQ = player1.getNPQ();
    unsigned long int score = player1.getScore();
    Menu& menu = gameState.getMenuState();


    float boardX = WINDOW_WIDTH / 2.0;
    float boardY = WINDOW_HEIGHT / 2.0;
    float boardBottomY = boardY + BOARD_RENDER_HEIGHT / 2.0;

    //Draw board pieces
    drawBoard(board, boardX, boardY);

    //Draw ghost piece
    drawGhostPiece(ghostPiece, boardX);

    //Draw active piece
    drawPiece(pPiece, boardX);

    //Draw piece holder
    drawPieceHolder(holder, boardX, PLAYER_ONE);

    //Draw next piece queue
    drawNPQ(NPQ, boardX, ONE_PLAYER_GAME, PLAYER_ONE);

    //Draw score
    drawScore(score, boardX, boardBottomY);

    //Draw the menu
    drawMenu(menu, (WINDOW_WIDTH / 2.0), (WINDOW_HEIGHT / 2.0));

    //Draw game over splash
    drawGameOverSplash(gameState, player1, player1);

    //Draw line and level info
    drawLevelInfo(ONE_PLAYER_GAME, boardX, player1);
}

void Renderer::drawTwoPlayerGame(GameState gameState)
{
    Player& player1 = gameState.getPlayer1State();
    Player& player2 = gameState.getPlayer2State();

    Board& board1 = player1.getBoard();
    Board& board2 = player2.getBoard();
    std::shared_ptr<Piece> pPiece1 = player1.getPPiece();
    std::shared_ptr<Piece> pPiece2 = player2.getPPiece();
    GhostPiece& ghostPiece1 = player1.getGhostPiece();
    GhostPiece& ghostPiece2 = player2.getGhostPiece();
    Holder& holder1 = player1.getHolder();
    Holder& holder2 = player2.getHolder();
    NextPieceQueue& NPQ1 = player1.getNPQ();
    NextPieceQueue& NPQ2 = player2.getNPQ();
    unsigned long int score1 = player1.getScore();
    unsigned long int score2 = player2.getScore();
    Menu& menu = gameState.getMenuState();

    float board1X = WINDOW_WIDTH / 3.0;
    float board1Y = WINDOW_HEIGHT / 2.0;
    float board1BottomY = board1Y + BOARD_RENDER_HEIGHT / 2.0;
    float board2X = WINDOW_WIDTH * 2.0 / 3.0;
    float board2Y = WINDOW_HEIGHT / 2.0;
    float board2BottomY = board2Y + BOARD_RENDER_HEIGHT / 2.0;

    //Draw boards
    drawBoard(board1, board1X, board1Y);
    drawBoard(board2, board2X, board2Y);

    //Draw ghost pieces
    drawGhostPiece(ghostPiece1, board1X);
    drawGhostPiece(ghostPiece2, board2X);

    //Draw active pieces
    drawPiece(pPiece1, board1X);
    drawPiece(pPiece2, board2X);

    //Draw piece holders
    drawPieceHolder(holder1, board1X, PLAYER_ONE);
    drawPieceHolder(holder2, board2X, PLAYER_TWO);

    //Draw next piece queues
    drawNPQ(NPQ1, board1X, TWO_PLAYER_GAME, PLAYER_ONE);
    drawNPQ(NPQ2, board2X, TWO_PLAYER_GAME, PLAYER_TWO);

    //Draw scores
    drawScore(score1, board1X, board1BottomY);
    drawScore(score2, board2X, board2BottomY);

    //Draw menu
    drawMenu(menu, (WINDOW_WIDTH / 2.0), (WINDOW_HEIGHT / 2.0));

    //Draw game over splash
    drawGameOverSplash(gameState, player1, player2);

    //Draw line and level info
    drawLevelInfo(TWO_PLAYER_GAME,board1X, player1);
    drawLevelInfo(TWO_PLAYER_GAME, board2X, player2);
}

void Renderer::drawTile(Tile tile, float boardX)
{
    int row = tile.getRow();
    int col = tile.getCol();
    int tileType = tile.getTileType();

    float xPos = boardX - (BOARD_RENDER_WIDTH / 2.f) + (TILE_RENDER_WIDTH * col);
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

void Renderer::drawGhostTile(Tile tile, float boardX)
{
    int col = tile.getCol();
    int row = tile.getRow();

    sf::RectangleShape tileRender(sf::Vector2f(TILE_RENDER_WIDTH, TILE_RENDER_HEIGHT));

    float tileX = boardX - (BOARD_RENDER_WIDTH / 2.f) + (TILE_RENDER_WIDTH * col);
    float tileY = (WINDOW_HEIGHT / 2.f) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * (row - 20));

    tileRender.setPosition(tileX, tileY);
    tileRender.setFillColor(sf::Color(0xCCCCCCCC));
    tileRender.setOutlineThickness(1.f);
    tileRender.setOutlineColor(sf::Color(0x999999));
    pWindow->draw(tileRender);

}

void Renderer::drawPiece(const std::shared_ptr<Piece>& piece, float boardX)
{
    std::array<Tile, TILES_PER_PIECE> tiles = piece->getTiles();

    for (auto& tile: tiles)
    {
        drawTile(tile, boardX);
    }
}

void Renderer::drawBoard(const Board& board, float xPos, float yPos)
{

    //Board background
    sf::Vector2f boardBgV(BOARD_RENDER_WIDTH, BOARD_RENDER_HEIGHT);
    sf::RectangleShape boardBg(boardBgV);
    boardBg.setOrigin(boardBgV.x / 2.0, boardBgV.y / 2.0);
    boardBg.setPosition(xPos, yPos);
    boardBg.setFillColor(sf::Color::White);
    boardBg.setOutlineColor(sf::Color::Blue);
    boardBg.setOutlineThickness(2.0);
    pWindow->draw(boardBg);

    //Vertical grid lines
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(1.0, BOARD_RENDER_HEIGHT));
        gridLine.setPosition(xPos - BOARD_RENDER_WIDTH / 2 + TILE_RENDER_WIDTH * i,
                             (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0));
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }

    //Draw horizontal grid lines
    for (int i = 0; i < BOARD_HEIGHT / 2; i++)
    {
        sf::RectangleShape gridLine(sf::Vector2f(BOARD_RENDER_WIDTH, 1.0));
        gridLine.setPosition(xPos - (BOARD_RENDER_WIDTH / 2.0),
                             (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * i));
        gridLine.setFillColor(sf::Color(0x99, 0x99, 0x99));
        pWindow->draw(gridLine);
    }

    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> tiles = board.getTiles();

    for (int i = (BOARD_HEIGHT / 2); i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            drawTile(tiles[i][j], xPos);
        }
    }
}

void Renderer::drawGhostPiece(const GhostPiece& ghostPiece, float boardX)
{
    std::array<Tile, TILES_PER_PIECE> tiles = ghostPiece.getTiles();

    for (auto& tile: tiles)
    {
        drawGhostTile(tile, boardX);
    }
}

void Renderer::drawPieceHolder(const Holder& holder, float boardX, int player)
{
    //Bounding box position
    float holderRenderX, holderRenderY;

    if (player == PLAYER_ONE)
    {
        // 1 tile away from left edge of board
        holderRenderX = boardX - (BOARD_RENDER_WIDTH / 2.0) - (TILE_RENDER_WIDTH * 3.0);
        // 2 tiles away from top edge of board
        holderRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 4.0);
    }
    else
    {
        // 1 tile away from right edge of board
        holderRenderX = boardX + (BOARD_RENDER_WIDTH / 2.0) + (TILE_RENDER_WIDTH * 3.0);
        // 2 tiles away from top edge of board
        holderRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 4.0);
    }


    //Draw bounding box
    sf::Vector2f holderRenderV(TILE_RENDER_WIDTH * 4.0, TILE_RENDER_HEIGHT * 4.0);
    sf::RectangleShape holderRender(holderRenderV);
    holderRender.setOrigin(holderRenderV.x / 2.0, holderRenderV.y / 2.0);

    holderRender.setPosition(holderRenderX, holderRenderY);
    holderRender.setFillColor(sf::Color(0xCCCCCCAA));
    holderRender.setOutlineColor(sf::Color::Blue);
    holderRender.setOutlineThickness(2.0);
    pWindow->draw(holderRender);

    //Text "HOLD"
    sf::Text holdText;
    holdText.setFont(mainFont);
    holdText.setString("HOLD");
    holdText.setCharacterSize(TEXT_SIZE);
    holdText.setFillColor(sf::Color::Black);
    sf::FloatRect holdTextV = holdText.getLocalBounds();
    holdText.setOrigin(holdTextV.left + holdTextV.width / 2.0, holdTextV.top + holdTextV.height / 2.0);
    float topOfBox = holderRenderY - holderRenderV.y / 2.0;
    holdText.setPosition(holderRenderX, topOfBox - TILE_RENDER_HEIGHT);
    pWindow->draw(holdText);

    //Piece display
    if (holder.getHeldPiece() != nullptr)
    {
        drawUIPiece(holder.getHeldPiece(), holderRenderX, holderRenderY, 0.8);
    }
}

void Renderer::drawNPQ(const NextPieceQueue& NPQ, float boardX, int mode, int player)
{
    //Bounding box position
    float NPQRenderX, NPQRenderY;
    if (mode == ONE_PLAYER_GAME)
    {
        // 1 tile away from right edge of board
        NPQRenderX = boardX + (BOARD_RENDER_WIDTH / 2.0) + (TILE_RENDER_WIDTH * 3.0);

        // 2 tiles away from top edge of board
        NPQRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 6.0);
    }
    else
    {
        if (player == PLAYER_ONE)
        {
            // 1 tile away from left edge of board
            NPQRenderX = boardX - (BOARD_RENDER_WIDTH / 2.0) - (TILE_RENDER_WIDTH * 3.0);

            // 8 tiles away from top edge of board
            NPQRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 12.0);
        }
        else
        {
            // 1 tile away from right edge of board
            NPQRenderX = boardX + (BOARD_RENDER_WIDTH / 2.0) + (TILE_RENDER_WIDTH * 3.0);

            // 8 tiles away from top edge of board
            NPQRenderY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 12.0);
        }

    }

    //Draw bounding box
    sf::Vector2f NPQRenderV(TILE_RENDER_WIDTH * 4.0, TILE_RENDER_HEIGHT * 4.0 * 2.0);
    sf::RectangleShape NPQRender(NPQRenderV);
    NPQRender.setOrigin(NPQRenderV.x / 2.0, NPQRenderV.y / 2.0);
    NPQRender.setPosition(NPQRenderX, NPQRenderY);
    NPQRender.setFillColor(sf::Color(0xCCCCCCAA));
    NPQRender.setOutlineColor(sf::Color::Blue);
    NPQRender.setOutlineThickness(2.0);
    pWindow->draw(NPQRender);

    //Text "NEXT"
    sf::Text nextText;
    nextText.setFont(mainFont);
    nextText.setString("NEXT");
    nextText.setCharacterSize(TEXT_SIZE);
    nextText.setFillColor(sf::Color::Black);
    sf::FloatRect nextTextV = nextText.getLocalBounds();
    nextText.setOrigin(nextTextV.left + nextTextV.width / 2.0, nextTextV.top + nextTextV.height / 2.0);
    float topOfBox = NPQRenderY - NPQRenderV.y / 2.0;
    nextText.setPosition(NPQRenderX, topOfBox - TILE_RENDER_HEIGHT);
    pWindow->draw(nextText);

    //NPQ pieces
    float topOfBoundBox = NPQRenderY - (NPQRenderV.y / 2.0);
    float separation = NPQRenderV.y / NPQ.size();
    for (unsigned long int i = 0; i < NPQ.size(); i++)
    {
        float yPos = topOfBoundBox + (separation / 2.0) + separation * i;
        drawUIPiece(NPQ.peek(i), NPQRenderX, yPos, 0.8);
    }
}

//Draw a piece on a give spot on the screen
void
Renderer::drawUIPiece(const std::shared_ptr<Piece>& pPiece, float pieceX, float pieceY, float scale)
{
    std::array<Tile, TILES_PER_PIECE> relativePieceTiles = pPiece->getRelativeTiles();


    //Offset the pieces so they render with their position in the center of their shape.
    float xOffset, yOffset;
    switch (pPiece->getType())
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

void Renderer::drawMenu(Menu& menu, float xPos, float yPos)
{
    drawMenu(menu, xPos, yPos, true);
}

void Renderer::drawMenu(Menu& menu, float xPos, float yPos, bool drawBackground)
{
    if (menu.getStatus() == MENU_OPEN)
    {

        //Large rectangle used to give the screen a dimmed effect
        if (drawBackground)
        {
            sf::RectangleShape dimBackground(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            dimBackground.setPosition(0, 0);
            dimBackground.setFillColor(sf::Color(50, 50, 50, 200));
            pWindow->draw(dimBackground);
        }

        //Background of menu
        sf::Vector2f menuBgV(menu.getWidth(), menu.getHeight()); //Menu's vector (shape)
        sf::RectangleShape menuBg(menuBgV);
        menuBg.setOrigin(menuBgV.x / 2.0, menuBgV.y / 2.0);
        float menuBgX = xPos;
        float menuBgY = yPos;
        menuBg.setPosition(menuBgX, menuBgY);
        menuBg.setFillColor(sf::Color(0xCCCCCCAA));
        menuBg.setOutlineColor(sf::Color::Blue);
        menuBg.setOutlineThickness(2.0);
        pWindow->draw(menuBg);

        //Draw menu buttons
        float marginSize = menuBgV.x / 50.0;
        float buttonWidth = menuBgV.x / 1.2 - marginSize * 2.0;
        float buttonHeight = (menuBgV.y / menu.getNumButtons()) / 1.2 - marginSize * 2.0;
        float topOfMenu = menuBgY - menuBgV.y / 2.0;
        float separation = menuBgV.y / menu.getNumButtons();

        for (int i = 0; i < menu.getNumButtons(); i++)
        {
            Button button = menu.getButton(i);

            //Draw button
            float buttonX = menuBgX;
            float buttonY = topOfMenu + (separation / 2.0) + separation * i;
            sf::Vector2f buttonRenderV(buttonWidth, buttonHeight);
            sf::RectangleShape buttonRender(buttonRenderV);
            buttonRender.setOrigin(buttonWidth / 2.0, buttonHeight / 2.0);
            buttonRender.setPosition(buttonX, buttonY);
            if (button.isActive())
            {
                buttonRender.setFillColor(sf::Color(0x0000FFFF));
            }
            else
            {
                buttonRender.setFillColor(sf::Color(0x000099FF));
            }
            buttonRender.setOutlineColor(sf::Color::Black);
            buttonRender.setOutlineThickness(2);
            pWindow->draw(buttonRender);

            //Draw button text
            sf::Text buttonText;
            buttonText.setFont(mainFont);
            buttonText.setString(button.getText());
            buttonText.setCharacterSize(TEXT_SIZE);
            if (button.isActive())
            {
                buttonText.setFillColor(sf::Color::White);
            }
            else
            {
                buttonText.setFillColor(sf::Color::Black);
            }
            sf::FloatRect buttonTextV = buttonText.getGlobalBounds();
            buttonText.setOrigin(buttonTextV.left + buttonTextV.width / 2.0,
                                 buttonTextV.top + buttonTextV.height / 2.0);
            buttonText.setPosition(buttonX, buttonY);
            pWindow->draw(buttonText);
        }
    }
}

void Renderer::drawMainLogo()
{
    sf::Vector2i logoPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 3.0);
    sf::Vector2i logoSize((WINDOW_WIDTH / 5.0), (WINDOW_HEIGHT / 3.0));
    sf::IntRect logoRect(logoPosition, logoSize);

    logoSprite.setTextureRect(logoRect);

    pWindow->draw(logoSprite);
}

void Renderer::drawScore(unsigned long int score, float boardX, float boardBottomY)
{
    sf::Text scoreText;
    scoreText.setFont(mainFont);
    scoreText.setString(std::to_string(score));
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setCharacterSize(TEXT_SIZE);
    sf::FloatRect scoreTextV = scoreText.getGlobalBounds();
    scoreText.setOrigin(scoreTextV.left + scoreTextV.width / 2.0,
                        scoreTextV.top + scoreTextV.height / 2.0);
    scoreText.setPosition(boardX, boardBottomY + TILE_RENDER_HEIGHT * 1.0);
    pWindow->draw(scoreText);
}

void Renderer::drawGameOverSplash(GameState gameState, Player& player1, Player& player2)
{
    if (gameState.isGameOver())
    {
        //Dimmed background
        sf::RectangleShape dimBackground(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        dimBackground.setPosition(0, 0);
        dimBackground.setFillColor(sf::Color(50, 50, 50, 100));
        pWindow->draw(dimBackground);

        //"GAME OVER"
        sf::Text gameOverText;
        gameOverText.setFont(mainFont);
        gameOverText.setString("GAME OVER");
        gameOverText.setFillColor(sf::Color::Black);
        gameOverText.setCharacterSize(TEXT_SIZE * 4.0);
        sf::FloatRect gameOverTextV = gameOverText.getGlobalBounds();
        gameOverText.setOrigin(gameOverTextV.left + gameOverTextV.width / 2.0,
                               gameOverTextV.top + gameOverTextV.height / 2.0);
        float gameOverX = WINDOW_WIDTH / 2.0;
        float gameOverY = WINDOW_HEIGHT / 2.0;
        gameOverText.setPosition(gameOverX, gameOverY);
        pWindow->draw(gameOverText);


        float winTextX = gameOverX;
        float winTextY = gameOverY + gameOverTextV.height;
        if (gameState.getMode() == TWO_PLAYER_GAME)
        {
            //"Player x Wins!"
            sf::Text winText;
            winText.setFont(mainFont);
            if (player1.getScore() > player2.getScore())
            {
                winText.setString("Player 1 Wins!");
            }
            else if (player1.getScore() < player2.getScore())
            {
                winText.setString("Player 2 Wins!");
            }
            else
            {
                winText.setString("Tied Game!");
            }

            winText.setFillColor(sf::Color::Black);
            winText.setCharacterSize(TEXT_SIZE);
            sf::FloatRect winTextV = winText.getGlobalBounds();
            winText.setOrigin(winTextV.left + winTextV.width / 2.0,
                              winTextV.top + winTextV.height / 2.0);
            winText.setPosition(winTextX, winTextY);
            pWindow->draw(winText);
        }

        if (gameState.getGameOverDelayTime().asMilliseconds() > GAME_OVER_DELAY)
        {
            //"Press any key to continue
            sf::Text continueText;
            continueText.setFont(mainFont);
            continueText.setString("Press any key to continue");
            continueText.setFillColor(sf::Color::Black);
            continueText.setCharacterSize(TEXT_SIZE);
            sf::FloatRect continueTextV = continueText.getGlobalBounds();
            continueText.setOrigin(continueTextV.left + continueTextV.width / 2.0,
                                   continueTextV.top + continueTextV.height / 2.0);
            if (gameState.getMode() == ONE_PLAYER_GAME)
            {
                continueText.setPosition(gameOverX, gameOverY + gameOverTextV.height);
            }
            else
            {
                continueText.setPosition(winTextX, winTextY + gameOverTextV.height);
            }
            pWindow->draw(continueText);
        }
    }
}

void Renderer::drawLevelInfo(int mode, float boardX, Player& player)
{

    float infoTextX, infoTextY;
    if (mode == ONE_PLAYER_GAME)
    {
        // 1 tile away from left edge of board
        infoTextX = boardX - (BOARD_RENDER_WIDTH / 2.0) - (TILE_RENDER_WIDTH * 3.0);

        // 2 tiles away from top edge of board
        infoTextY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 18.0);
    }
    else
    {
        if (player.getPlayerNumber() == PLAYER_ONE)
        {
            // 1 tile away from left edge of board
            infoTextX = boardX - (BOARD_RENDER_WIDTH / 2.0) - (TILE_RENDER_WIDTH * 3.0);

            // 8 tiles away from top edge of board
            infoTextY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 18.0);
        }
        else
        {
            // 1 tile away from right edge of board
            infoTextX = boardX + (BOARD_RENDER_WIDTH / 2.0) + (TILE_RENDER_WIDTH * 3.0);

            // 8 tiles away from top edge of board
            infoTextY = (WINDOW_HEIGHT / 2.0) - (BOARD_RENDER_HEIGHT / 2.0) + (TILE_RENDER_HEIGHT * 18.0);
        }

    }

    //Draw bounding box
    sf::Vector2f NPQRenderV(TILE_RENDER_WIDTH * 4.0, TILE_RENDER_HEIGHT * 4.0 * 2.0);
    sf::RectangleShape NPQRender(NPQRenderV);
    NPQRender.setOrigin(NPQRenderV.x / 2.0, NPQRenderV.y / 2.0);
    NPQRender.setPosition(infoTextX, infoTextY);
    NPQRender.setFillColor(sf::Color(0xCCCCCCAA));
    NPQRender.setOutlineColor(sf::Color::Blue);
    NPQRender.setOutlineThickness(2.0);
//    pWindow->draw(NPQRender);

    //Text "LEVEL: XX"
    sf::Text levelText;
    levelText.setFont(mainFont);
    levelText.setString("LEVEL: " + std::to_string(player.getLevel()));
    levelText.setCharacterSize(TEXT_SIZE);
    levelText.setFillColor(sf::Color::Black);
    sf::FloatRect levelTextV = levelText.getLocalBounds();
    levelText.setOrigin(levelTextV.left + levelTextV.width / 2.0, levelTextV.top + levelTextV.height / 2.0);
    levelText.setPosition(infoTextX, infoTextY);
    pWindow->draw(levelText);

    //Text "LINES: XX"
    sf::Text linesText;
    linesText.setFont(mainFont);
    linesText.setString("LINES: " + std::to_string(player.getLinesCleared()));
    linesText.setCharacterSize(TEXT_SIZE);
    linesText.setFillColor(sf::Color::Black);
    sf::FloatRect linesTextV = linesText.getLocalBounds();
    linesText.setOrigin(linesTextV.left + linesTextV.width / 2.0, linesTextV.top + linesTextV.height / 2.0);
    linesText.setPosition(infoTextX, infoTextY + linesTextV.height * 1.5);
    pWindow->draw(linesText);
}