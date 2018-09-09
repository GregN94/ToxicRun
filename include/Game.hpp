#ifndef GAME_HPP
#define GAME_HPP

#include "GameObjects.hpp"
#include "MapGenerator.hpp"
#include "MyContactListener.hpp"
#include "Stats.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <LTBL/LightSystem.h>

class Game
{
public:
    Game(sf::VideoMode videoMode, sf::RenderWindow &window);

    void setUp(sf::VideoMode videoMode);
    void run();
    void draw();


private:
    void controlPlayer();
    void cameraFollowPlayer();
    sf::Text gameOverText(sf::RenderWindow &window);

    sf::RenderWindow &window;
    ltbl::LightSystem lightSystem;
    GameObjects gameObjects;

    b2World world;
    std::shared_ptr<Player> player;
    MapGenerator mapGenerator;
    MyContactListener myContactListener;
    sf::Font font;
    Stats stats;
    Water water;
};


#endif //GAME_HPP
