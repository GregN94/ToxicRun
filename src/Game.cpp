
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

bool Game::run()
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
    return exit;
}

void Game::gameOverText()
{
    sf::Text gameOverText;
    gameOverText.setFont(font); // font is a sf::Font
    gameOverText.setCharacterSize(100); // in pixels, not points!

    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition( (float)window.getSize().x / 2,
                              (float)window.getSize().y / 2 );
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString("GAME OVER");
    gameOverText.setOrigin(gameOverText.getGlobalBounds().width / 2 , gameOverText.getGlobalBounds().height / 2);
    window.draw(gameOverText);

    sf::Text exitText;
    exitText.setFont(font); // font is a sf::Font
    exitText.setCharacterSize(64); // in pixels, not points!

    exitText.setFillColor(sf::Color::Yellow);
    exitText.setPosition( (float)window.getSize().x / 2,
                          (float)window.getSize().y / 2 + 100 );
    exitText.setStyle(sf::Text::Bold);
    exitText.setString("EXIT");
    exitText.setOrigin(exitText.getGlobalBounds().width / 2 , exitText.getGlobalBounds().height / 2);
    window.draw(exitText);
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
    if (player->graphicBody.getPosition().y < (float)window.getSize().y / 2)
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
        gameOverText();
        mouseInput();
    }
    window.display();
}

void Game::mouseInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition();
        if (position.x > 860 and position.x < 1060 and position.y > 635 and position.y < 685)
            exit = true;
    }

}


