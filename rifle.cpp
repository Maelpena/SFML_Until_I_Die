#pragma once
#include "rifle.h"
#include <iostream>
#include "game.h"

Rifle::Rifle() : Weapon(0.1f)
{
    type = "rifle";

}

std::string Rifle::getType()
{
    return type;
}

Rifle::~Rifle(){}