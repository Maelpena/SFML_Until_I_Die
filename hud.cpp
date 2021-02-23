#include "game.h"
#include "handgun.h"
#include "hud.h"
#include <iostream>

Hud::Hud(Player* player, float screenSizeX, float screenSizeY)
{
    this->player = player;
    font1.loadFromFile("./font/m39.TTF");

    font2.loadFromFile("./font/NewRocker-Regular.otf");
    
    bgLifeBar.setSize(sf::Vector2f(400, 50));
    bgLifeBar.setPosition(15, 15);
    bgLifeBar.setFillColor(sf::Color::Black);

    lifeBar.setSize(sf::Vector2f(400, 50));
    lifeBar.setPosition(15, 15);
    lifeBar.setFillColor(sf::Color(52, 201, 36));

    lifeText = createTextWidget(90, 26, 25, 1);

    bgXpBar.setSize(sf::Vector2f(400, 50));
    bgXpBar.setPosition(screenSizeX - 415, 15);
    bgXpBar.setFillColor(sf::Color::Black);

    xpBar.setSize(sf::Vector2f(400, 50));
    xpBar.setPosition(screenSizeX - 415, 15);
    xpBar.setFillColor(sf::Color(44,117, 255));

    xpText = createTextWidget(screenSizeX - 365, 25, 25, 1);

    levelText = createTextWidget(screenSizeX - 210, 85, 20, 1);

    ammoText = createTextWidget(screenSizeX - 150, screenSizeY - 40, 30,1);

    magazineText = createTextWidget(screenSizeX - 320, screenSizeY - 38, 25, 1);

    killCountText = createTextWidget(15, 85, 25, 2);

    killSerieText = createTextWidget(15, 120, 25, 2);

    waveText = createTextWidget(15, screenSizeY - 45, 30, 2);

    zombieAliveText = createTextWidget(15, screenSizeY - 85, 25, 2);

    bloodTexture.loadFromFile("./sprite/blood.jpg");
    blood.setTexture(bloodTexture);
    blood.setScale(1.6f, 2.5f);
    blood.setPosition(sf::Vector2f(0, 0));
    blood.setColor(sf::Color(240, 240, 240, 0));
    playerBloodTime = 0.f;
}

Hud::~Hud(){}

sf::Text Hud::createTextWidget(int posX, int posY, int size, int fontIndex)
{
    sf::Text textWidget;
    if (fontIndex == 1)
    {
        textWidget.setFont(font1);

    } else 
    {
        textWidget.setFont(font2);
    }
    textWidget.setPosition(posX, posY);
    textWidget.setFillColor(sf::Color::White);
    textWidget.setCharacterSize(size);

    return textWidget;
}

void Hud::update(float deltaTime)
{
   
    //life bar
    float newLifeBarSize = (player->getHp()/player->getHpMax()) * 400;
    lifeBar.setSize(sf::Vector2f(newLifeBarSize, lifeBar.getSize().y));

    //life bar text
    std::string newLifeText = std::to_string((int)player->getHp()) + " / " + std::to_string((int)player->getHpMax());
    lifeText.setString(newLifeText);

    // xp bar
    float newXpBarSize = (player->getXp()/player->getXpNeeded()) * 400;
    xpBar.setSize(sf::Vector2f(newXpBarSize, xpBar.getSize().y));

    //xp bar text
    std::string newXpText = std::to_string((int)player->getXp()) + " / " + std::to_string((int)player->getXpNeeded());
    xpText.setString(newXpText);

    //level text
    levelText.setString("Niveau :" + std::to_string(player->getLevel()));

    //ammo text
    ammoText.setString(std::to_string(player->getAmmoRemain()));

    //magazine text
    magazineText.setString(std::to_string((int)player->getWeapon()->getMagazine()) + "/" + std::to_string((int)player->getWeapon()->getMaxAmmoMagazine()));

    //kill count text
    killCountText.setString(std::to_string((int)player->getKillCount()) + " kills" );

    killSerieText.setString("x" + std::to_string((int)player->getKillSerie()) + " kill series bonus !" );

    waveText.setString("Vague " + std::to_string(Game::getWaveIndex()));

    zombieAliveText.setString("zombies en vie " + std::to_string(Game::getZombieAlive()));


    //blood opacity
    if (playerBloodTime >= 0)
        playerBloodTime -= deltaTime;
    else 
        playerBloodTime = 0;
    float bloodOpacity = 70 - (player->getHp()/player->getHpMax()) * 70 + playerBloodTime * 40;
    blood.setColor(sf::Color(255, 255, 255, bloodOpacity));

}

void Hud::playerHit()
{
    playerBloodTime = 1.f;
}

void Hud::draw(sf::RenderWindow& window)
{
    window.draw(bgLifeBar);
    window.draw(bgXpBar);
    window.draw(lifeBar);
    window.draw(lifeText);
    window.draw(xpBar);
    window.draw(xpText);
    window.draw(levelText);
    window.draw(ammoText);
    window.draw(magazineText);
    window.draw(killSerieText);
    window.draw(killCountText);
    window.draw(waveText);
    window.draw(zombieAliveText);
    window.draw(blood);
}