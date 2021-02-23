#include "redzombie.h"
#include "game.h"
#include "lifecollectible.h"
#include <chrono>

RedZombie::RedZombie() : Zombie()
{
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);
    hpMax = 200.f;
    hp = hpMax;
    int additionalSpeed = Game::getWaveIndex() * 5 < 85 ? Game::getWaveIndex() * 5 : 85;
    movementSpeed = (rand() % 50 + 50) + additionalSpeed;
    damageCac = 30;
    sprite.setScale(sf::Vector2f(0.4f, 0.4f));
    sprite.setColor(sf::Color::Red);
    sprite.setOrigin(sf::Vector2f(80.f, 90.f));
    bgLifeBar.setSize(sf::Vector2f(30, 3));
    bgLifeBar.setPosition(posX -15, posY+20);
    bgLifeBar.setFillColor(sf::Color(0,0,0));

    lifeBar.setSize(sf::Vector2f(30, 3));
    lifeBar.setPosition(posX -15, posY+20);
    lifeBar.setFillColor(sf::Color(230,50, 50));
    attackSpeed = 0.4f;
    attackCoolDown = attackSpeed;
    xp = 8;
    collisionRange = 50;
}    

void RedZombie::die()
{
    Game::dropCollectible(new LifeCollectible(posX, posY));
}

RedZombie::~RedZombie(){}