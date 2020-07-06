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

public:
    std::vector<sf::IntRect> rect;
    Weapons(float damage_,std::string name_,size_t it_);
    void moving();
     float vy;
     float vx;
     float damage;
     size_t it;
     std::string name;
     bool canhit;
};

#endif // WEAPONS_H
