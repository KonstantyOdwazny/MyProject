#ifndef MENU_H
#define MENU_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "vector"
#include "abstractwindow.h"

/*
 *Class game menu
 *
 */

enum Activity{
    StartGame,Sterowanie,Exit
};

class MainMenu:public AbstractWindow
{
private:
    //functions
    void InitText() override;
    void InitMusic() override;
    void InitTexture() override;
public:
    MainMenu();
    ~MainMenu();
    //properties
    Activity action;
    bool isselect;
    std::vector<sf::Text> napisy;
    bool active;
    //functions
    void PollEvents() override;
    void Drawing() override;
    bool Running() override;
    void PlayMusic() override;
    void Update() override;
};

#endif // MENU_H
