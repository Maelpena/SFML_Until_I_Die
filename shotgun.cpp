#pragma once
#include "shotgun.h"
#include <iostream>
#include "game.h"

Shotgun::Shotgun() : Weapon(0.4f)
{
    type = "shotgun";

}

std::string Shotgun::getType()
{
    return type;
}

Shotgun::~Shotgun(){}