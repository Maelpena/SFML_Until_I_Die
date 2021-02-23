#include "gameover.h"
#include "game.h"
#include <vector>
#include <math.h>

Gameover::Gameover() {
    itbackground = 0;

    gbgTexture.loadFromFile("./sprite/gameoverbg.jpg");
    gbackground.setTexture(gbgTexture);
    gbackground.setScale(4, 6);
    gbackground.setPosition(sf::Vector2f(0, 0));
    gbackground.setColor(sf::Color(0, 0, 0, 0));

    replayButtonTexture.loadFromFile("./sprite/replay.png");
    replayButton.setTexture(replayButtonTexture);
    replayButton.setPosition(sf::Vector2f(200, 450));
    replayButton.setScale(0.08f, 0.08f);

    quitButtonTexture.loadFromFile("./sprite/escape.png");
    quitButton.setTexture(quitButtonTexture);
    quitButton.setPosition(sf::Vector2f(500, 370));
    quitButton.setScale(0.3f, 0.3f);

    font.loadFromFile("./font/m39.TTF");
    gameoverText.setFont(font);
    gameoverText.setString("VOUS ETES MORT");
    gameoverText.setPosition(100, 200);
    gameoverText.setCharacterSize(55);
    gameoverText.setFillColor(sf::Color::White);
    gameoverText.setStyle(sf::Text::Bold);
}

Gameover::~Gameover() {}

void Gameover::gameOverCommand(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > 220 && position.x < 350 &&
            position.y > 465 && position.y < 600) 
        {
            Game::restart();  
            itbackground = 0;  

        } 
        else if (position.x > 570 && position.x < 795 &&
            position.y > 490 && position.y < 600)
        {
            window.close();
        }
    }
}

void Gameover::draw(sf::RenderWindow& window, float deltatime)
{
    window.draw(gbackground);

    if (itbackground < 200)
    {
        itbackground += deltatime * 100;
        gbackground.setColor(sf::Color(0, 0, 0, itbackground));
    }
    else {
        window.draw(gameoverText);
        window.draw(replayButton);
        window.draw(quitButton);
    }
}

