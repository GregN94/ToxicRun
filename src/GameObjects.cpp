#include <GameObjects.hpp>

#include "GameObjects.hpp"
#include "ShadowObject.hpp"

void GameObjects::update()
{
    for (const auto object : objectList) {
        object->update();
    }
}

void GameObjects::lower()
{
    for (const auto object : objectList) {
        object->lower();
    }
}

void GameObjects::draw(sf::RenderWindow& window)
{
    for (const auto object : objectList) {
        window.draw(object->getBody());
    }
}

void GameObjects::loadTextures()
{
    platformTexture.loadFromFile("../res/ground.png");
    playerTexture.loadFromFile("../res/runner.png");
    wallTexture.loadFromFile("../res/wall.png");
}

void GameObjects::createWalls(b2World& world, sf::VideoMode videoMode)
{
    std::shared_ptr<GameObject> wall = std::make_shared<GameObject>(world,
                                                                    (float) wallTexture.getSize().x / 2,
                                                                    videoMode.height - (float) wallTexture.getSize().y / 2,
                                                                    wallTexture,
                                                                    1,
                                                                    b2_staticBody);
    wall->isMovingAllowed = false;
    objectList.push_back(wall);

    std::shared_ptr<GameObject> wall2 = std::make_shared<GameObject>(world,
                                                                     videoMode.width - wallTexture.getSize().x / 2,
                                                                     videoMode.height - wallTexture.getSize().y / 2,
                                                                     wallTexture,
                                                                     1,
                                                                     b2_staticBody);
    wall2->isMovingAllowed = false;
    objectList.push_back(wall2);
}

void GameObjects::createGround(b2World &world, sf::VideoMode videoMode)
{
    std::shared_ptr<GameObject> ground = std::make_shared<GameObject>(world,
                                                                     videoMode.width / 2,
                                                                     videoMode.height - platformTexture.getSize().y / 2,
                                                                     platformTexture,
                                                                     1,
                                                                     b2_staticBody);
    objectList.push_back(ground);

}

void GameObjects::createPlatform(b2World &world, ltbl::LightSystem &lightSystem, float positionX, float positionY)
{
    std::shared_ptr<ShadowObject> platform = std::make_shared<ShadowObject>(world,
                                                                      positionX,
                                                                      positionY,
                                                                      platformTexture,
                                                                      0.15,
                                                                      b2_staticBody);
    objectList.push_back(platform);
    lightSystem.addConvexHull(platform->convexHull);
}

std::shared_ptr<Player> GameObjects::createPlayer(b2World& world, sf::VideoMode videoMode, ltbl::LightSystem& lightSystem)
{
    std::shared_ptr<Player> player = std::make_shared<Player>(world,
                                                              videoMode.width/ 2,
                                                              videoMode.height - platformTexture.getSize().y,
                                                              playerTexture);
    objectList.push_back(player);
    lightSystem.addLight(player->light);
    return player;
}
