#include "game.h"
#include "collectible.h"
#include <vector>
#include <math.h>

Game* Game::game = nullptr;
Game::Game(sf::Vector2u mapSize) :window(sf::VideoMode(mapSize.x * 0.6f , mapSize.y * 0.6 ), "Until I Die"), 
playerView(sf::FloatRect(0, 0, window.getSize().x/2, window.getSize().y/2)),
hudView(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y))
{
    player = new Player(window.getSize().x, window.getSize().y);
    wave = new Wave(window.getSize().x, window.getSize().y);
    menuGameOver = new Gameover();
    mainMenu = new Menu();
    isPaused = true;
    isMainMenu = true;
    isGameOver = false;
    deltaTime = 0;

    mapTexture.loadFromFile("./sprite/map.jpg");
    mapSprite.setTexture(mapTexture);
    mapSprite.setScale(sf::Vector2f(0.6f, 0.6f));
    game = this;
}

Game::~Game() {
    while (!bullets.empty()) {
        delete bullets.back();
        bullets.pop_back();
    }
    while (!collectibles.empty()) {
        delete collectibles.back();
        collectibles.pop_back();
    }
    while (!zombies.empty()) {
        delete zombies.back();
        zombies.pop_back();
    }
    delete menuGameOver;
    delete mainMenu;
    delete wave;
    delete player;

}

void Game::collide() {
    bool isZombieDeleted = false;
    auto zIt = game->zombies.begin();
    while (zIt != game->zombies.end())
    {
        // Player collision with zombies
        isZombieDeleted = false;
        sf::Vector2f pPos = game->player->getSprite().getPosition();
        sf::Vector2f zPos = (*zIt)->getSprite().getPosition();
        float dist = sqrt((pPos.x - zPos.x)*(pPos.x - zPos.x) + (pPos.y - zPos.y)*(pPos.y - zPos.y));
        
        if (dist < 50)
        {
            (*zIt)->setIsAttacking(true);
        } else {
            (*zIt)->setIsAttacking(false);
        }
        
        auto bIt = game->bullets.begin();
        while (bIt != game->bullets.end())
        {
            // Erase Bullets too far
            if ((*bIt)->getSprite().getPosition().x < 0 || 
                (*bIt)->getSprite().getPosition().x > game->window.getSize().x || 
                (*bIt)->getSprite().getPosition().y < 0 || 
                (*bIt)->getSprite().getPosition().y > game->window.getSize().y)
            {
                delete(*bIt);
                bIt = game->bullets.erase(bIt);
                break;
            }
            
            // Zombie Collision with bullets
            sf::Vector2f bPos = (*bIt)->getSprite().getPosition();
            sf::Vector2f zPos = (*zIt)->getSprite().getPosition();
            float dist = sqrt((bPos.x - zPos.x)*(bPos.x - zPos.x) + (bPos.y - zPos.y)*(bPos.y - zPos.y));
           
            if (dist < (*zIt)->getCollisionRange())
            {
                if ((*zIt)->takeDamage((*bIt)->getDamage()))
                {
                    game->player->killZombie(*zIt);
                    delete(*zIt);
                    zIt = game->zombies.erase(zIt);
                    isZombieDeleted = true;
                    //--zIt;
                }
                delete(*bIt);
                bIt = game->bullets.erase(bIt);
                break;
            }else {
                ++bIt;
            }
        }
        if (game->zombies.size() == 0 || zIt == game->zombies.end())
            break;

        ++zIt; 

        if (isZombieDeleted)
            --zIt;
        
    }

    // player collision with collectibles
    auto cIt = game->collectibles.begin();
    while (cIt != game->collectibles.end())
    {
        sf::Vector2f pPos = game->player->getSprite().getPosition();
        sf::Vector2f cPos = (*cIt)->getSprite().getPosition();
        float dist = sqrt((pPos.x - cPos.x)*(pPos.x - cPos.x) + (pPos.y - cPos.y)*(pPos.y - cPos.y));
           
        if (dist < 30)
        {
            game->player->pickUpCollectible((*cIt));
            delete(*cIt);
            cIt = game->collectibles.erase(cIt);
        } else
        {
        ++cIt;
        }
    }
}


void Game::moveEntity(float time, sf::Vector2f mousePos){
    player->move(time, mousePos);
    for(auto it = std::begin(zombies); it != std::end(zombies); ++it) 
    {
        (*it)->move(time);
    }
    
 
    for(auto it = std::begin(bullets); it != std::end(bullets); ++it) 
    {
        (*it)->move(time);
    }
}



