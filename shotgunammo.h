#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "collectible.h"


class ShotgunAmmo : public Collectible 
{
public:
    ShotgunAmmo(float, float);
    ~ShotgunAmmo();
    
    std::string getType();
private:
    std::string type;
};