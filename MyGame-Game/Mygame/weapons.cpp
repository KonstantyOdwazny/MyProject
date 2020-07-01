#include "weapons.h"
#include "iostream"

//weapon constructor
void Weapons::InitTextures()
{
    if(!texture.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/spritesheet_weapons.png"))
    {
        std::cout<<"Blad";
    }
    texture.setRepeated(true);
    szerokosc=int(texture.getSize().x/9.0f);
    wysokosc=int(texture.getSize().y/16.0f);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<15;j++)
        {
            rect.emplace_back(sf::IntRect(i*szerokosc,j*wysokosc,szerokosc,wysokosc));
        }
    }
}

void Weapons::moving()
{
    this->move(0.0f,vy);
}


