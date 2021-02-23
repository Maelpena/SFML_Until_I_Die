#include "greenzombie.h"
#include "game.h"

GreenZombie::GreenZombie() : Zombie()
{
    hpMax = 30.f;
    hp = hpMax;
    int additionalSpeed = Game::getWaveIndex() * 5 < 85 ? Game::getWaveIndex() * 5 : 85;
    movementSpeed = 200;
    damageCac = 5;
    sprite.setScale(sf::Vector2f(0.15f, 0.15f));
    sprite.setColor(sf::Color::Green);
    sprite.setOrigin(sf::Vector2f(80.f, 90.f));

    attackSpeed = .15f;
    attackCoolDown = attackSpeed;
    xp = 2;
    collisionRange = 20;
}    

GreenZombie::~GreenZombie() {}
