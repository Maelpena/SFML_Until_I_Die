#include"SFML/Graphics.hpp"
#pragma once
// #include "player.h"

class Player;

class Zombie {
public:
    Zombie();
    ~Zombie();

    void move(float);
    virtual void die();
    bool takeDamage(float);
    void attaqueCac();
    void aim();
    void updateLifeBar();
    sf::Sprite getSprite();
    std::string getType();
    float getDamage();
    void setIsAttacking(bool);
    void draw(sf::RenderWindow&);
    void setSpawnPos();
    float getXp();
    float getCollisionRange();

protected:
    sf::Sprite sprite;
    sf::Texture texture;
    float hpMax;
    float hp;
    float movementSpeed;
    float damageCac;
    float posX;
    float posY;
    float dirX;
    float dirY;
    float rot;
    Player* target;
    std::string type;
    float damage;
    bool isAttacking;
    sf::RectangleShape lifeBar;
    sf::RectangleShape bgLifeBar;
    float attackCoolDown;
    float attackSpeed;
    float collisionRange;
    float xp;

};