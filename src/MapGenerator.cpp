#include "MapGenerator.hpp"

MapGenerator::MapGenerator(GameObjects &gameObjects, sf::VideoMode videoMode, ltbl::LightSystem &lightSystem,
                           b2World &world)
        :gameObjects(gameObjects),
         videoMode(videoMode),
         lightSystem(lightSystem),
         world(world)
{}

void MapGenerator::generateMap()
{
    gameObjects.createPlatform(world, lightSystem, videoMode.width / 2 , videoMode.height -450);
    gameObjects.createPlatform(world, lightSystem, videoMode.width / 2 + 580, videoMode.height -200);
}

