#include "menu.h"
#include <iostream>

void MainMenu::InitTextPosition()
{
    for(size_t i=0;i<napisy.size();i++)
    {
        napisy[i].setPosition(100.0f,100.0f+i*100.0f);
        napisy[i].setFillColor(sf::Color::Red);
        napisy[i].setStyle(sf::Text::Bold);
    }
}

MainMenu::MainMenu():isselect(false)
{
    font.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Mecha.ttf");
    napisy.emplace_back(sf::Text("New game",font,70));
    napisy.emplace_back(sf::Text("Select Character",font,70));
    napisy.emplace_back(sf::Text("Exit game",font,70));
    this->InitTextPosition();
    window=new sf::RenderWindow(sf::VideoMode(400,300),"Main Menu");
    active=true;
}

MainMenu::~MainMenu()
{
    delete this->window;
}

void MainMenu::UpdateEvents()
{
    if(active==true)
    {
    while (this->window->pollEvent(this->event)) {
        if(this->event.type==sf::Event::MouseButtonPressed)
        {
            if(this->event.mouseButton.button==sf::Mouse::Left)
            {
                for(size_t i=0;i<napisy.size();i++)
                {
                    sf::Vector2i v=sf::Mouse::getPosition(*window);
                    if(napisy[i].getGlobalBounds().contains(v.x,v.y))
                    {
                        active=false;
                        window->close();
                        break;
                    }
                }
            }
        }
        if(this->event.type==sf::Event::Closed)
        {
            window->close();
        }
    }
    }


}

void MainMenu::Drawing()
{
    if(active==true)
    {
    this->window->clear(sf::Color::Black);
    for(size_t i=0;i<napisy.size();i++)
    {
        this->window->draw(napisy[i]);
    }
    this->window->display();
    }
}

bool MainMenu::Running()
{
    return this->window->isOpen();
}
