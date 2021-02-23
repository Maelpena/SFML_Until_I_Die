#pragma once
#include "handgun.h"
#include <iostream>
#include "game.h"

Handgun::Handgun() : Weapon(0.2f)
{
    type = "handgun";
}

std::string Handgun::getType()
{
    return type;
}
  
Handgun::~Handgun(){}
