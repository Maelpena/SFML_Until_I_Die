#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Game;

class Gameover {
public:
    Gameover();
    ~Gameover();

    void gameOverCommand(sf::RenderWindow&);
    void draw(sf::RenderWindow&, float);

private:
    sf::Sprite          gbackground;
    sf::Texture         gbgTexture;
    float               itbackground;
    sf::Sprite          replayButton;
    sf::Texture         replayButtonTexture;
    sf::Sprite          quitButton;
    sf::Texture         quitButtonTexture;
    sf::Font            font;
    sf::Text            gameoverText;
};