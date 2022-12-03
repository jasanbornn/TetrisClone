#include <SFML/Graphics.hpp>
#include "input/InputHandler.h"
#include "render/Renderer.h"
#include "control/Updater.h"
#include "WindowConstants.h"

int main()
{
    //Seed randomizer
    unsigned seed = time(nullptr);
    srand(seed);

    // create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window");

    InputHandler inputHandler(&window);
    Updater updater(&window);
    Renderer renderer(&window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Input input = inputHandler.poll();
        GameState gameState = updater.update(input);
        renderer.render(gameState);
    }

    return 0;
}