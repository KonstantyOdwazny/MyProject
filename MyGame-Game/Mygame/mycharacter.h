#ifndef MYCHARACTER_H
#define MYCHARACTER_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <memory>
#include <iostream>
//#include "collision.h"

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
    MyCharacter() : sf::Sprite(){
        vx=0;
        vy=0;
        ax=0;
        ay=0;
        x=0;
        y=0;
        run=false;
        it=24;
        jump_it=1;
        jump=false;
        is_colission=true;
        timelimit=0.2f;
        time=0.0f;
        jumpHeight=100.0f;
        //canjump =true;
    }
    //~MyCharacter();

//public properties

    float vx;   //horizontal velocity
    float vy;   //vertical velocity
    float ax;   //horizontal acceleration
    float ay;   //vertical acceleration
    float x;    //position horizontal a hero
    float y;    //position vertical a hero
    bool run;   //run or not
    bool jump;  //jump or not
    bool is_colission;

    bool canjump;
    float jumpHeight;

    int it;
    int jump_it;
    float timelimit;    //limit of animation time
    float time;
    //container of a animation frame a hero
    std::vector<sf::IntRect> vector_animationframe;

//functions public

    void animation_frame();
    void InitSprite(sf::IntRect r);     //create hero
    void InitTexture(std::string filename);     //download texture from file
    //void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void render(sf::RenderTarget& window);  //draw a hero
    void setposition(float x_,float y_);    //set the position on the map
    void runstep(const sf::Time& elapsed);  //animation of running
    void jumpstep();    //animation of jumping
    void stop();    //animation when hero stay
    void moving(const sf::Time& elapsed);
    //colission with static object
    void Oncollision(sf::Vector2f direction);


};

#endif // MYCHARACTER_H
