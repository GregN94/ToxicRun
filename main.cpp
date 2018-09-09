#include "Game.hpp"

#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define BITS_PER_PIXEL  32

void closeWindow(sf::RenderWindow& window);

int main()
{
    sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL);
    sf::RenderWindow window(videoMode, "ToxicRun", sf::Style::Fullscreen);

    Game game(videoMode, window);
    game.setUp(videoMode);

    while (window.isOpen())
    {
        closeWindow(window);
        window.clear(sf::Color::White);
        game.run();
    }
    return 0;
}

void closeWindow(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}
