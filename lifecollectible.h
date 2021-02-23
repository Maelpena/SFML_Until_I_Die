#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "collectible.h"


class LifeCollectible : public Collectible 
{
public:
    LifeCollectible(float, float);
    ~LifeCollectible();

    std::string getType();
private:
    std::string type;
};