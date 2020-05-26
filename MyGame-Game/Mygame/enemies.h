#ifndef ENEMIES_H
#define ENEMIES_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <iostream>
#include "items.h"

class Enemies
{
private:
    //private functions
    void InitSprite();
    void animationframe();
    void loadfromfile(const std::string& filename);
    void InitTextures();

    //private properties
    std::vector<std::unique_ptr<sf::Texture>> textures;
    std::vector<sf::IntRect> vector_animationframe;
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

    std::vector<std::unique_ptr<sf::Sprite>> sprites;

    //public functions
    void drawing(sf::RenderTarget& target);
    void walkingstep();
    void moving();
};

#endif // ENEMIES_H
