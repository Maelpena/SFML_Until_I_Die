#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "game.h"
#include <vector>

int main()
{
    sf::Texture mapTexture;
    mapTexture.loadFromFile("./sprite/map.jpg");
    //Game *game = new Game(mapTexture.getSize());
    Game *game = new Game(mapTexture.getSize());
    game->update();
    delete game;
    return 0;
}