void Game::drawEntity(){
    window.draw(mapSprite);

    for(auto it = std::begin(collectibles); it != std::end(collectibles); ++it) 
    {
        (*it)->draw(window);
    }

    player->draw(window);
    
    for(auto it = std::begin(zombies); it != std::end(zombies); ++it) 
    {
        (*it)->draw(window);


    }
    
    for(auto it = std::begin(bullets); it != std::end(bullets); ++it) 
    {
        (*it)->draw(window);
    }

}

void Game::moveCamera()
{
    float pPosX= player->getSprite().getPosition().x;
    float pPosY = player->getSprite().getPosition().y;
    float wSizeX4 = window.getSize().x/4;
    float wSizeY4 = window.getSize().y/4;

    if (pPosX < wSizeX4)
        pPosX = wSizeX4;

    if (pPosX > wSizeX4 * 3)
        pPosX = wSizeX4 * 3;

    if (pPosY < wSizeY4)
        pPosY = wSizeY4;

    if (pPosY > wSizeY4 * 3)
        pPosY = wSizeY4 * 3;

    playerView.setCenter(pPosX, pPosY);
    window.setView(playerView);
}


void Game::update(){
    sf::Clock Clock;
    float shootTimer = 0;


    while(window.isOpen()){

        window.clear();
        sf::Event event; 
        sf::Time elapsed = Clock.getElapsedTime();
        deltaTime = elapsed.asSeconds();
        Clock.restart();
        
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseWheelScrolled:
                    if (!isPaused)
                        player->changeWeapon(event.mouseWheelScroll.delta);     
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape && isGameOver == false && isMainMenu == false)
                    {
                        isPaused = (isPaused == false) ? true : false;
                    }   
                    break;
                default:
                    break;
            }
        }
        moveCamera();

        if (!isPaused)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= player->getWeapon()->getFireRate() && player->getWeapon()->getMagazine() > 0)
            {
                bullets.push_back(player->playerShoot());
                shootTimer = 0;
            }

            shootTimer += deltaTime;

            wave->update(deltaTime);

            moveEntity(deltaTime, mousePos);
            collide();
        }
        drawEntity();

        window.setView(hudView);
        player->updateAndDrawHud(window, deltaTime);
    

        if (isGameOver) {
            isPaused = true;
            menuGameOver->draw(window, deltaTime);
            menuGameOver->gameOverCommand(window);

        }
        if (isMainMenu) {
            mainMenu->draw(window);
            if (mainMenu->mainMenuCommand(window)) {
                isPaused = false;
                isMainMenu = false;
            }
        }

        window.display();
    }
}


void Game::dropCollectible(Collectible* collectible)
{
    game->collectibles.push_back(collectible);
}

Game* Game::getInstance()
{
    return game;
}

float Game::getDeltaTime()
{
    return game->deltaTime;
}

sf::Vector2u Game::getWindowSize()
{
    return game->window.getSize();
}

const sf::RenderWindow& Game::getWindow()
{
    return game->window;
}

Player* Game::getPlayer()
{
    return game->player;
}

int Game::getZombieAlive() {
    return game->zombies.size();
}

void Game::spawnZombie(int zIndex) 
{
    if (zIndex == 1)
    {
        Zombie* zombie = new Zombie();
        game->zombies.push_back(zombie);
    } else if (zIndex == 2)
    {
        RedZombie* redzombie = new RedZombie();
        game->zombies.push_back(redzombie);
    } else if (zIndex == 3)
    {
        GreenZombie* greenZombie = new GreenZombie();
        game->zombies.push_back(greenZombie);
    }
}

bool Game::allZombiesDead() 
{
    return game->getZombieAlive() == 0 ? true : false;
}

int Game::getWaveIndex()
{
    return game->wave->getWaveNbr();
}

void Game::restart() 
{
    game->resetData();
    game->isPaused = false;
}

void Game::resetData()
{
    isGameOver = false;
    while(!bullets.empty()) {
        delete bullets.back();
        bullets.pop_back();
    }
    while(!collectibles.empty()) {
        delete collectibles.back();
        collectibles.pop_back();
    }
    while(!zombies.empty()) {
        delete zombies.back();
        zombies.pop_back();
    }
    game->wave->reset();

    delete game->player;
    game->player = new Player(window.getSize().x, window.getSize().y);
}

void Game::setGameOver(bool isGameOver)
{
    game->isGameOver = isGameOver;
}