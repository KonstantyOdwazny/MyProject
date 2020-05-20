#ifndef MYCHARACTER_H
#define MYCHARACTER_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <memory>
#include <iostream>

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
    }
    //~MyCharacter();
    //public properties
    float vx;
    float vy;
    float ax;
    float ay;
    float x;
    float y;
    bool run;
    bool jump;
    bool is_colission;
    int it;
    int jump_it;
    std::vector<sf::IntRect> vector_animationframe;
    //functions public
    void animation_frame();
    void InitSprite(sf::IntRect r);
    void InitTexture(std::string filename);
    //void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void render(sf::RenderTarget& window);
    void setposition(float x_,float y_);
    void runstep();
    void jumpstep();
    void stop();
    void moving(const sf::Time& elapsed);
    //colission with static object
    bool colission(const std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& sp);
};

#endif // MYCHARACTER_H
