#ifndef MAPGAME_H
#define MAPGAME_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <vector>
#include <memory>
//#include "collision.h"

enum fieldtype{
    None, STONE,Stone1,stone2,stone3,stone4,stone5,stone6,stone7,stone8,stone9,stone10,stone11,stone12,stone13,stone14,stone15,DIRT,COUNT
};
/*
 * two small help structures
 *
 *
 */
struct Tile{
    //fieldtype type;
    int type;
    bool iswall;
};
struct bounds{
    float left;
    float top;
    float width;
    float height;
};

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
    void getposition(size_t it);
    //size our textures
    const static int tile_height =128;
    const static int tile_width =128;

    const static int height =18;
    const static int width =32;
    //object our help struct Tile when we have a number which texture we have draw with our png
    Tile poziom[height][width];

    //vector textures
    std::vector<std::unique_ptr<sf::Texture>> textures;
    //vector sprites
    std::vector<std::vector<std::unique_ptr<sf::Sprite>>> sprites;
    //help vector of our grounds bounds
    std::vector<bounds> bounds_vector;

    bool CheckCollision(sf::Sprite& other,float p);




};

#endif // MAPGAME_H
