#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "zombie.h"
#include "redzombie.h"
#include "greenzombie.h"

class Bullet  {
    public:
        Bullet(float, float, float, float, float);
        ~Bullet();

        void move(float);
        sf::Sprite getSprite();
        float getDamage();
        void draw(sf::RenderWindow&);

    private:

        sf::Sprite sprite; 
        sf::Texture texture;
        sf::CircleShape shape;

        float damage;
        float movementSpeed;
        float posX;
        float posY;
        float dirX;
        float dirY;
};