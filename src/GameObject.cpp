#include "GameObject.hpp"

GameObject::GameObject(b2World& world, float positionX, float positionY, sf::Texture& texture, float scale, b2BodyType type)
{
    graphicBody.setTexture(texture);
    graphicBody.setOrigin(graphicBody.getTextureRect().width / 2, graphicBody.getTextureRect().height / 2);
    graphicBody.setPosition(positionX, positionY);
    graphicBody.setScale(scale, scale);
    b2BodyDef body;
    body.position = b2Vec2(positionX / SCALE, positionY / SCALE);
    body.type = type;
    physicalBody = world.CreateBody(&body);
    shape.SetAsBox(graphicBody.getTextureRect().width  * scale / (2 * SCALE), graphicBody.getTextureRect().height * scale / (2 * SCALE));
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.2f;
    FixtureDef.shape = &shape;
    physicalBody->CreateFixture(&FixtureDef);

    graphicBody.setRotation(physicalBody->GetAngle() * 180 / b2_pi);
    physicalBody->SetSleepingAllowed(true);
}

void GameObject::setPosition(float x, float y)
{
    b2Vec2 vect = b2Vec2(x / 30, y / 30);
    physicalBody->SetTransform(vect, 0);
    graphicBody.setPosition(x, y);
}

void GameObject::update()
{
    graphicBody.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
    graphicBody.setRotation(180 / b2_pi * physicalBody->GetAngle());
}

sf::Sprite GameObject::getBody()
{
    return graphicBody;
}
