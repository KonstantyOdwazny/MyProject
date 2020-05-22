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
    //window
    sf::RenderWindow* window;
    //events
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
    sf::Vector2f direction;
    //time
    sf::Clock clock;
    sf::Time elapsed;
    //view
    sf::View view;

    void CheckCollision(sf::Vector2f& direction ,float p);
};

#endif // GAME_H
