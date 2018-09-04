#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

#define MAX_SPEED       3.5
#define FORCE           1000
#define AIR_FORCE       60
#define MASS            18
#define IMPULSE         2.7
#define PLAYER_SCALE    0.3
#define LIGHT_RADIUS    1500

enum Direction
{
    LEFT = -1,
    RIGHT = 1
};

class Player : public GameObject
{
public:
    Player(b2World& world, float x, float y, sf::Texture& texture, float scale = PLAYER_SCALE);
    void update() override;
    void moveLeft();
    void moveRight();
    void jump();

    ltbl::Light* light;
    bool canIJump = true;

private:
    void rotate(Direction direction);
    void changeDirection();
    void createLight();
    void createFootSensor();
    void animation();
    void runAnimation();
    void jumpAnimation();
    void move(bool predicate, float force);
    void stand();
    bool isMovingLeft();
    bool isMovingRight();
    bool isMovingUp();
    bool isMovingDown();

    int imageIndex = 8;
    sf::Clock clock;
};

#endif // PLAYER_HPP
