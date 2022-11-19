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
        switch(events.at(i).type)
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
                    piece.moveDown();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    piece.moveLeft();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    piece.moveRight();
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

    gameState = GameState(board,piece);

    return gameState;

}
