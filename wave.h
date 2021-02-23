#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Game;

class Wave {
    public:
        Wave(unsigned int, unsigned int);
        ~Wave();

        void update(float);
        int getWaveNbr();
        void reset();

    protected:
        bool waveFinished;
        float spawnCooldown;
        int waveNbr;
        float zombieToSpawn;
        float redZombieToSpawn;
        float zombieMax;
        float redZombieMax;
};