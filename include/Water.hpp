#ifndef WATER_HPP
#define WATER_HPP

#include <SFML/Graphics.hpp>

class Water
{
public:
    Water(sf::VideoMode videoMode);
    void draw(sf::RenderWindow& window);
    void update();
    void lower();

private:
    sf::RectangleShape body;
};


#endif //WATER_HPP
