#include "bullet.h"


Bullet::Bullet(float posX0, float posY0, float dirX0, float dirY0, float damage){

    texture.loadFromFile("./sprite/Bullet.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.5f, 0.5f)); 
    sprite.setOrigin(sf::Vector2f(10.f, 10.f));
    sprite.setColor(sf::Color::Red);

    this->posX = posX0;
    this->posY = posY0;     
    this->dirX = dirX0;
    this->dirY = dirY0;
    movementSpeed = 1000;
    this->damage = damage;
};


Bullet::~Bullet(){};

void Bullet::move(float time){
        posX += time * movementSpeed * dirX;
        posY += time * movementSpeed * dirY;
        sprite.setPosition(posX, posY);
}

sf::Sprite Bullet::getSprite()
{
    return sprite;
}


float Bullet::getDamage()
{
    return damage;
}


void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}