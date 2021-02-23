#include "rifleammo.h"
#include "collectible.h"
#include <iostream>

RifleAmmo::RifleAmmo(float posX, float posY) : Collectible( posX, posY)
{
    texture.loadFromFile("./sprite/rifle_aimo.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f)); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); 
    quantity = 60;
    type = "rifle";

}
    
std::string RifleAmmo::getType()
{
    return type;
}
    
RifleAmmo::~RifleAmmo(){}