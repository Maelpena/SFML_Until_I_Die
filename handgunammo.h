#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "collectible.h"


class HandgunAmmo : public Collectible 
{
public:
    HandgunAmmo(float, float);
    ~HandgunAmmo();

    std::string getType();
private:
    std::string type;
};