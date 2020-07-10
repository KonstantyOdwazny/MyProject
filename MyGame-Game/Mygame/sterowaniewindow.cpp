#include "sterowaniewindow.h"
#include <iostream>


void SterowanieWindow::InitTexture()
{
    this->texture=new sf::Texture();
    if(!this->texture->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Sterowanie.png"))
    {
        std::cout<<"Nie otwarl sie!"<<std::endl;
    }
    this->texture->setRepeated(true);
    this->sprite=new sf::Sprite();
    this->sprite->setTexture(*this->texture);
}

void SterowanieWindow::InitMusic()
{
    main_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/MagoryNET-Dreams-In-A-Stasis-Chamber.ogg");
    main_music.setBuffer(main_buffer);
    main_music.setLoop(true);
}

SterowanieWindow::SterowanieWindow()
{
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"Sterowanie");
    this->InitMusic();
    this->InitTexture();
}

SterowanieWindow::~SterowanieWindow()
{
    delete this->window;
    delete this->texture;
    delete this->sprite;
}

void SterowanieWindow::PollEvents()
{
    while(window->pollEvent(ev))
    {
        if(ev.type==sf::Event::Closed)
        {
            main_music.stop();
            window->close();

        }
    }
}

bool SterowanieWindow::Running()
{
    return this->window->isOpen();
}

void SterowanieWindow::Drawing()
{
    window->clear(sf::Color::Black);
    window->draw(*this->sprite);
    window->display();
}

void SterowanieWindow::PlayMusic()
{
    main_music.play();
}
