#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

class Player : public GameObject
{
public:
    Player(b2World& world, float x, float y, sf::Texture& texture);
    void update() override;
    void moveLeft();
    void moveRight();
    void jump();

private:
    float maxSpeed = 0.5;
    float force = 2.55;
};

#endif // PLAYER_HPP
