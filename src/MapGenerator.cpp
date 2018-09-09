#include <random>
#include "MapGenerator.hpp"

#define MIN_WIDTH 400
#define MAX_WIDTH 580
#define MIN_HEIGHT 150
#define MAX_HEIGHT 250

std::vector<Position> fragment_01 = { {200, 0},
//                                      {400, 150},
                                      {800, 200},
                                      {600, 100 + MAX_HEIGHT} };

std::vector<Position> fragment_02 = { {900, 0},
                                      {400, 200},
                                      {600, 100 + MAX_HEIGHT} };

std::vector<Position> fragment_03 = { {400, 200},
                                      {900, 400} };

std::vector<std::vector<Position>> mapFragments = { fragment_01,
                                                    fragment_02,
                                                    fragment_03 };



MapGenerator::MapGenerator(GameObjects &gameObjects, sf::VideoMode videoMode, ltbl::LightSystem &lightSystem,
                           b2World &world)
        :gameObjects(gameObjects),
         videoMode(videoMode),
         lightSystem(lightSystem),
         world(world)
{
    mapParts.push_back( { 0, -(float) videoMode.height / 2 } );
    mapParts.push_back( { (float) videoMode.width / 2, -(float) videoMode.height / 2 } );
    mapParts.push_back( { 0, 0 } );
    mapParts.push_back( { (float) videoMode.width / 2, 0 } );
    mapParts.push_back( { 0, (float) videoMode.height / 2 } );
    mapParts.push_back( { (float) videoMode.width / 2, (float) videoMode.height / 2 } );
}

void MapGenerator::generateMap()
{
    for (const auto mapPart : mapParts)
    {
        createMapFragment(mapPart);
    }
}

void MapGenerator::createMapFragment(Position mapFragment)
{
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> range(0, (int)mapFragments.size() - 1); // define the range
    auto index = (unsigned)range(eng);
    for (const auto platformPosition : mapFragments.at(index))
    {
        float positionX = platformPosition.x + mapFragment.x;
        float positionY = platformPosition.y + mapFragment.y;

        if (highest > positionY)
        {
            highest = positionY;
            highestPlatform = gameObjects.createPlatform(world, lightSystem, positionX, positionY);
        }
        else
        {
            gameObjects.createPlatform(world, lightSystem, positionX, positionY);
        }
    }
}

void MapGenerator::update()
{
    highest = highestPlatform->graphicBody.getPosition().y;
    if (highest >= 0)
    {
        createMapFragment(mapParts.at(0));
        createMapFragment(mapParts.at(1));
    }
}
