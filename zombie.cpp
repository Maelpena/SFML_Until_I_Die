#include "zombie.h"
#include "player.h"
#include <iostream>
#include "game.h"
#include "collectible.h"
#include "handgunammo.h"
#include "rifleammo.h"
#include "shotgunammo.h"
#include <random>
#include <chrono>




Zombie::Zombie()
{
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);

    hpMax = 50.f;
    hp = hpMax;

    int additionalSpeed = Game::getWaveIndex() * 5 < 85 ? Game::getWaveIndex() * 5 : 85;

    movementSpeed = (rand() % 50 + 50) + additionalSpeed;

    damageCac = 10;
    texture.loadFromFile("./sprite/zombi.png");
    sprite.setTexture(texture);
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    sprite.setOrigin(sf::Vector2f(80.f, 90.f));
    setSpawnPos();
    rot = 0;
    target = Game::getPlayer();
    isAttacking = false;
    bgLifeBar.setSize(sf::Vector2f(30, 3));
    bgLifeBar.setPosition(posX - 15, posY + 25);
    bgLifeBar.setFillColor(sf::Color(0, 0, 0));

    lifeBar.setSize(sf::Vector2f(30, 3));
    lifeBar.setPosition(posX - 15, posY + 25);
    lifeBar.setFillColor(sf::Color(230, 50, 50));
    attackSpeed = .3f;
    attackCoolDown = attackSpeed;
    xp = 2;
    collisionRange = 30;


}

Zombie::~Zombie() {
    return;
}

void Zombie::move(float time)
{
    aim();
    sprite.setRotation(rot);

    if (!isAttacking)
    {
        attackCoolDown = attackSpeed;
        posX += time * movementSpeed * dirX;
        posY += time * movementSpeed * dirY;

        sprite.setPosition(posX, posY);
        lifeBar.setPosition(posX - 15, posY - 30);
        bgLifeBar.setPosition(posX - 15, posY - 30);
    }
    else {
        attackCoolDown -= time;
        if (attackCoolDown <= 0)
        {
            target->takeDamage(damageCac);
            attackCoolDown = attackSpeed;
        }
    }

}

void Zombie::aim()
{
    const float PI = 3.14159265f;

    float dx = posX - target->getPosX();

    float dy = posY - target->getPosY();

    rot = (atan2(dy, dx)) * 180 / PI + 180;

    dirX = cos((PI / 180) * rot);
    dirY = sin((PI / 180) * rot);

}

bool Zombie::takeDamage(float damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        die();
        return true;
    }
    else
    {
        updateLifeBar();
        return false;
    }

}

void Zombie::updateLifeBar()
{
    float newLifeBarSize = (hp / hpMax) * 30;
    lifeBar.setSize(sf::Vector2f(newLifeBarSize, lifeBar.getSize().y));
}

void Zombie::die()
{
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);    int dropAmmoLuck = rand() % 100 + 0;
    if (dropAmmoLuck > 75)
    {
        int ammoIndexToDrop = rand() % 3 + 1;
        switch (ammoIndexToDrop)
        {
        case 1:
            Game::dropCollectible(new HandgunAmmo(posX, posY));
            break;
        case 2:
            Game::dropCollectible(new RifleAmmo(posX, posY));
            break;
        case 3:
            Game::dropCollectible(new ShotgunAmmo(posX, posY));
            break;
        default:
            break;
        }
    }
}
sf::Sprite Zombie::getSprite()
{
    return sprite;
}

std::string Zombie::getType()
{
    return type;
}

float Zombie::getDamage()
{
    return damage;
}

void Zombie::setIsAttacking(bool isAttacking)
{
    this->isAttacking = isAttacking;
}

void Zombie::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(bgLifeBar);
    window.draw(lifeBar);
}

void Zombie::setSpawnPos()
{
    long long t1 = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::srand((unsigned int)t1);
    int spawnPosIndex = rand() % 4 + 1;
    switch (spawnPosIndex) {
    case 1:
        posX = -50;
        posY = rand() % Game::getWindowSize().y;
        break;
    case 2:
        posX = rand() % Game::getWindowSize().x;
        posY = -50;
        break;
    case 3:
        posX = Game::getWindowSize().x + 50;
        posY = rand() % Game::getWindowSize().y;
        break;
    case 4:
        posX = rand() % Game::getWindowSize().x;
        posY = Game::getWindowSize().y + 50;
        break;
    default:
        break;
    }
}

float Zombie::getXp()
{
    return xp;
}

float Zombie::getCollisionRange()
{
    return collisionRange;
}