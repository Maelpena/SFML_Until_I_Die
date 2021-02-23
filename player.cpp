#include "player.h"
#include "handgun.h"
#include "game.h"
#include "rifle.h"
#include "shotgun.h"
#include <iostream>


Player::Player(float screenSizeX, float ScreenSizeY)
{
    handGunTexture.loadFromFile("./sprite/player_handgun.png");

    rifleTexture.loadFromFile("./sprite/player_rifle.png");
    shotGunTexture.loadFromFile("./sprite/player_shotgun.png");
    sprite.setTexture(handGunTexture);
    sprite.setScale(sf::Vector2f(0.25f, 0.25f)); 
    sprite.setOrigin(sf::Vector2f(105.f, 115.f));
    posX = 300;
    posY = 300;
    sprite.setPosition(posX, posY);
    dirX = 0;
    dirY = 0;
    rot = 0;
    Handgun* a = new Handgun();
    weapon = a;
    weapons.push_back(weapon);
    weapons.push_back(new Shotgun());
    weapons.push_back(new Rifle());
    //test too mush life
    //hpMax = 1000000;
    hpMax = 100;
    hp = hpMax;
    movementSpeed = 250;
    killCount = 0;
    killSerie = 0;
    level = 1;
    xp = 0;
    xpNeeded = 2000;
    weaponIndex = 0;
    handgunAmmoRemain = 100;
    shotgunAmmoRemain = 100;
    rifleAmmoRemain = 100;

    hud = new Hud(this, screenSizeX, ScreenSizeY);
};

Player::~Player(){
    delete hud;
    while (!weapons.empty()) {
        delete weapons.back();
        weapons.pop_back();
    }
};


bool Player::getInputs() 
{
    bool reloadInput = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    bool leftInput = sf::Keyboard::isKeyPressed(sf::Keyboard::Q);
    bool rightInput = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool upInput = sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
    bool downInput = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    if (reloadInput)
    {
        reload();
    }
    if(leftInput && upInput){
        dirX = -0.7f;
        dirY = -0.7f;
        return true;
    }
    else if(leftInput && downInput){
        dirX = -0.7f;
        dirY = 0.7f;
        return true;
    }
    else if(rightInput && upInput){
        dirX = 0.7f;
        dirY = -0.7f;
        return true;
    }
    else if(rightInput && downInput){
        dirX = 0.7f;
        dirY = 0.7f;
        return true;
    }
    else if(leftInput){
        dirX = -1;
        dirY = 0;
        return true;
    }
    else if(rightInput){
        dirX = 1;
        dirY = 0;
        return true;
    }
    else if(upInput){
        dirY = -1;
        dirX = 0;
        return true;
    }
    else if(downInput){
        dirY = 1;
        dirX = 0;
        return true;
    }
    else
    {
        dirY = 0;
        dirX = 0;
    return false;
    }
    
}

void Player::changeWeapon(int change)
{
    weaponIndex = change + weaponIndex;

    if (weaponIndex < 0)
    {
        weaponIndex = weapons.size()-1;
    } else if (weaponIndex > weapons.size()-1)
    {
        weaponIndex = 0;
    }

    weapon = weapons[weaponIndex];

    switch (weaponIndex)
    {
    case 0:
        sprite.setTexture(handGunTexture);
        break;
    case 1:
        sprite.setTexture(shotGunTexture);
        break;
    case 2:
        sprite.setTexture(rifleTexture);
        break;
    default:
        sprite.setTexture(handGunTexture);
        break;
    }
}


void Player::reload()
{   
    int ammoToReload = weapon->getMaxAmmoMagazine() - weapon->getMagazine();
    if (weapon->getType() == "rifle")
        if (rifleAmmoRemain - ammoToReload >= 0)
            rifleAmmoRemain -= ammoToReload;
        else
        {
            ammoToReload = rifleAmmoRemain;
            rifleAmmoRemain = 0;
        }
    else if (weapon ->getType() == "handgun")
        if (handgunAmmoRemain - ammoToReload >= 0)
            handgunAmmoRemain -= ammoToReload;
        else
        {
            ammoToReload = handgunAmmoRemain;
            handgunAmmoRemain = 0;
        }
    else if (weapon ->getType() == "shotgun")
        if (shotgunAmmoRemain - ammoToReload >= 0)
            shotgunAmmoRemain -= ammoToReload;
        else
        {
            ammoToReload = shotgunAmmoRemain;
            shotgunAmmoRemain = 0;
        } 
    weapon->reload(ammoToReload);
}

