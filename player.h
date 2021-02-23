#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "weapon.h"
#include "collectible.h"
#include "hud.h"


class Game;

class Player {
public:
    Player(float, float);
    ~Player();

    void move(float, sf::Vector2f);
    void draw(sf::RenderWindow&);
    void updateAndDrawHud(sf::RenderWindow&, float);
    void takeDamage(float);
    Bullet* playerShoot();
    void changeWeapon(int);
    void aim(sf::Vector2f);
    void killZombie(Zombie*);
    void winXp(float x);
    bool getInputs(); 
    void reload();
    sf::Sprite getSprite();
    float getPosX();
    float getPosY();
    void pickUpCollectible(Collectible*);
    int getAmmoRemain();
    float getHp();
    float getHpMax();
    float getXp();
    float getXpNeeded();
    int getLevel();
    float getKillCount();
    float getKillSerie();
    Weapon* getWeapon();

private:
    Hud* hud;
    sf::Sprite sprite; 
    sf::Texture handGunTexture;
    sf::Texture rifleTexture;
    sf::Texture shotGunTexture;
    float hpMax;
    float hp;
    float movementSpeed;
    std::vector<Weapon*> weapons;
    Weapon* weapon;
    float posX;
    float posY;
    float dirX;
    float dirY;
    float rot;
    int killCount;  
    int level;
    float xp;    
    float xpNeeded;    
    int killSerie;
    int weaponIndex;
    int handgunAmmoRemain;
    int shotgunAmmoRemain;
    int rifleAmmoRemain;
};