#include "handgunammo.h"
#include "collectible.h"
#include <iostream>

HandgunAmmo::HandgunAmmo(float posX, float posY) : Collectible( posX, posY)
{
    texture.loadFromFile("./sprite/handgun_aimo.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f)); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); 
    quantity = 30;
    type = "handgun";

}

std::string HandgunAmmo::getType()
{
    return type;
}
    
HandgunAmmo::~HandgunAmmo(){}