void Player::move(float time, sf::Vector2f mousePos)
{
    aim(mousePos);

    if (getInputs()){
        if ((time * movementSpeed * dirX + posX) < 15)
        {
            posX = 15;
        } else if ((time * movementSpeed * dirX + posX) > Game::getWindowSize().x - 15)
        {
            posX = Game::getWindowSize().x - 15;
        } else {
            posX += time * movementSpeed * dirX;
        }

        if ((time * movementSpeed * dirY + posY) < 15)
        {
            posY = 15;
        } else if ((time * movementSpeed * dirY + posY) > Game::getWindowSize().y - 15)
        {
            posY = Game::getWindowSize().y - 15;
        } else
        {
        posY += time * movementSpeed * dirY;
        }
        sprite.setPosition(posX, posY);
    };
    sprite.setRotation(rot);

}

void Player::aim(sf::Vector2f mousePos){

    const float PI = 3.14159265f;
    
    float dx = posX - mousePos.x;
    float dy = posY - mousePos.y;
    
    rot = (atan2(dy, dx)) * 180 / PI + 180;

}

Bullet* Player::playerShoot()
{
    const float PI = 3.14159265f;

    dirX = cos((PI/180)*rot);
    dirY = sin((PI/180)*rot);

    return weapon->shoot(posX + dirX *30, posY + dirY*30, dirX, dirY, level);

}

void Player::takeDamage(float damage)
{
    if ((hp - damage) <= 0)
    {
        hp = 0;
        Game::setGameOver(true);
    }else {
        hp -= damage;
        hud->playerHit();
    }
    
    killSerie = 0;
}

void Player::killZombie(Zombie* zombie)
{
    killCount += 1;
    killSerie += 1;
    winXp(zombie->getXp());
}

void Player::winXp(float xp)
{
    this->xp += xp * (killSerie + 100);

    if (this->xp >= xpNeeded)
    {
        level += 1;
        this->xp = 0;
        hpMax += 10;
        hp += 10;
        xpNeeded = xpNeeded * 1.2f;
    }
}

void Player::pickUpCollectible(Collectible* collectible)
{
    if (collectible->getType() == "rifle")
        rifleAmmoRemain += collectible->getQuantity();
    else if (collectible ->getType() == "handgun")
        handgunAmmoRemain += collectible->getQuantity();
    else if (collectible->getType() == "shotgun")
        shotgunAmmoRemain += collectible->getQuantity();
    else if (collectible->getType() == "life")
        hp = hp + collectible->getQuantity() > hpMax ? hpMax : hp + collectible->getQuantity();
}  

sf::Sprite Player::getSprite()
{
    return sprite;
}

float Player::getPosX()
{
    return posX;
}


float Player::getPosY()
{
    return posY;
}


int Player::getAmmoRemain()
{
    if (weapon->getType() == "handgun")
    {
        return handgunAmmoRemain;
    } else if (weapon->getType() == "rifle")
    {
        return rifleAmmoRemain;
    } else
    {
        return shotgunAmmoRemain;
    }
    
    
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::updateAndDrawHud(sf::RenderWindow& window, float deltaTime)
{
    hud->update(deltaTime);
    hud->draw(window);
}

float Player::getXp()
{
    return xp;
}
float Player::getXpNeeded()
{
    return xpNeeded;
}
int Player::getLevel()
{
    return level;
}
float Player::getHp()
{
    return hp;
}
float Player::getHpMax()
{
    return hpMax;
}
float Player::getKillCount()
{
    return killCount;
}
float Player::getKillSerie()
{
    return killSerie;
}
Weapon* Player::getWeapon()
{
    return weapon;
}