#include "GameObject.hpp"
#include "GameObjects.hpp"
#include "Player.hpp"
#include "MyContactListener.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

int main()
{
    unsigned int SCREEN_WIDTH = 1920;
    unsigned int SCREEN_HEIGHT = 1080;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "ToxicRun", sf::Style::Fullscreen);
//    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "ToxicRun");
    b2Vec2 gravity(0.f, 9.8f / 20);
    b2World world(gravity);
    bool canIJump = true;
    MyContactListener myContactListenerInstance(&canIJump);

    //in FooTest constructor
    world.SetContactListener(&myContactListenerInstance);

    sf::Texture groundTexture;
    sf::Texture playerTexture;
    sf::Texture  wallTexture;

    groundTexture.loadFromFile("../res/ground.png");
    playerTexture.loadFromFile("../res/human.png");
    wallTexture.loadFromFile("../res/brick.png");

    GameObjects gameObjects;

    GameObject wall(world,
                    (float) wallTexture.getSize().x / 4,
                    SCREEN_HEIGHT - (float) wallTexture.getSize().y / 4,
                    wallTexture,
                    0.5,
                    b2_staticBody);
    gameObjects.add(wall);
    GameObject wall2(world,
                     (float) wallTexture.getSize().x / 4,
                     SCREEN_HEIGHT - 3 * (float) wallTexture.getSize().y / 4,
                     wallTexture,
                     0.5,
                     b2_staticBody);
    gameObjects.add(wall2);
    GameObject wall3(world,
                     SCREEN_WIDTH - wallTexture.getSize().x / 4,
                     SCREEN_HEIGHT - wallTexture.getSize().y / 4,
                     wallTexture,
                     0.5,
                     b2_staticBody);
    gameObjects.add(wall3);
    GameObject wall4(world,
                     SCREEN_WIDTH - wallTexture.getSize().x / 4,
                     SCREEN_HEIGHT - 3 * wallTexture.getSize().y / 4,
                     wallTexture,
                     0.5,
                     b2_staticBody);
    gameObjects.add(wall4);

    GameObject ground(world,
                      SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT - groundTexture.getSize().y / 2,
                      groundTexture,
                      2,
                      b2_staticBody);
    gameObjects.add(ground);

    GameObject platform(world,
                        SCREEN_WIDTH / 2,
                        SCREEN_HEIGHT - 200,
                        groundTexture,
                        0.5,
                        b2_staticBody);
    gameObjects.add(platform);


    std::shared_ptr<Player>  player = std::make_shared<Player>(world, SCREEN_WIDTH / 2, SCREEN_HEIGHT - groundTexture.getSize().y, playerTexture);
    gameObjects.add(player);


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player->moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player->moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if ( canIJump )
                player->jump();
        }

        gameObjects.update();
        gameObjects.draw(window);
        window.display();

        world.Step(1/60.f, 8, 3);

    }
    return 0;
}
