#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Water.hpp"

#define FORCE           60
#define AIR_FORCE       25
#define MASS            18
#define IMPULSE         5
#define PLAYER_SCALE    0.3
#define LIGHT_RADIUS    600
#define AIR_RESISTANCE_X  0.8
#define AIR_RESISTANCE_Y  0.3

enum Direction
{
    LEFT = -1,
    RIGHT = 1
};

class Player : public GameObject
{
public:
    Player(b2World& world,
           float x,
           float y,
           sf::Texture& texture,
           ltbl::LightSystem& lightSystem,
           float scale = PLAYER_SCALE);
    ~Player() override;
    void update() override;
    void moveLeft();
    void moveRight();
    void jump();
    bool checkIfIsInWater(float waterSurfacePosition);
    int getHp() { return hp; }
    void takeDamage();

    bool canIJump = true;

private:
    void applyAirResistance();
    void rotate(Direction direction);
    void changeDirection();
    void createLight();
    void createFootSensor();
    void animation();
    void runAnimation();
    void jumpAnimation();
    void move(float force);
    void stand();
    bool isMovingLeft();
    bool isMovingRight();
    bool isMovingUp();
    bool isMovingDown();

    int imageIndex = 8;
    sf::Clock animationClock;
    sf::Clock damageClock;
    ltbl::LightSystem& lightSystem;
    ltbl::Light* light;

    int hp = 100;
    bool isInWater = false;
};

#endif // PLAYER_HPP
