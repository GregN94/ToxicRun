#include "GameObjects.hpp"

void GameObjects::update()
{
    for (const auto object : objectList) {
        object->update();
    }
}

void GameObjects::draw(sf::RenderWindow& window)
{
    for (const auto object : objectList) {
        window.draw(object->getBody());
    }
}

void GameObjects::add(std::shared_ptr<IGameObject> object_ptr)
{
    objectList.push_back(object_ptr);
}

void GameObjects::add(GameObject newGameObject)
{
    objectList.push_back(std::make_shared<GameObject>(newGameObject));
}