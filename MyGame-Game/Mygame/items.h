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

enum KeyColor{
    yellow=14,red=15,green=16,blue=17
};

//help struct to selecting items on different type
class Weapons;
struct item_type
{
    std::string name;
    bool dynamic;
    sf::Vector2f velocity;
    bool dangerous;
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

    const static int height =27;
    const static int width =47;

    Tile poz_coin[height][width];

    Tile poziom[height][width];

    Tile poz_key[height][width];

    //vector textures
    std::vector<std::unique_ptr<sf::Texture>> textures;

    //help vector type of items
    std::vector<std::vector<item_type>> typeofitem;

    //weapons container
    std::vector<Weapons> weapons;

    //container of sprite
    std::vector<std::vector<std::unique_ptr<sf::Sprite>>> items;

    //kontener pozycji pochodni
    std::vector<sf::Vector2f> pochodnie_pozycja;

    //container of coins
    std::vector<std::unique_ptr<sf::Texture>> coins_tex;
    std::vector<std::unique_ptr<sf::Sprite>> coinsy;
    //container of keys
    std::vector<std::unique_ptr<sf::Sprite>> keys;
    std::vector<std::pair<KeyColor,bool>> iskeycollect;

    //container of doors
    std::vector<std::unique_ptr<sf::Sprite>> doors;
    std::vector<int> position_doors;

    //public functions
    void drawing(sf::RenderTarget& target);
    void Collision_events(sf::Vector2f& direction,const size_t& i,const size_t& j);
    void moving(sf::Time& elapsed);
    void Collectkeys(const size_t& i);
    //items with items collision
    void Collider_items();
};

class Weapons
{
private:

public:
    Weapons();
    std::string type;
    int damage;
    std::unique_ptr<sf::Texture> texture;
    std::unique_ptr<sf::Sprite> sprite;
};

#endif // ITEMS_H
