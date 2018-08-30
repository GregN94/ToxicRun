#include "Player.hpp"
#include <iostream>

#define MAX_SPEED   4
#define FORCE       1000
#define AIR_FORCE   60


std::vector<sf::IntRect> drawings = {sf::IntRect(0,    0,   480,  440),
                                     sf::IntRect(480,  0,   480,  440),
                                     sf::IntRect(960,  0,   480, 440),
                                     sf::IntRect(1440, 0,   480, 440),
                                     sf::IntRect(0,    440, 480,  440),
                                     sf::IntRect(480,  440, 480,  440),
                                     sf::IntRect(960,  440, 480, 440),
                                     sf::IntRect(1440, 440, 480, 440)};

Player::Player(b2World& world, float positionX, float positionY, sf::Texture& texture, float scale)
{
    playerScale = scale;
    graphicBody.setTexture(texture);
    graphicBody.setTextureRect(drawings.at(drawingIndex));
    graphicBody.setOrigin( (float) graphicBody.getTextureRect().width / 2,
                           (float) graphicBody.getTextureRect().height / 2);

    graphicBody.setPosition(positionX, positionY);
    graphicBody.setScale(playerScale, playerScale);


    b2BodyDef body;
    body.position = b2Vec2(positionX / BOX2D_SCALE, positionY / BOX2D_SCALE);
    body.type = b2_dynamicBody;
    physicalBody = world.CreateBody(&body);
    b2PolygonShape shape;
    shape.SetAsBox(graphicBody.getTextureRect().width  * 0.3 * playerScale  / (2 * BOX2D_SCALE),
                   graphicBody.getTextureRect().height * 0.75 *playerScale  / (2 * BOX2D_SCALE));

    b2FixtureDef fixtureDef;
    fixtureDef.density = DENSITY;
    fixtureDef.friction = FRICTION;
    fixtureDef.shape = &shape;
    physicalBody->CreateFixture(&fixtureDef);
    physicalBody->SetUserData( (void*)1 );

    graphicBody.setRotation(physicalBody->GetAngle() * 180 / b2_pi);
    physicalBody->SetSleepingAllowed(true);

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(0.3, 0.3, b2Vec2(0, graphicBody.getTextureRect().height *0.75* playerScale / (2 * BOX2D_SCALE)), 0);

    //fixture definition
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1;
    myFixtureDef.isSensor = true;

    //add main fixture
    physicalBody->CreateFixture(&myFixtureDef);

    b2Fixture* footSensorFixture = physicalBody->CreateFixture(&myFixtureDef);
    footSensorFixture->SetUserData( (void*)3 );

    b2MassData mass{18, physicalBody->GetLocalCenter(), physicalBody->GetInertia()};
    physicalBody->SetMassData(&mass);
    physicalBody->SetAngularDamping(2);
    physicalBody->SetSleepingAllowed(false);

    physicalBody->SetFixedRotation(true);


    testLight = new ltbl::Light();
    testLight->center = Vec2f(200.0f, 200.0f);
    testLight->radius = 700.0f;
    testLight->size = 20.0f;
    testLight->softSpreadAngle = 0.0f;
    testLight->calculateAABB();
}

void Player::moveLeft()
{
    if ( canIJump )
        move(physicalBody->GetLinearVelocity().x > -MAX_SPEED, -FORCE);
    else
        move(physicalBody->GetLinearVelocity().x > -MAX_SPEED, -AIR_FORCE);
}

void Player::moveRight()
{
    if ( canIJump )
        move(physicalBody->GetLinearVelocity().x < MAX_SPEED, FORCE);
    else
        move(physicalBody->GetLinearVelocity().x < MAX_SPEED, AIR_FORCE);
}

void Player::move(bool predicate, float force)
{
    if (predicate)
        physicalBody->ApplyForce(b2Vec2(force, 0), physicalBody->GetWorldCenter(), true);
}

void Player::jump()
{
    if ( canIJump )
    {
        float impulse = -physicalBody->GetMass() * 2.7;
        physicalBody->ApplyLinearImpulse(b2Vec2(0, impulse), physicalBody->GetWorldCenter(), true);
    }
}

void Player::update()
{
    GameObject::update();
    if (clock.getElapsedTime().asSeconds() > 0.1f){
        animate();
        clock.restart();
    }
    testLight->center.x = graphicBody.getPosition().x;
    testLight->center.y = 1080 - graphicBody.getPosition().y;
    testLight->updateTreeStatus();
}

void Player::animate()
{
    if (physicalBody->GetLinearVelocity().x > 0.1)
    {
        animateRight();
    }
    else if (physicalBody->GetLinearVelocity().x < -0.1)
    {
        animateLeft();
    }
    else if (drawingIndex != 7 and drawingIndex != 3)
    {
        drawingIndex = 3;
        graphicBody.setTextureRect(drawings.at(drawingIndex));
    }
}

void Player::animateLeft()
{
    animateRun();
    graphicBody.setScale({-playerScale, playerScale});
}

void Player::animateRight()
{
    animateRun();
    graphicBody.setScale({playerScale, playerScale});
}

void Player::animateRun()
{
    drawingIndex++;
    if (drawingIndex == 8) drawingIndex = 1;
    graphicBody.setTextureRect(drawings.at(drawingIndex));
}