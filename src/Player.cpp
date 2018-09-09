#include "Player.hpp"
#include <iostream>
#include <Player.hpp>


#define STAND_IMG   8
#define RISE_IMG    3
#define FALL_IMG    2

std::vector<sf::IntRect> images = {sf::IntRect(0,    0,   480,  440),
                                     sf::IntRect(480,  0,   480,  440),
                                     sf::IntRect(960,  0,   480, 440),
                                     sf::IntRect(1440, 0,   480, 440),
                                     sf::IntRect(0,    440, 480,  440),
                                     sf::IntRect(480,  440, 480,  440),
                                     sf::IntRect(960,  440, 480, 440),
                                     sf::IntRect(1440, 440, 480, 440),
                                     sf::IntRect(1920, 0,   480, 440)};


Player::Player(b2World& world,
               float positionX,
               float positionY,
               sf::Texture& texture,
               ltbl::LightSystem& lightSystem,
               float scale)
    : lightSystem(lightSystem)
{
    objectScale = scale;
    createGraphicBody(texture, images.at(imageIndex), positionX, positionY);
    createPhysicalBody(world, b2_dynamicBody, positionX, positionY, 0.2, 0.75, DENSITY, FRICTION);

    graphicBody.setRotation(physicalBody->GetAngle() * 180 / b2_pi);
    createFootSensor();

    b2MassData mass {MASS, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);

    physicalBody->SetSleepingAllowed(false);
    physicalBody->SetFixedRotation(true);

    createLight();
}

Player::~Player()
{
    lightSystem.removeLight(light);
    delete light;
}

void Player::createFootSensor()
{
    b2Vec2 center = b2Vec2(0, (float32)(graphicBody.getTextureRect().height *
                                        0.75 * objectScale / (2 * BOX2D_SCALE)));
    float width = 0.3;
    float height = 0.3;
    float angle = 0;
    b2PolygonShape footSensorShape;
    footSensorShape.SetAsBox(width, height, center, angle);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &footSensorShape;
    sensorFixtureDef.density = 1;
    sensorFixtureDef.isSensor = true;

    b2Fixture* footSensorFixture = physicalBody->CreateFixture(&sensorFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );
}

void Player::createLight()
{
    light = new ltbl::Light();
    light->center = Vec2f(graphicBody.getPosition().x, 1080 - graphicBody.getPosition().y);
    light->radius = LIGHT_RADIUS;
    light->size = 30.0f;
    light->softSpreadAngle = 0.0f;
    lightSystem.addLight(light);
}

void Player::moveLeft()
{
    if ( canIJump )
        move(-FORCE);
    else
        move(-AIR_FORCE);
}

void Player::moveRight()
{
    if ( canIJump )
        move(FORCE);
    else
        move(AIR_FORCE);
}

void Player::move(float force)
{
    physicalBody->ApplyForce(b2Vec2(force, 0), physicalBody->GetWorldCenter(), true);
}

void Player::jump()
{
    if ( canIJump )
    {
        float impulse = -physicalBody->GetMass() * IMPULSE;
        physicalBody->ApplyLinearImpulse(b2Vec2(0, impulse), physicalBody->GetWorldCenter(), true);
    }
}

void Player::applyAirResistance()
{
    float airDampingX = -physicalBody->GetLinearVelocity().x * abs(physicalBody->GetLinearVelocity().x) * AIR_RESISTANCE_X;
    float airDampingY = -physicalBody->GetLinearVelocity().y * abs(physicalBody->GetLinearVelocity().y) * AIR_RESISTANCE_Y;
    physicalBody->ApplyForce(b2Vec2(airDampingX, airDampingY), physicalBody->GetWorldCenter(), true);
}

void Player::update()
{
    GameObject::update();
    applyAirResistance();
    if (animationClock.getElapsedTime().asSeconds() > 0.1f){
        animation();
        animationClock.restart();
    }

    if (isInWater)
    {
        takeDamage();
    }

    light->center.x = graphicBody.getPosition().x;
    light->center.y = 1080 - graphicBody.getPosition().y;
    light ->updateTreeStatus();
}

void Player::changeDirection()
{
    if (isMovingRight())
        rotate(RIGHT);
    else if (isMovingLeft())
        rotate(LEFT);
}

void Player::rotate(Direction direction)
{
    graphicBody.setScale( { direction * objectScale, objectScale} );
}

void Player::animation()
{
    changeDirection();
    if (canIJump)
        runAnimation();
    else jumpAnimation();
}

void Player::jumpAnimation()
{
    if (isMovingUp())
    {
        imageIndex = RISE_IMG;
        graphicBody.setTextureRect(images.at(imageIndex));
    }
    else if (isMovingDown())
    {
        imageIndex = FALL_IMG;
        graphicBody.setTextureRect(images.at(imageIndex));
    }
    else stand();
}

void Player::runAnimation()
{
    if (isMovingLeft() or isMovingRight())
    {
        imageIndex++;
        if (imageIndex == 9) imageIndex = 0;
        graphicBody.setTextureRect(images.at(imageIndex));
    }
    else stand();
}

void Player::stand()
{
    if (imageIndex != STAND_IMG)
    {
        imageIndex = STAND_IMG;
        graphicBody.setTextureRect(images.at(imageIndex));
    }
}

bool Player::isMovingLeft()
{
    return physicalBody->GetLinearVelocity().x < -0.1;
}

bool Player::isMovingRight()
{
    return physicalBody->GetLinearVelocity().x > 0.1;
}

bool Player::isMovingUp()
{
    return physicalBody->GetLinearVelocity().y < -0.15;
}

bool Player::isMovingDown()
{
    return physicalBody->GetLinearVelocity().y > 0.15;
}

bool Player::checkIfIsInWater(float waterSurfacePosition)
{
    if (graphicBody.getPosition().y + graphicBody.getTextureRect().height * PLAYER_SCALE * 0.35 > waterSurfacePosition)
    {
        isInWater = true;
        return true;
    }
    isInWater = false;
    return false;

}

void Player::takeDamage()
{
    if (damageClock.getElapsedTime().asSeconds() > 0.3f){
        damageClock.restart();
        hp -= 5;
    }
}

void Player::killPlayer()
{
    if (damageClock.getElapsedTime().asSeconds() > 0.05f){
        damageClock.restart();
        hp -= 5;
    }
}
