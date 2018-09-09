#include "Game.hpp"

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define BITS_PER_PIXEL  32

int main()
{
    sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL);
    sf::RenderWindow window(videoMode, "ToxicRun", sf::Style::Fullscreen);

    Game game(videoMode, window);
    game.setUp(videoMode);

    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        if (game.run())
            window.close();
    }
    return 0;
}

