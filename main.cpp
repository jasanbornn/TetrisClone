#include <SFML/Graphics.hpp>
#include "input/InputHandler.h"
#include "render/Renderer.h"
#include "WindowConstants.h"

int main()
{
    //Seed randomizer
    unsigned seed = time(nullptr);
    srand(seed);

    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");

    InputHandler inputHandler(&window);
    GameState gameState(&window);
    Renderer renderer(&window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Input input = inputHandler.poll();
        gameState.update(input);
        renderer.render(gameState);
    }

    return 0;
}