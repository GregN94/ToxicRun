#ifndef SHADOW_OBJECT_HPP
#define SHADOW_OBJECT_HPP

#include <LTBL/LightSystem.h>

#include "GameObject.hpp"

class ShadowObject : public GameObject
{
public:
    ShadowObject(b2World& world,
                float positionX,
                float positionY,
                sf::Texture& texture,
                float scale,
                b2BodyType type,
                 ltbl::LightSystem& ls,
                float friction = FRICTION);
    ~ShadowObject();
    ltbl::ConvexHull* convexHull;
    ltbl::LightSystem& ls;

    void update() override;

};


#endif //SHADOW_OBJECT_HPP
