#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Collectible {
    public:
        Collectible(float, float);
        ~Collectible();
    
        void draw(sf::RenderWindow&);
        sf::Sprite getSprite();
        virtual std::string getType();
        int getQuantity();
    
    protected:
        std::string type;
        sf::Sprite sprite;
        sf::Texture texture;
        int quantity;
};