#ifndef MYCHARACTER_H
#define MYCHARACTER_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include "weapons.h"
//#include "enemies.h"

/*
 * Here we have a class of our hero
 * Create textures and sprites
 * Animation
 * Another action
 */

class MyCharacter :public sf::Sprite
{
private:
    //private functions
    //void InitTexture(std::string filename);

    //private properties
    sf::Texture texture;

public:
    //Constructor and destructor
    MyCharacter();
    //~MyCharacter();

//public properties

    float vx;   //horizontal velocity
    float vy;   //vertical velocity
    float ax;   //horizontal acceleration
    float ay;   //vertical acceleration
    float x;    //position horizontal a hero
    float y;    //position vertical a hero

    bool run;   //run or not
    bool jump;
    bool is_colission;
    bool facerigth; //hero have face on the right or left

    bool canjump; //can jump or not
    float jumpHeight; //higth of the jump

    int it; //iterator vector animation  frame
    int jump_it; //iterator jump animation frame
    int stay_it;
    int begin_stop;
    int hit_it;

    float timelimit;    //limit of animation time
    float time;
    float stop_time;
    float jump_time;
    //container of a animation frame a hero
    std::vector<sf::IntRect> vector_animationframe;
    Weapons* weapon;

    sf::Vector2f start_position; //start hero's position
    int life; //number of hero's lifes
    int coins; //number of hero's coins

//functions public

    void animation_frame(); //set vector of animation frame
    void InitSprite(sf::IntRect r);     //create hero
    void InitTexture(std::string filename);     //download texture from file
    //void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void render(sf::RenderTarget& window);  //draw a hero

    void runstep(const sf::Time& elapsed);  //animation of running
    void jumpstep(const sf::Time& elapsed);    //animation of jumping
    void stop(const sf::Time& elapsed);    //animation when hero stay
    void moving(const sf::Time& elapsed); //moving a hero with a time beetwen frame
    void Deadstep(sf::Time& elapsed); //animation when hero die
    void HitAnimation(const sf::Time& elapsed);
    void KickAnimation();

    //colission with static object
    void Oncollision(sf::Vector2f direction); //detect does hero in collision
    //colission with dynamic object
    void OnitemCollision(sf::Vector2f& direction);
    void OnSpecialBoxCollision(sf::Vector2f& direction);
    //collision with enemies
    void OnEnemiesCollision(sf::Vector2f& direction,sf::Time& elapsed);

    //create new weapon
    Weapons* CreateWeapons(float damage_,std::string name_,size_t it_);
};

#endif // MYCHARACTER_H
