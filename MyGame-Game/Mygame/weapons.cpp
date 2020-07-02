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
    //szerokosc=int(texture.getSize().x/9.0f);
    //wysokosc=int(texture.getSize().y/17.0f);
    szerokosc=130;
    wysokosc=130;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<15;j++)
        {
            rect.emplace_back(sf::IntRect(i*szerokosc,j*wysokosc,szerokosc,wysokosc));
        }
    }
}
//constructor
Weapons::Weapons(float damage_, std::string name_, size_t it_):sf::Sprite(),damage(damage_),it(it_),name(name_){
    this->InitTextures();
   this->setTexture(texture);
  this->setTextureRect(rect[it]);
   this->setScale(0.3f,0.3f);
   this->setOrigin(this->getGlobalBounds().width/2.0f,this->getGlobalBounds().height/2.0f);
   vy=0.0f;
                                                                                                                                                                                                                            vx=0.0f;
}

void Weapons::moving()
{
    int licz=0;
    licz++;
    if(licz<=10)
    {
        vy+=3.0f;
    }
    else
    {
        vy-=3.0f;
    }
    this->move(0.0f,vy);

}


