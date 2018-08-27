#include "Player.hpp"
#include <iostream>

#define MAX_SPEED   1.5
#define FORCE       10
#define TORQUE      100

Player::Player(b2World& world, float x, float y, sf::Texture& texture, float scale)
    : GameObject(world, x, y, texture, scale, b2_dynamicBody)
{
    b2MassData mass{18, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);
    physicalBody->SetAngularDamping(2);
    physicalBody->SetSleepingAllowed(false);
}

void Player::moveLeft()
{
    if (physicalBody->GetLinearVelocity().x > -MAX_SPEED)
        physicalBody->ApplyForce(b2Vec2(-FORCE, 0), physicalBody->GetWorldCenter(), true);
}

void Player::moveRight()
{
    if (physicalBody->GetLinearVelocity().x < MAX_SPEED)
        physicalBody->ApplyForce(b2Vec2(FORCE, 0), physicalBody->GetWorldCenter(), true);
}

void Player::jump()
{

    float impulse = -physicalBody->GetMass() * 5;
    physicalBody->ApplyLinearImpulse(b2Vec2(0, impulse), physicalBody->GetWorldCenter(), true);
//    std::cout << "jump" << std::endl;
}

void Player::update()
{
    if (physicalBody->GetAngle() > b2_pi / 6)
        physicalBody->ApplyTorque(-TORQUE, true);
    if (physicalBody->GetAngle() < -b2_pi / 6)
        physicalBody->ApplyTorque(TORQUE, true);

    GameObject::update();
}