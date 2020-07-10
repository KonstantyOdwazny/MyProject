#include "game.h"

using namespace std;

int main()
{

    MainMenu menu;
    menu.PlayMusic();
    while(menu.Running() && menu.active==true)
    {
        menu.PollEvents();

        menu.Update();

        menu.Drawing();
    }
    if(menu.action==Activity::Exit)
    {
        return 0;
    }
    else
    {
        if(menu.action==Activity::Sterowanie)
        {
            SterowanieWindow sterowanie;
            sterowanie.PlayMusic();
            while(sterowanie.Running())
            {
                sterowanie.PollEvents();
                //sterowanie.Update();
                sterowanie.Drawing();
            }
            return main();
        }
    OptionsWindow select;
    select.PlayMusic();
    while(select.Running())
    {
        select.PollEvents();

        select.Update();

        select.Drawing();
    }
    if(select.exitorplay==false)
    {
        return 0;
    }
    else
    {
    Game game(select.heroclass);
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
    }
}
