#include "GameObject.hpp"
#include "GameObjects.hpp"
#include "Player.hpp"
#include "MyContactListener.hpp"
#include "ShadowObject.hpp"
#include "MapGenerator.hpp"

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <LTBL/LightSystem.h>
#include <iostream>
#include <Water.hpp>

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGHT   1080
#define BITS_PER_PIXEL  32
#define GRAVITY         9.8

void closeWindow(sf::RenderWindow& window);

int main()
{
    sf::VideoMode videoMode(SCREEN_WIDTH, SCREEN_HEIGHT, BITS_PER_PIXEL);
    sf::RenderWindow window(videoMode, "ToxicRun", sf::Style::Fullscreen);

    ltbl::LightSystem lightSystem(qdt::AABB(Vec2f(0.0f, 0.0f), Vec2f(static_cast<float>(videoMode.width),
                                  static_cast<float>(videoMode.height))),
                                  &window);

    b2World world(b2Vec2(0.f, GRAVITY));

    GameObjects gameObjects;
    gameObjects.loadTextures();

    std::shared_ptr<Player> player = gameObjects.createPlayer(world, videoMode, lightSystem);

    gameObjects.createGround(world, videoMode);
    gameObjects.createWalls(world, videoMode);
    MapGenerator mapGenerator(gameObjects, videoMode, lightSystem, world);
    mapGenerator.generateMap();


    MyContactListener myContactListenerInstance(&player->canIJump);
    world.SetContactListener(&myContactListenerInstance);
    Water water(videoMode);

    while (window.isOpen())
    {
        closeWindow(window);
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

        if (player->graphicBody.getPosition().y < SCREEN_HEIGHT / 2)
        {
            gameObjects.lower();
            water.lower();
        }

        gameObjects.update();
        gameObjects.draw(window);
        mapGenerator.update();

        water.update();
        water.draw(window);

        lightSystem.renderLights(); // Calculate the lights
        lightSystem.renderLightTexture(0.0f); // Draw the lights

        window.display();
        world.Step(1 / 60.f, 8, 3);

    }
    return 0;
}

void closeWindow(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}
