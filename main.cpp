#include "GameObject.hpp"
#include "GameObjects.hpp"
#include "Player.hpp"
#include "MyContactListener.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <LTBL/LightSystem.h>
#include <iostream>

int main()
{
    unsigned int SCREEN_WIDTH = 1920;
    unsigned int SCREEN_HEIGHT = 1080;
    sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "ToxicRun", sf::Style::Fullscreen);

    ltbl::LightSystem ls(qdt::AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(videoMode.width), static_cast<float>(videoMode.height))), &window);

    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);

    sf::Texture groundTexture;
    sf::Texture playerTexture;
    sf::Texture wallTexture;
    sf::Texture platformTexture;

    groundTexture.loadFromFile("../res/ground.png");
    playerTexture.loadFromFile("../res/runner2.png");
    wallTexture.loadFromFile("../res/wall.png");
    platformTexture.loadFromFile("../res/platform.png");

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
                    b2_staticBody);
    gameObjects.add(wall);
    GameObject wall3(world,
                     SCREEN_WIDTH - wallTexture.getSize().x / 2,
                     SCREEN_HEIGHT - wallTexture.getSize().y / 2,
                     wallTexture,
                     1,
                     b2_staticBody);
    gameObjects.add(wall3);


    GameObject platform(world,
                        SCREEN_WIDTH / 2,
                        SCREEN_HEIGHT - 200,
                        platformTexture,
                        0.5,
                        b2_staticBody);
    gameObjects.add(platform);

    GameObject platform2(world,
                        SCREEN_WIDTH / 2 + 200,
                        SCREEN_HEIGHT / 2 + 200,
                        platformTexture,
                        0.5,
                        b2_staticBody);
    gameObjects.add(platform2);

    GameObject platform3(world,
                         SCREEN_WIDTH / 2 + 400,
                         SCREEN_HEIGHT / 2,
                         platformTexture,
                         0.5,
                         b2_staticBody);
    gameObjects.add(platform3);

    std::shared_ptr<Player>  player = std::make_shared<Player>(world, SCREEN_WIDTH / 2, SCREEN_HEIGHT - groundTexture.getSize().y, playerTexture);
    gameObjects.add(player);
    ls.addLight(player->testLight);

    MyContactListener myContactListenerInstance(&player->canIJump);
    world.SetContactListener(&myContactListenerInstance);

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
            player->jump();
        }

        gameObjects.update();
        gameObjects.draw(window);

        // Calculate the lights
        ls.renderLights();
        // Draw the lights
        ls.renderLightTexture(0.0f);

        window.display();

        world.Step(1/60.f, 8, 3);
    }
    return 0;
}
