#pragma once
#include "weapon.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "game.h"

Weapon::Weapon(float fireRate)
{
    //test too mush bullet
    //this->fireRate = fireRate - 0.1999999;
    this->fireRate = fireRate ;

    damage = fireRate * 10 * 5;

    maxAmmoMagazine = 0.6 / fireRate * 10;
    //test too mush bullet
    //maxAmmoMagazine = 0.6/fireRate*1000000;
    magazine = maxAmmoMagazine;
    reloadTimer = 0;

};

Weapon::~Weapon(){};


Bullet* Weapon::shoot(float playerPosX, float playerPosY, float playerDirX, float playerDirY, float playerLevel)
{
    Bullet* bullet = new Bullet(playerPosX, playerPosY, playerDirX, playerDirY, (1 + playerLevel/10) * damage);
    magazine -= 1;

    return bullet;
}

void Weapon::reload(int quantity)
{ 
    magazine += quantity; 
}


std::string Weapon::getType()
{
    return type;
}

float Weapon::getMagazine()
{
    return magazine;
}


float Weapon::getMaxAmmoMagazine()
{
    return maxAmmoMagazine;
}
float Weapon::getFireRate()
{
    return fireRate;
}