#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "vector"

/*
 *Class game menu
 *
 */

enum Activity{
    StartGame,SelectHero,Exit
};

class MainMenu
{
private:
    //txt

    sf::Font font;
    //audio
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;
    sf::SoundBuffer menu_buffer;
    sf::Sound menu_music;
    //graphic
    sf::Texture bacground_tex;
    sf::Sprite bacground;
    //events
    sf::Event event;
    //window
    sf::RenderWindow* window;
    //functions
    void InitTextPosition();
public:
    MainMenu();
    ~MainMenu();
    //properties
    Activity action;
    bool isselect;
    std::vector<sf::Text> napisy;
    bool active;
    //functions
    void UpdateEvents();
    void Drawing();
    bool Running();
};

#endif // MENU_H
