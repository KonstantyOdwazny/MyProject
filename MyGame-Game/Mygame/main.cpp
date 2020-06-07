#include "game.h"

using namespace std;

int main()
{
    Game game;
    int koniec=0;
    while(game.running())
    {

        //events
        game.pollevent();
        if(game.startagain==true)
        {
            koniec=1;
            break;
        }
        //updating
        game.update();
        //drawing everything
        game.render();
    }
    if(koniec==1)
    {
        return main();
    }
    else
    {
        return 0;
    }
}
