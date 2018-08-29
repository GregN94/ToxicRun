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

    b2Vec2 gravity(0.f, 9.8f / 10);
    b2World world(gravity);
    bool canIJump = true;
    MyContactListener myContactListenerInstance(&canIJump);

    //in FooTest constructor
    world.SetContactListener(&myContactListenerInstance);

    sf::Texture groundTexture;
    sf::Texture playerTexture;
    sf::Texture  wallTexture;
    sf::Texture  platformTexture;
    sf::Texture backgroundTexture;

    groundTexture.loadFromFile("../res/ground.png");
    playerTexture.loadFromFile("../res/runner2.png");
    wallTexture.loadFromFile("../res/wall.png");
    platformTexture.loadFromFile("../res/platform.png");
    backgroundTexture.loadFromFile("../res/background.png");
    sf::Sprite background(backgroundTexture);

    GameObjects gameObjects;


    GameObject ground(world,
                      SCREEN_WIDTH / 2,
                      SCREEN_HEIGHT - groundTexture.getSize().y / 2,
                      groundTexture,
                      1,
                      b2_staticBody);
    gameObjects.add(ground);
    
    GameObject wall(world,
                    (float) wallTexture.getSize().x / 2,
                    SCREEN_HEIGHT - (float) wallTexture.getSize().y / 2,
                    wallTexture,
                    1,
                    b2_staticBody,
                    0);
    gameObjects.add(wall);
    GameObject wall3(world,
                     SCREEN_WIDTH - wallTexture.getSize().x / 2,
                     SCREEN_HEIGHT - wallTexture.getSize().y / 2,
                     wallTexture,
                     1,
                     b2_staticBody,
                     0);
    gameObjects.add(wall3);



    GameObject platform(world,
                        SCREEN_WIDTH / 2,
                        SCREEN_HEIGHT - 200,
                        platformTexture,
                        0.5,
                        b2_staticBody);
    gameObjects.add(platform);

    GameObject platform2(world,
                        SCREEN_WIDTH / 2 + 100,
                        SCREEN_HEIGHT / 2 + 200,
                        platformTexture,
                        0.5,
                        b2_staticBody);
    gameObjects.add(platform2);


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

        window.draw(background);
        gameObjects.update();
        gameObjects.draw(window);
        window.display();

        world.Step(1/60.f, 8, 3);

    }
    return 0;
}
