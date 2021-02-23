#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "player.h"
#include "hud.h"
#include "wave.h"
#include "collectible.h"
#include "gameover.h"
#include "menu.h"
#include <vector>

class Game {
    public:
        Game(sf::Vector2u);
        ~Game();    
        
        void collide();
        void moveEntity(float, sf::Vector2f);
        void drawEntity();
        void moveCamera();
        void update();   
        
        static void spawnZombie(int);
        static void dropCollectible(Collectible*);
        static Game* getInstance();
        static float getDeltaTime();
        static sf::Vector2u getWindowSize();
        static const sf::RenderWindow& getWindow();
        static Player* getPlayer();
        static int getZombieAlive();
        static bool allZombiesDead();
        static int getWaveIndex();
        static void restart();
        static void setGameOver(bool);
        void resetData();

protected:
    static Game* game;
    sf::Sprite mapSprite; 
    sf::Texture mapTexture;
    Gameover* menuGameOver;
    Menu* mainMenu;
    bool isGameOver;
    bool isMainMenu;
    Wave* wave;
    sf::RenderWindow window;
    sf::View playerView;
    sf::View hudView;
    Player* player;
    std::vector<Bullet*> bullets;
    std::vector<Zombie*> zombies;
    std::vector<Collectible*> collectibles;
    sf::Vector2u windowSize;
    bool isPaused;
    float deltaTime;

};