
#include <Water.hpp>

#include "Water.hpp"

Water::Water(sf::VideoMode videoMode)
{
    body = sf::RectangleShape(sf::Vector2f(videoMode.width, videoMode.height));
    body.setPosition(0, videoMode.height);
    body.setFillColor(sf::Color(0, 100, 0, 120));
}

void Water::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Water::update()
{
    body.setPosition( 0, (float)(body.getPosition().y - 0.2) );

}

void Water::lower()
{
    body.setPosition( 0, (float)(body.getPosition().y + 0.2) );

}

float Water::getSurfacePosition()
{
    return body.getPosition().y;
}
