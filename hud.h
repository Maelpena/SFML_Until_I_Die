#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "weapon.h"
#include "player.h"
#include "collectible.h"

class Hud 
{
public:
    Hud(Player*, float, float);
    ~Hud();
    sf::Text createTextWidget(int, int, int, int);
    void update(float);
    void draw(sf::RenderWindow&);
    void playerHit();

private:
    Player* player;
    sf::Font font1;
    sf::Font font2;
    sf::RectangleShape bgLifeBar;
    sf::RectangleShape lifeBar;
    sf::Text lifeText;
    sf::RectangleShape bgXpBar;
    sf::RectangleShape xpBar;
    sf::Text levelText;
    sf::Text killCountText;
    sf::Text killSerieText;
    sf::Text xpText;
    sf::Text magazineText;
    sf::Text ammoText;
    sf::Text waveText;
    sf::Text zombieAliveText;
    sf::Texture bloodTexture;
    sf::Sprite blood;
    float playerBloodTime;
};
