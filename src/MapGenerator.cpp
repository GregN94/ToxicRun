
#include <MapGenerator.hpp>

#include "MapGenerator.hpp"

#define MIN_WIDTH 400
#define MAX_WIDTH 580
#define MIN_HEIGHT 150
#define MAX_HEIGHT 250

std::vector<Position> fragment = { {200, 0},
                                   {400, 150},
                                   {400 + MAX_WIDTH, 150},
                                   {600, 100 + MAX_HEIGHT} };

std::vector<std::vector<Position>> mapFragments = {fragment};



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
    for (const auto platformPosition : fragment)
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
