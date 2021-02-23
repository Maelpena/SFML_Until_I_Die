#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "bullet.h"
#include "weapon.h"

class Handgun : public Weapon 
{
public:
    Handgun();
    ~Handgun();

    std::string getType();
private:
    std::string type;
};