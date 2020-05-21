#ifndef COLLISION_H
#define COLLISION_H
#include "SFML/Graphics.hpp"
/*
 * Class where we check collision player witch the other object
 *
 */


class Collision
{
private:
    //sf::RectangleShape& body;
      sf::Sprite& body;
public:
    Collision(sf::Sprite& body);

    void Move(float dx,float dy){body.move(dx,dy);}

    bool Checkcollision(Collision& other,float p);
    sf::Vector2f Getposition(){return body.getPosition();}
    sf::Vector2f Gethalfsize();

};

#endif // COLLISION_H
