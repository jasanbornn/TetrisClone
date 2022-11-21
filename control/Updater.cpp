//
// Created by jamie on 11/13/22.
//

#include "Updater.h"

Updater::Updater(sf::RenderWindow* pWindow)
{
    this->pWindow = pWindow;
}

GameState Updater::update(const Input& input)
{
    Board board = this->gameState.getBoardState();
    Piece piece = this->gameState.getPieceState();

    std::vector<sf::Event> events = input.getEvents();

    for (int i = 0; i < events.size(); i++)
    {
        switch (events.at(i).type)
        {
            case sf::Event::Closed:
                pWindow->close();
                break;
//            case sf::Event::Resized:
//                break;
//            case sf::Event::LostFocus:
//                break;
//            case sf::Event::GainedFocus:
//                break;
//            case sf::Event::TextEntered:
//                break;
            case sf::Event::KeyPressed:

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    pWindow->close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    if(pieceCanMove(piece,1, 0))
                    {
                        piece.moveDown();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    if(pieceCanMove(piece,0, -1))
                    {
                        piece.moveLeft();
                    }
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    if(pieceCanMove(piece,0, 1))
                    {
                        piece.moveRight();
                    }
                }

                break;
            case sf::Event::KeyReleased:
                break;
//            case sf::Event::MouseWheelMoved:
//                break;
//            case sf::Event::MouseWheelScrolled:
//                break;
//            case sf::Event::MouseButtonPressed:
//                break;
//            case sf::Event::MouseButtonReleased:
//                break;
//            case sf::Event::MouseMoved:
//                break;
//            case sf::Event::MouseEntered:
//                break;
//            case sf::Event::MouseLeft:
//                break;
//            case sf::Event::JoystickButtonPressed:
//                break;
//            case sf::Event::JoystickButtonReleased:
//                break;
//            case sf::Event::JoystickMoved:
//                break;
//            case sf::Event::JoystickConnected:
//                break;
//            case sf::Event::JoystickDisconnected:
//                break;
//            case sf::Event::TouchBegan:
//                break;
//            case sf::Event::TouchMoved:
//                break;
//            case sf::Event::TouchEnded:
//                break;
//            case sf::Event::SensorChanged:
//                break;
//            case sf::Event::Count:
//                break;
        }
    }

    gameState = GameState(board, piece);

    return gameState;

}

bool Updater::pieceCanMove(Piece piece, int dRow, int dCol)
{
    std::array<Tile, TILES_PER_PIECE> pieceTiles = piece.getTiles();
    std::array<std::array<Tile, BOARD_WIDTH>, BOARD_HEIGHT> boardTiles = this->gameState.getBoardState().getTiles();
    for (int i = 0; i < TILES_PER_PIECE; i++)
    {
        if (pieceTiles[i].getCol() + dCol > BOARD_WIDTH - 1 || pieceTiles[i].getCol() + dCol < 0)
        {
            return false;
        }

        if (pieceTiles[i].getRow() + dRow > BOARD_HEIGHT - 1 || pieceTiles[i].getRow() + dRow < 0)
        {
            return false;
        }

        if (boardTiles[pieceTiles[i].getRow() + dRow][pieceTiles[i].getCol() + dCol].getTileType() != TILE_NULL)
        {
            return false;
        }

    }
    return true;
}