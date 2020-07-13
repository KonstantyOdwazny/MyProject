#include "winwindow.h"
#include <iostream>

void WinWindow::InitText()
{
    font.loadFromFile("Mecha.ttf");
    text.setString("End");
    text.setFont(font);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Red);
    //text.setPosition(400,300);
}

void WinWindow::InitMusic()
{
    click_buffer.loadFromFile("metalClick.ogg");
    click_sound.setBuffer(click_buffer);
    contains_buffer.loadFromFile("handleSmallLeather.ogg");
    contains_music.setBuffer(contains_buffer);
}

void WinWindow::InitTexture()
{
    this->texture=new sf::Texture();
    if(!this->texture->loadFromFile("wintlo.png"))
    {
        std::cout<<"Nie otwarl sie!"<<std::endl;
    }
    this->texture->setRepeated(true);
    this->sprite=new sf::Sprite();
    this->sprite->setTexture(*this->texture);
}

WinWindow::WinWindow()
{
    this->InitText();
    window=new sf::RenderWindow(sf::VideoMode(400,600),"Main Menu");
    this->InitMusic();
    this->InitTexture();
    run=true;
}

WinWindow::~WinWindow()
{
    delete this->window;
    delete this->sprite;
    delete this->texture;
}

void WinWindow::Update()
{
    sf::Vector2i v= sf::Mouse::getPosition(*window);
    if(text.getGlobalBounds().contains(float(v.x),float(v.y)))
    {
        contains_music.play();
        text.setFillColor(sf::Color::White);
    }
    text.setFillColor(sf::Color::Red);
}

void WinWindow::Drawing()
{
    this->window->clear(sf::Color::Black);
    this->window->draw(*this->sprite);
    this->window->draw(this->text);
    this->window->display();
}

void WinWindow::PollEvents()
{
    while (this->window->pollEvent(this->ev)) {
        if(this->ev.type==sf::Event::MouseButtonPressed)
        {
            if(this->ev.mouseButton.button==sf::Mouse::Left)
            {
                click_sound.play();
                sf::Vector2i v= sf::Mouse::getPosition(*window);
                if(text.getGlobalBounds().contains(float(v.x),float(v.y)))
                {
                    run=false;
                    window->close();
                }


            }
        }
        if(ev.type==sf::Event::Closed)
        {
            run=false;
            window->close();
        }
    }
}

bool WinWindow::Running()
{
    return this->window->isOpen();
}
