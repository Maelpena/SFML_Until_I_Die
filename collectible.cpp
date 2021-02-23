
#include "collectible.h"
#include <iostream>

Collectible::Collectible(float posX, float posY)
{
    sprite.setPosition(posX, posY);
}

Collectible::~Collectible(){

}

sf::Sprite Collectible::getSprite(){
    return sprite;
}

std::string Collectible::getType()
{
    return type;
}


void Collectible::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

int Collectible::getQuantity()
{
    return quantity;
}