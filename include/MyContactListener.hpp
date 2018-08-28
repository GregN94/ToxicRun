#ifndef MY_CONTACT_LISTENER_HPP
#define MY_CONTACT_LISTENER_HPP

#include <Box2D/Box2D.h>

class MyContactListener : public b2ContactListener
{
public:
    explicit MyContactListener(bool* canIJump);
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
    bool* canIJump;
};


#endif MY_CONTACT_LISTENER_HPP
