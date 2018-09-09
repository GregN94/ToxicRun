
#include <GameObject.hpp>

#include "GameObject.hpp"

GameObject::GameObject(b2World& world,
                       float positionX,
                       float positionY,
                       sf::Texture& texture,
                       float scale,
                       b2BodyType type,
                       float friction,
                       sf::Rect<int> textureRect)
{
    objectScale = scale;
    createGraphicBody(texture, textureRect, positionX, positionY);
    createPhysicalBody(world, type, positionX, positionY, 1, 1, DENSITY, friction);

    graphicBody.setRotation(physicalBody->GetAngle() * 180 / b2_pi);
    physicalBody->SetSleepingAllowed(true);
}

void GameObject::createPhysicalBody(b2World& world,
                                    b2BodyType type,
                                    float positionX,
                                    float positionY,
                                    float widthScale,
                                    float heightScale,
                                    float density,
                                    float friction)
{
    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(positionX / BOX2D_SCALE, positionY / BOX2D_SCALE);
    bodyDef.type = type;
    physicalBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape;
    shape.SetAsBox(graphicBody.getTextureRect().width  * widthScale  * objectScale / (2 * BOX2D_SCALE),
                   graphicBody.getTextureRect().height * heightScale * objectScale / (2 * BOX2D_SCALE));

    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.shape = &shape;
    physicalBody->CreateFixture(&fixtureDef);
}

void GameObject::createGraphicBody(sf::Texture& texture, sf::Rect<int>rect, float positionX, float positionY)
{
    graphicBody.setTexture(texture);
    if (rect.height != 0 && rect.width != 0)
    {
        graphicBody.setTextureRect(rect);
    }
    graphicBody.setOrigin( (float) graphicBody.getTextureRect().width / 2,
                           (float) graphicBody.getTextureRect().height / 2);

    graphicBody.setPosition(positionX, positionY);
    graphicBody.setScale(objectScale, objectScale);
}

void GameObject::lower()
{
    if (isMovingAllowed)
    {
        float y = 0.035;
        physicalBody->SetTransform(b2Vec2(physicalBody->GetPosition().x, physicalBody->GetPosition().y + y),
                                   physicalBody->GetAngle());
    }
}

void GameObject::update()
{
    graphicBody.setPosition(physicalBody->GetPosition().x * BOX2D_SCALE,
                            physicalBody->GetPosition().y * BOX2D_SCALE);
    graphicBody.setRotation(180 / b2_pi * physicalBody->GetAngle());
}

sf::Sprite GameObject::getBody()
{
    return graphicBody;
}

sf::Vector2f GameObject::getPosition()
{
    return graphicBody.getPosition();

}

GameObject::~GameObject()
{
    physicalBody->GetWorld()->DestroyBody(physicalBody);

}
