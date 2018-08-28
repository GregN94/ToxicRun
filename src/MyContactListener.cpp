#include "MyContactListener.hpp"

MyContactListener::MyContactListener(bool *canIJump)
    : canIJump(canIJump)
{
}

void MyContactListener::BeginContact(b2Contact *contact)
{
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (long)fixtureUserData == 3 )
    {
        *this->canIJump = true;
    }

    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (long)fixtureUserData == 3 )
    {
        *this->canIJump = true;
    }
}

void MyContactListener::EndContact(b2Contact* contact) {
    //check if fixture A was the foot sensor
    void* fixtureUserData = contact->GetFixtureA()->GetUserData();
    if ( (long)fixtureUserData == 3 )
    {
        *this->canIJump = false;
    }
    //check if fixture B was the foot sensor
    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if ( (long)fixtureUserData == 3 )
    {
        *this->canIJump = false;
    }
}