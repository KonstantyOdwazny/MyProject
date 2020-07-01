#ifndef WEAPONS_H
#define WEAPONS_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

class Weapons :public sf::Sprite
{
private:
    void InitTextures();
    sf::Texture texture;

    int szerokosc;
    int wysokosc;
    float vy;
public:
    std::vector<sf::IntRect> rect;
    Weapons():sf::Sprite(){this->InitTextures();
                          this->setTexture(texture);
                          this->setTextureRect(rect[6]);
                          this->setScale(0.3f,0.3f);
                          this->setOrigin(this->getGlobalBounds().width/2.0f,this->getGlobalBounds().height/2.0f);
                          vy=2.0f;};
    void moving();


};

#endif // WEAPONS_H
