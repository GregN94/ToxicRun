#ifndef STATS_HPP
#define STATS_HPP

#include <SFML/Graphics.hpp>

class Stats
{
public:
    explicit Stats(sf::RenderWindow& window);
    void update(int playerHP, int distance);
    void draw();

private:
    sf::Texture heartTexture;
    sf::RenderWindow& window;

    sf::Font font;
    sf::Sprite heart;
    sf::Text text;
    sf::Text pointsText;
    int playerHP = 100;
    int distance = 0;
};


#endif //STATS_HPP
