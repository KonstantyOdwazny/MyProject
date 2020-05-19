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
    Game();
    virtual ~Game();
    void update();
    void render();
    bool running();
    void pollevent();

    MapGame* level;
    MyCharacter* hero;

};

#endif // GAME_H
