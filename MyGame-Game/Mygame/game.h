#ifndef GAME_H
#define GAME_H
#include "mapgame.h"
#include "mycharacter.h"

/*
 Main game class
 create game loop and renderwindow
*/
class Game
{
private:
    sf::RenderWindow* window;
    sf::Event ev;
public:
    //constructor and destructor
    Game();
    virtual ~Game();
    //public functions
    void update();
    void render();
    bool running();
    void pollevent();
    //public properties
    MapGame* level;
    MyCharacter* hero;
    //time
    sf::Clock clock;
    sf::Time elapsed;
    //view
    sf::View view;
};

#endif // GAME_H
