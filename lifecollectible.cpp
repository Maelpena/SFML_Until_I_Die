#include "lifecollectible.h"
#include "collectible.h"
#include <iostream>

LifeCollectible::LifeCollectible(float posX, float posY) : Collectible( posX, posY)
{
    texture.loadFromFile("./sprite/life_collectible.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.13f, 0.13f)); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); 
    quantity = 10;
    type = "life";

}

std::string LifeCollectible::getType()
{
    return type;
}
    
LifeCollectible::~LifeCollectible(){}