#include "robotsbullet.h"
//private create function

void RobotsBullet::InitTextures()
{
    texture.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Bullet.png");
    texture.setRepeated(true);
    this->setTexture(texture);
    this->setScale(0.5f,0.5f);
}

RobotsBullet::RobotsBullet(bool& faceright_,sf::Vector2f& position):sf::Sprite(),faceright(faceright_)
{
    this->InitTextures();
    this->setPosition(position);
}

void RobotsBullet::Shoot(sf::Time& elapsed)
{
    if(faceright)
    {
        this->move(250.0f*elapsed.asSeconds(),0.0f);
    }
    else
    {
        this->move(-250.0f*elapsed.asSeconds(),0.0f);
    }
}

