#include "shotgunammo.h"
#include "collectible.h"
#include <iostream>

ShotgunAmmo::ShotgunAmmo(float posX, float posY) : Collectible( posX, posY)
{
    texture.loadFromFile("./sprite/shotgun_aimo.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(1.f, 1.f)); 
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); 
    quantity = 15;
    type = "shotgun";

}
std::string ShotgunAmmo::getType()
{
    return type;
}

ShotgunAmmo::~ShotgunAmmo(){}