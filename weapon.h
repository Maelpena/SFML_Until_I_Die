#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "bullet.h"

class Weapon {
public:
    Weapon(float);
    ~Weapon();

    Bullet* shoot(float, float, float, float, float);
    void reload(int);
    virtual std::string getType();
    float getMagazine();
    float getMaxAmmoMagazine();
    float getFireRate();

private:
    std::string type;
    float damage;
    float fireRate;
    float reloadTimer;
    float magazine;
    float maxAmmoMagazine;
        
};