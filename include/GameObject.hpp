#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class IGameObject
{
public:
    virtual void update() = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::Sprite getBody() = 0;
};

class GameObject : public IGameObject
{
public:
    float SCALE = 30.f;
    GameObject(b2World& world, float x, float y, sf::Texture& texture, float scale, b2BodyType type);
    void setPosition(float x, float y) override;
    void update() override;
    sf::Sprite getBody() override;

    sf::Sprite graphicBody;
    b2Body* physicalBody;
    b2PolygonShape Shape;
};

class GameObjects
{
public:
    GameObjects() {objectList.reserve(40);}
    void update();
    void add(GameObject);
    void draw(sf::RenderWindow&);

    std::vector<std::shared_ptr<IGameObject>> objectList;
    void add(std::shared_ptr<IGameObject> object_ptr);
};

#endif // GAMEOBJECT_HPP
