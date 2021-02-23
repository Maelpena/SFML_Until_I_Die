#include <SFML/Graphics.hpp>
#include <vector>

class Menu {
    public:
        Menu();
        ~Menu();

        bool mainMenuCommand(sf::RenderWindow&);
        float getTime();
        void draw(sf::RenderWindow&);

    protected:
        sf::Sprite          background;
        sf::Texture         bgTexture;
        sf::Sprite          playButton;
        sf::Texture         playButtonTexture;
        sf::Sprite          quitButton;
        sf::Texture         quitButtonTexture;
        sf::Font            font;
        sf::Text            gameName;
        sf::Text            credit;
};