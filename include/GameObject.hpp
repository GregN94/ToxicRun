#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <LTBL/LightSystem.h>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define DENSITY         1
#define FRICTION        0.5
#define BOX2D_SCALE     30

class IGameObject
{
public:
    virtual void update() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual void lower() = 0;
    virtual sf::Sprite getBody() = 0;
};

class GameObject : public IGameObject
{
public:
    GameObject(b2World& world,
               float positionX,
               float positionY,
               sf::Texture& texture,
               float scale,
               b2BodyType type,
               float friction = FRICTION,
               sf::Rect<int> textureRect = sf::Rect<int>());

    GameObject(){};

    void setPosition(float x, float y) override;
    void lower() override;
    void update() override;
    sf::Sprite getBody() override;

    void createGraphicBody(sf::Texture& texture, sf::Rect<int>rect, float positionX, float positionY);
    void createPhysicalBody(b2World& world,
                            b2BodyType type,
                            float positionX,
                            float positionY,
                            float widthScale,
                            float heightScale,
                            float density,
                            float friction);

    sf::Sprite graphicBody;
    b2Body* physicalBody;
    float objectScale;
    bool isMovingAllowed = true;
};

#endif // GAME_OBJECT_HPP
