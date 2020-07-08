#ifndef ROBOTSBULLET_H
#define ROBOTSBULLET_H
#include "SFML/Graphics.hpp"

/*
 * Class where create robots bullet
 * animation, sound
 *
 *
 *
 */



class RobotsBullet:public sf::Sprite
{
private:
    //properties
    sf::Texture texture;
    int direction;
    bool faceright;
    //functions
    void InitTextures();
public:
    RobotsBullet(bool& faceright_,sf::Vector2f& position);
    void Shoot(sf::Time& elapsed);
};


#endif // ROBOTSBULLET_H
