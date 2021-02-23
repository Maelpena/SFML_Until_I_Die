#include"SFML/Graphics.hpp"
#pragma once
#include "zombie.h"

// #include "player.h"

class Player;

class RedZombie : public Zombie {
    public:
        RedZombie();
        ~RedZombie();

        void die();
};