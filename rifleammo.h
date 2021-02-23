#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "collectible.h"


class RifleAmmo : public Collectible 
{
public:
    RifleAmmo(float, float);
    ~RifleAmmo();

    std::string getType();
private:
    std::string type;
};