#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player(b2World& world, float x, float y, sf::Texture& texture);
    void moveLeft();
    void moveRight();
    void jump();

private:
    int maxSpeed = 1;
    int force = 5;
};

#endif // PLAYER_HPP
