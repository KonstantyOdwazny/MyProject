#ifndef MAPGAME_H
#define MAPGAME_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include <memory>
//#include "collision.h"
#include "items.h"


/*
 * Class our map
 * Cretae Background and grass itp.
 *
*/

class MapGame
{
public:
    //constructors and destructor
    MapGame();
    MapGame(std::string filename);
    ~MapGame();
    //public functions
    void loadfromfile(std::string filename);
    void createSprite();
    void drawing(sf::RenderTarget& target);
    //size our textures
    const static int tile_height =128;
    const static int tile_width =128;

    const static int height =28;
    const static int width =47;
    //object our help struct Tile when we have a number which texture we have draw with our png
    Tile poziom[height][width];

    //vector textures
    std::vector<std::unique_ptr<sf::Texture>> textures;
    //vector sprites
    std::vector<std::vector<std::unique_ptr<sf::Sprite>>> sprites;
    sf::Vector2f pom;
    sf::Sprite* backgrounds;
    sf::Texture* tex;


};

#endif // MAPGAME_H
