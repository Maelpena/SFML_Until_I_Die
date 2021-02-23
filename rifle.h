#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "bullet.h"
#include "weapon.h"

class Rifle : public Weapon 
{
public:
    Rifle();
    ~Rifle();

    std::string getType();
private:
    std::string type;
};