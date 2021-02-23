#include "menu.h"
#include <vector>
#include <math.h>


Menu::Menu() {

    bgTexture.loadFromFile("./sprite/menu_bg.jpg");
    background.setTexture(bgTexture);
    background.setScale(0.85f, 0.85f);
    background.setPosition(sf::Vector2f(-100, -10));
    playButtonTexture.loadFromFile("./sprite/playButton.png");
    playButton.setTexture(playButtonTexture);
    playButton.setPosition(sf::Vector2f(450, 200));
    playButton.setScale(0.4f, 0.4f);
    quitButtonTexture.loadFromFile("./sprite/quitButton.png");
    quitButton.setTexture(quitButtonTexture);
    quitButton.setPosition(sf::Vector2f(450, 450));
    quitButton.setScale(0.4f, 0.4f);
    font.loadFromFile("font/m39.TTF");
    gameName.setFont(font);
    gameName.setString("UNTIL I DIE");
    gameName.setPosition(370, 100);
    gameName.setCharacterSize(50);
    gameName.setFillColor(sf::Color::Black);
    gameName.setStyle(sf::Text::Bold);
}

Menu::~Menu(){}

float Menu::getTime() {
        sf::Clock Clock;
        sf::Time elapsed = Clock.getElapsedTime();
        float time = elapsed.asMicroseconds();
        Clock.restart();

        return time;
}


bool Menu::mainMenuCommand(sf::RenderWindow& window) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        if (position.x > 535 && position.x < 790 &&
            position.y > 265 && position.y < 415) 
        {
            return true;
        } 
        else if (position.x > 540 && position.x < 790 &&
            position.y > 515 && position.y < 660)
        {
            window.close();
        }
        else
            return false;
    }
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(playButton);
    window.draw(quitButton);
    window.draw(gameName);
}