#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "GameObject.hpp"
#include <SFML/Graphics.hpp>

class GameObjects
{
public:
    GameObjects() {objectList.reserve(40);}
    void update();
    void add(GameObject);
    void draw(sf::RenderWindow&);

    std::vector<std::shared_ptr<IGameObject>> objectList;
    void add(std::shared_ptr<IGameObject> object_ptr);
};

#endif GAME_OBJECTS_H
