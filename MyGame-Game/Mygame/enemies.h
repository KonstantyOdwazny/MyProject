#ifndef ENEMIES_H
#define ENEMIES_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <iostream>
//#include "items.h"

/*
 * Enemies clas
 * Sprites,textures
 * Moving and animation enemies
 *
*/


//help structure to load from file
struct Tile{
    //fieldtype type;
    int type;
    bool iswall;
};



class Enemies
{
private:
    //private functions
    void InitSprite();
    void animationframe();
    void loadfromfile(const std::string& filename);
    void InitTextures();
    void InitTime();
    void TurnAround();
    void CheckTurnface();
    void InitLifes();

    //private properties
    std::vector<std::unique_ptr<sf::Texture>> textures;
    std::vector<sf::IntRect> vector_animationframe;
    float timelimit;
    std::vector<float> time;
    std::vector<bool> faceright;
    size_t it;
    float walktime;
    float walklimittime;
    float stoptime;
public:
    Enemies();
    Enemies(std::string filename);
    //public properties

    //size our textures
    const static int tile_height =128;
    const static int tile_width =96;
    //size a map
    const static int height =22;
    const static int width =47;
    //object our help struct Tile when we have a number which texture we have draw with our png
    Tile poziom[height][width];

    //vector of sprites enemies
    std::vector<std::unique_ptr<sf::Sprite>> sprites;
    //vector velocity enemies
    std::vector<float> veclocities;
    //vector of enemies's lifes
    std::vector<int> lifes;

    //public functions
    void drawing(sf::RenderTarget& target);
    void walkingstep(const sf::Time& elapsed);
    void moving(const sf::Time& elapsed);
    void OnCollision(const sf::Vector2f& direction,const size_t& i);
    void Dead(const size_t& i);
};

#endif // ENEMIES_H
