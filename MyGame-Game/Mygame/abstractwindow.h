#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class AbstractWindow
{
protected:
    sf::RenderWindow* window;
    sf::Texture* texture;
    sf::Sprite* sprite;
    sf::Font font;
    //audio
    sf::SoundBuffer click_buffer;
    sf::Sound click_sound;
    sf::SoundBuffer main_buffer;
    sf::Sound main_music;
    sf::SoundBuffer contains_buffer;
    sf::Sound contains_music;
    //events
    sf::Event ev;
    //functions
    virtual void InitText()=0;
    virtual void InitMusic()=0;
    virtual void InitTexture()=0;
public:
    AbstractWindow();
    virtual ~AbstractWindow()=default;
    virtual void PollEvents()=0;
    virtual void Drawing()=0;
    virtual bool Running()=0;
    virtual void PlayMusic()=0;
    virtual void Update()=0;
};

#endif // ABSTRACTWINDOW_H
