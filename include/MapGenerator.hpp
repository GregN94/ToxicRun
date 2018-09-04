#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "GameObjects.hpp"

#define MIN_WIDTH 400
#define MAX_WIDTH 580
#define MIN_HIGHT 150
#define MAX_HIGHT 250

class MapGenerator
{
public:
    MapGenerator(GameObjects& gameObjects,
                 sf::VideoMode videoMode,
                 ltbl::LightSystem& lightSystem,
                 b2World& world);
    void generateMap();

private:
    GameObjects& gameObjects;
    sf::VideoMode videoMode;
    ltbl::LightSystem& lightSystem;
    b2World& world;
};


#endif //MAP_GENERATOR_HPP
