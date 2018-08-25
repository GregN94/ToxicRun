#include "Player.hpp"
#include <iostream>

Player::Player(b2World& world, float x, float y, sf::Texture& texture)
    : GameObject(world, x, y, texture, 0.1, b2_dynamicBody)
{
    b2MassData mass{5, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);
}

void Player::moveLeft()
{
    if (physicalBody->GetLinearVelocity().x > -maxSpeed)
        physicalBody->ApplyForce(b2Vec2(-force, 0), physicalBody->GetWorldCenter(), true);
}

void Player::moveRight()
{
    if (physicalBody->GetLinearVelocity().x < maxSpeed)
        physicalBody->ApplyForce(b2Vec2(force, 0), physicalBody->GetWorldCenter(), true);
}

void Player::jump()
{
        float impulse = -physicalBody->GetMass() * 3.5;
            physicalBody->ApplyLinearImpulse(b2Vec2(0,impulse), physicalBody->GetWorldCenter(), true );

}
