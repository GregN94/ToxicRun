#include "Stats.hpp"

Stats::Stats(sf::RenderWindow& window)
    :  window(window)
{
    heartTexture.loadFromFile("../res/heart.png");

    heart.setOrigin(120, 100);
    heart.setPosition(60, 50);
    heart.setTexture(heartTexture);
    heart.setScale(0.4, 0.4);

    font.loadFromFile("../res/Arial.ttf");

    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(32); // in pixels, not points!

    text.setFillColor(sf::Color::Red);
    text.setPosition(60, 60);
    text.setStyle(sf::Text::Bold);

    pointsText.setFont(font);
    pointsText.setCharacterSize(32); // in pixels, not points!

    pointsText.setFillColor(sf::Color::Yellow);
    pointsText.setPosition(window.getSize().x / 2, 50);
    pointsText.setStyle(sf::Text::Bold);
}

void Stats::update(int playerHP, int distance)
{
    this->playerHP = playerHP;
    this->distance = distance;
}

void Stats::draw()
{
    text.setString(std::to_string(this->playerHP));
    text.setOrigin(text.getGlobalBounds().width / 2, 20);
    window.draw(heart);
    window.draw(text);

    pointsText.setString("Score: " + std::to_string(this->distance));
    pointsText.setOrigin(pointsText.getGlobalBounds().width / 2, 20);
    window.draw(pointsText);
}

