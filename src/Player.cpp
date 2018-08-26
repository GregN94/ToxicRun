#include "Player.hpp"
#include <iostream>

Player::Player(b2World& world, float x, float y, sf::Texture& texture)
    : GameObject(world, x, y, texture, 0.1, b2_dynamicBody)
{
    b2MassData mass{18, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);
    physicalBody->SetAngularDamping(2);
    physicalBody->SetSleepingAllowed(false);
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
    float impulse = -physicalBody->GetMass() * 0.165 / 15;
        physicalBody->ApplyLinearImpulse(b2Vec2(0,impulse), physicalBody->GetWorldCenter(), true );
}

void Player::update()
{
    if (physicalBody->GetAngle() > 3.14 / 6)
        physicalBody->ApplyTorque(-55, true);
    if (physicalBody->GetAngle() < -3.14 / 6)
        physicalBody->ApplyTorque(55, true);

    GameObject::update();
}