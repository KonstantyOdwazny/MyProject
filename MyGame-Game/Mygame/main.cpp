#include "game.h"

using namespace std;

int main()
{

    MainMenu menu;
    while(menu.Running() && menu.active==true)
    {
        menu.UpdateEvents();

        menu.Drawing();
    }
    Game game;
    int koniec=0;
    sf::SoundBuffer begin_buffer;
    sf::Sound begin_music;
    begin_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/bensound-epic.ogg");
    begin_music.setBuffer(begin_buffer);
    begin_music.setLoop(true);
    begin_music.play();
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
        begin_music.stop();
        return main();
    }
    else
    {
        return 0;
    }
}
