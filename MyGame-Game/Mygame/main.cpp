#include "game.h"

using namespace std;

int main()
{
    Game game;
    while(game.running())
    {
        //events
        game.pollevent();
        //updating
        game.update();
        //drawing everything
        game.render();
    }
    return 0;
}
