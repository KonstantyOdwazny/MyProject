#ifndef ITEMS_H
#define ITEMS_H
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "enemies.h"
/*
 * Class items
 * drawing dynamic elements on map
 * selecting items
 * different type of items
 *
 */

//help struct to selecting items on different type

struct item_type
{
    std::string name;
    bool dynamic;
    sf::Vector2f velocity;
};

class Items
{
private:
    //private functions
    void loadfromfile(const std::string& filename);
    void createSprite();
public:
    //constructor and destructor
    Items();
    Items(std::string filename);

    //public properties
    const static int tile_height =128;
    const static int tile_width =128;

    const static int height =22;
    const static int width =47;

    Tile poziom[height][width];

    //vector textures
    std::vector<std::unique_ptr<sf::Texture>> textures;

    //help vector type of items
    std::vector<std::vector<item_type>> typeofitem;

    //container of sprite
    std::vector<std::vector<std::unique_ptr<sf::Sprite>>> items;

    //kontener pozycji pochodni
    std::vector<sf::Vector2f> pochodnie_pozycja;

    //public functions
    void drawing(sf::RenderTarget& target);
    void Collision_events(sf::Vector2f& direction,const size_t& i,const size_t& j);
    void moving(sf::Time& elapsed);
    //items with items collision
    void Collider_items();
};

#endif // ITEMS_H
