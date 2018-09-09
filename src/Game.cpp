
#include <Game.hpp>

#include "Game.hpp"

#define GRAVITY         9.8


Game::Game(sf::VideoMode videoMode, sf::RenderWindow& window)
    : window(window),
      lightSystem(qdt::AABB(Vec2f(0.0f, 0.0f),
                  Vec2f(static_cast<float>(videoMode.width),
                        static_cast<float>(videoMode.height))),
                  &window),
      world(b2Vec2(0.f, GRAVITY)),
      player(gameObjects.createPlayer(world, videoMode, lightSystem)),
      mapGenerator(gameObjects, videoMode, lightSystem, world),
      myContactListener(&player->canIJump),
      stats(window, font),
      water(videoMode)
{
}

void Game::setUp(sf::VideoMode videoMode)
{
    font.loadFromFile("../res/Arial.ttf");

    gameObjects.loadTextures();
    gameObjects.createGround(world, videoMode);
    gameObjects.createWalls(world, videoMode);

    mapGenerator.generateMap();

    world.SetContactListener(&myContactListener);
    lightSystem.ambientColor = sf::Color(8, 8, 8);
    water = Water(videoMode);
}

void Game::run()
{
    controlPlayer();
    cameraFollowPlayer();

    if (player->getHp() > 0)
    {
        gameObjects.update();
        mapGenerator.update();
        water.update();
        if (player.use_count() == 1)
        {
            player->killPlayer();
        }
        stats.update(player->getHp(), gameObjects.getDistance());
    }

    player->checkIfIsInWater(water.getSurfacePosition());

    draw();
    world.Step(1 / 60.f, 8, 3);
}

sf::Text Game::gameOverText(sf::RenderWindow& window)
{
    sf::Text gameOverText;
    gameOverText.setFont(font); // font is a sf::Font
    gameOverText.setCharacterSize(100); // in pixels, not points!

    gameOverText.setFillColor(sf::Color::Green);
    gameOverText.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString("GAME OVER");
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2 , gameOverText.getGlobalBounds().height / 2);
    return gameOverText;
}

void Game::controlPlayer()
{
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
}

void Game::cameraFollowPlayer()
{
    if (player->graphicBody.getPosition().y < window.getSize().y / 2)
    {
        gameObjects.lower();
        water.lower();
    }
}

void Game::draw()
{
    gameObjects.draw(window);
    water.draw(window);

    lightSystem.renderLights(); // Calculate the lights
    lightSystem.renderLightTexture(0.0f); // Draw the lights

    stats.draw();

    if (player->getHp() <= 0)
    {
        window.draw(gameOverText(window));
    }
    window.display();
}


