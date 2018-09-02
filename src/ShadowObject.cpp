#include "ShadowObject.hpp"

#include <iostream>

ShadowObject::ShadowObject(b2World &world,
                           float positionX,
                           float positionY,
                           sf::Texture &texture,
                           float scale,
                           b2BodyType type,
                           float friction)
       : GameObject(world,
                    positionX,
                    positionY,
                    texture,
                    scale,
                    type,
                    friction)
{
    convexHull = new ltbl::ConvexHull();
    ltbl::ConvexHullVertex newVertex;

    newVertex.position.x = static_cast<float>(-graphicBody.getTextureRect().width * scale / 2);
    newVertex.position.y = static_cast<float>(graphicBody.getTextureRect().height * scale / 2);
    convexHull->vertices.push_back(newVertex);

    newVertex.position.x = static_cast<float>(-graphicBody.getTextureRect().width * scale / 2);
    newVertex.position.y = static_cast<float>(-graphicBody.getTextureRect().height* scale  / 2);
    convexHull->vertices.push_back(newVertex);

    newVertex.position.x = static_cast<float>(graphicBody.getTextureRect().width * scale / 2);
    newVertex.position.y = static_cast<float>(-graphicBody.getTextureRect().height * scale / 2);
    convexHull->vertices.push_back(newVertex);

    newVertex.position.x = static_cast<float>(graphicBody.getTextureRect().width * scale / 2);
    newVertex.position.y = static_cast<float>(graphicBody.getTextureRect().height * scale / 2);
    convexHull->vertices.push_back(newVertex);

    convexHull->centerHull();
    convexHull->calculateNormals();
    convexHull->setWorldCenter(Vec2f(graphicBody.getPosition().x, 1080 - graphicBody.getPosition().y));
    convexHull->generateAABB();
}

void ShadowObject::update()
{
    GameObject::update();
    convexHull->setWorldCenter(Vec2f(graphicBody.getPosition().x, 1080 - graphicBody.getPosition().y));
    convexHull->generateAABB();
}
