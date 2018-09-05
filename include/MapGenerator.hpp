#ifndef MAP_GENERATOR_HPP
#define MAP_GENERATOR_HPP

#include "GameObjects.hpp"

struct Position
{
    float x;
    float y;
};

class MapGenerator
{
public:
    MapGenerator(GameObjects& gameObjects,
                 sf::VideoMode videoMode,
                 ltbl::LightSystem& lightSystem,
                 b2World& world);
    void generateMap();
    void createMapFragment(Position mapFragment);
    void update();

private:
    GameObjects& gameObjects;
    sf::VideoMode videoMode;
    ltbl::LightSystem& lightSystem;
    b2World& world;
    std::vector<Position> mapParts;
    float highest = 0;
    std::shared_ptr<ShadowObject> highestPlatform;
};


#endif //MAP_GENERATOR_HPP
