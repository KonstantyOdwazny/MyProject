#ifndef ENEMIES_H
#define ENEMIES_H
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include "robotsbullet.h"

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

struct Statistic{
    float lives;
    std::string name;
    int type_atack;
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
    RobotsBullet* createbullet(bool faceright_,sf::Vector2f v);

    //private properties
    std::vector<std::unique_ptr<sf::Texture>> textures;
    std::vector<sf::IntRect> vector_animationframe;
    float timelimit;
    std::vector<float> time;

    size_t it;
    float walktime;
    float walklimittime;
    float stoptime;
    float timetoshoot;
    sf::SoundBuffer laser_buffer;
    sf::Sound laser_sound;

public:
    Enemies();
    Enemies(std::string filename);
    ~Enemies();
    //public properties

    //size our textures
    const static int tile_height =128;
    const static int tile_width =96;
    //size a map
    const static int height =28;
    const static int width =47;
    //object our help struct Tile when we have a number which texture we have draw with our png
    Tile poziom[height][width];

    //vector of sprites enemies
    std::vector<std::unique_ptr<sf::Sprite>> sprites;
    //vector velocity enemies
    std::vector<float> veclocities;
    //vector of enemies's lifes
    std::vector<int> lifes;
    //vector enemies statistic
    std::vector<Statistic> enemies_statistic;
     std::vector<bool> faceright;

    std::vector<RobotsBullet*> bullets;
    bool heroisnear;

    //public functions
    void drawing(sf::RenderTarget& target);
    void walkingstep(const sf::Time& elapsed);
    void moving(const sf::Time& elapsed);
    void OnCollision(const size_t& i,const sf::Vector2f& direction);
    void Dead(const size_t& i);
    void SpecialAtack(sf::Time& elapsed);

};

#endif // ENEMIES_H
