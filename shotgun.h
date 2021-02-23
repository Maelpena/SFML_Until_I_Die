#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "bullet.h"
#include "weapon.h"

class Shotgun : public Weapon 
{
public:
    Shotgun();
    ~Shotgun();
    std::string getType();
private:
    std::string type;
};