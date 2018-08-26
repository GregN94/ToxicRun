//
// Created by grzegorz on 26.08.18.
//

#include "GameObjects.hpp"

void GameObjects::update()
{
    for (auto object : objectList) {
        object->update();
    }
}

void GameObjects::draw(sf::RenderWindow& window)
{
    for (auto object : objectList) {
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