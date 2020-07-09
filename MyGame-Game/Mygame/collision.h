#ifndef COLLISION_H
#define COLLISION_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <memory>
#include "mycharacter.h"
#include "items.h"

/*
 *
 *
 * Collider engine
 *
 *
 */

class Collision
{
public:
    Collision();
    void CheckCollisions(std::vector<std::unique_ptr<sf::Sprite>>& sprites,MyCharacter& hero,sf::Vector2f direction,float p,sf::Time& elapsed);
    void CheckCollisions(std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& v,MyCharacter& s,sf::Vector2f& direction,float p);
    void CheckCollisions(Items& things,MyCharacter& hero,sf::Vector2f& direction,float p,sf::Time& elapsed);
    void CheckCollisions(std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& sprites,Items& things,sf::Vector2f& direction,float p);
    void CheckCollisions(Enemies& enemies,Items& things,sf::Vector2f& direction);
    void WeaponHit(Weapons& weapon,Enemies& enemy);
    void BulletsCollision(std::vector<RobotsBullet*>& bullets,Items& things,MyCharacter& hero,std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& map,sf::Time& elapsed);
};

#endif // COLLISION_H
