#include "menu.h"
#include <iostream>

void MainMenu::InitText()
{
    font.loadFromFile("Mecha.ttf");
    napisy.emplace_back(sf::Text("New game",font,70));
    napisy.emplace_back(sf::Text("Sterowanie",font,70));
    napisy.emplace_back(sf::Text("Exit game",font,70));
    for(size_t i=0;i<napisy.size();i++)
    {
        napisy[i].setPosition(10.0f,70.0f+i*100.0f);
        napisy[i].setFillColor(sf::Color::White);
        napisy[i].setStyle(sf::Text::Bold);
    }
}

void MainMenu::InitMusic()
{
    click_buffer.loadFromFile("metalClick.ogg");
    click_sound.setBuffer(click_buffer);
    main_buffer.loadFromFile("MagoryNET-Dreams-In-A-Stasis-Chamber.ogg");
    main_music.setBuffer(main_buffer);
    main_music.setLoop(true);
    contains_buffer.loadFromFile("handleSmallLeather.ogg");
    contains_music.setBuffer(contains_buffer);
}

void MainMenu::InitTexture()
{

    this->texture=new sf::Texture();
    if(!this->texture->loadFromFile("Menu_tlo.png"))
    {
        std::cout<<"Nie otwarl sie!"<<std::endl;
    }
    this->texture->setRepeated(true);
    this->sprite=new sf::Sprite();
    this->sprite->setTexture(*this->texture);

}

MainMenu::MainMenu():isselect(false)
{
    this->InitText();
    window=new sf::RenderWindow(sf::VideoMode(400,600),"Main Menu");
    active=true;
    this->InitMusic();
    this->InitTexture();
}

MainMenu::~MainMenu()
{
    delete this->window;
    delete this->sprite;
    delete this->texture;
}

void MainMenu::PollEvents()
{
    if(active==true)
    {
    while (this->window->pollEvent(this->ev)) {
        if(this->ev.type==sf::Event::MouseButtonPressed)
        {
            if(this->ev.mouseButton.button==sf::Mouse::Left)
            {
                click_sound.play();
                for(size_t i=0;i<napisy.size();i++)
                {
                    sf::Vector2i v=sf::Mouse::getPosition(*window);
                    if(napisy[i].getGlobalBounds().contains(v.x,v.y))
                    {

                        if(napisy[i].getString()=="New game")
                        {
                        active=false;
                        this->action=Activity::StartGame;
                        main_music.stop();
                        window->close();
                        break;
                        }
                        else if(napisy[i].getString()=="Sterowanie")
                        {
                            active=false;
                            this->action=Activity::Sterowanie;
                            main_music.stop();
                            window->close();
                            break;
                        }
                        else if(napisy[i].getString()=="Exit game")
                        {
                            active=false;
                            this->action=Activity::Exit;
                            main_music.stop();
                            window->close();
                            break;
                        }
                    }

                }
            }
        }
        if(this->ev.type==sf::Event::Closed)
        {
            active=false;
            this->action=Activity::Exit;
            main_music.stop();
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
    window->draw(*this->sprite);
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

void MainMenu::PlayMusic()
{
    this->main_music.play();
}

void MainMenu::Update()
{
    for(size_t i=0;i<napisy.size();i++)
    {
     sf::Vector2i v=sf::Mouse::getPosition(*window);
     if(napisy[i].getGlobalBounds().contains(v.x,v.y))
     {
         contains_music.play();
         napisy[i].setFillColor(sf::Color::Red);
     }
     else
     {
         napisy[i].setFillColor(sf::Color::White);
     }
    }
}
