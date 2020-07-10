#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <vector>
#include "abstractwindow.h"

/*
 * Class a window when we select
 * character
 *
 *
 */

enum HeroClass{
    MaleAdventure,FemaleAdventure,BlackMale,BlackFemale
};

class OptionsWindow:public AbstractWindow
{
private:
    //properties
    std::vector<sf::Text> txt;
    //functions
    void InitTexture() override;
    void InitMusic() override;
    void InitText() override;
public:
    OptionsWindow();
    ~OptionsWindow();
    bool Running() override;
    void Update() override;
    void PollEvents() override;
    void PlayMusic() override;
    void Drawing() override;
    HeroClass heroclass;
    bool exitorplay;
};

#endif // OPTIONSWINDOW_H
