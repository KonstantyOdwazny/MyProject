#include "mycharacter.h"

//private functions
void MyCharacter::InitTexture(std::string filename)
{
    if(!texture.loadFromFile(filename)){
        std::cout<<"Blad otwarcia pliku"<<std::endl;
    }
    this->texture.setRepeated(true);
}

void MyCharacter::animation_frame()
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<8;j++)
        {
            this->vector_animationframe.emplace_back(sf::IntRect(i*128,j*150+110,128,150));
        }
    }
}

void MyCharacter::InitSprite(sf::IntRect r)
{
    this->setTexture(this->texture);
    this->setTextureRect(r);
    this->setScale(0.25f,0.25f);
    //this->setPosition(100.0f*0.4f,300.0f*0.4f);
}

void MyCharacter::render(sf::RenderTarget &window)
{
    window.draw(*this);
}

void MyCharacter::setposition(float x,float y)
{
    this->setPosition(x*0.25f,y*0.25f);
}
