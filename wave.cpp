#include "wave.h"
#include "game.h"
#include <time.h>
#include <chrono>
//#include <sysinfoapi.h>

Wave::Wave(unsigned int sizeX, unsigned int sizeY ) : 
    zombieToSpawn(5), waveNbr(1), redZombieMax(0), redZombieToSpawn(0),
    //test too mush zombie
    //zombieToSpawn(5), waveNbr(1), redZombieMax(0), redZombieToSpawn(0),
    waveFinished(false), spawnCooldown(1), zombieMax(5) {}

Wave::~Wave() {}

void Wave::update(float deltaTime) {
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);

    if (!waveFinished) {
        if ((redZombieToSpawn > 0 || zombieToSpawn > 0) && spawnCooldown <= 0 ) {
            
            int randRedZombie = rand()%1000 + 1;
            int randGreenZombie = rand()%11;

            float percentOfRedZombie = 0;
            if (zombieToSpawn == 0 && redZombieToSpawn > 0)
            {
                percentOfRedZombie = 1000;
            } else {
                percentOfRedZombie = redZombieToSpawn > 0 ? redZombieToSpawn/zombieToSpawn * 1000 : 0;

            }
            if (randRedZombie < percentOfRedZombie)
            {
                Game::spawnZombie(2);
                redZombieToSpawn--;
            } else if (waveNbr >= 5 && randGreenZombie == 0)
            {
                Game::spawnZombie(3);
            }
            else
            {
                Game::spawnZombie(1);
                zombieToSpawn--;
            }

        }
        if (zombieToSpawn <= 0 && Game::allZombiesDead() && redZombieToSpawn <= 0) {
            waveFinished = true;
        }
    }
    if (waveFinished) {
        waveNbr++;
        if (waveNbr > 9)
        {
            redZombieMax = waveNbr - 9;
            redZombieToSpawn = redZombieMax;
        }
        zombieMax += waveNbr;
        zombieToSpawn = zombieMax;
        waveFinished = false;
    }
    if (spawnCooldown <= 0)
    {
        spawnCooldown = 1-waveNbr*0.03 > 0.3 ? 1-waveNbr*0.03 : 0.3;
        //test too much zombie
        //spawnCooldown = 0.0000001f;

    } else {
        spawnCooldown -= deltaTime;
    }
    
}

int Wave::getWaveNbr() {
    return waveNbr;
}

void Wave::reset() {
    waveNbr = 1;
    zombieToSpawn = 5;
    waveFinished = false;
    spawnCooldown = 0.0f;
    zombieMax = 5;
}