#include "optionswindow.h"

void OptionsWindow::InitTexture()
{
    this->texture=new sf::Texture();
    this->texture->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Select.png");
    this->texture->setRepeated(true);
    this->sprite=new sf::Sprite();
    this->sprite->setTexture(*this->texture);
}

void OptionsWindow::InitMusic()
{
    click_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/metalClick.ogg");
    click_sound.setBuffer(click_buffer);
    main_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/MagoryNET-Dreams-In-A-Stasis-Chamber.ogg");
    main_music.setBuffer(main_buffer);
    main_music.setLoop(true);
    contains_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/handleSmallLeather.ogg");
    contains_music.setBuffer(contains_buffer);
}

void OptionsWindow::InitText()
{
    font.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Mecha.ttf");
    txt.emplace_back(sf::Text("Jack",font,40));
    txt.emplace_back(sf::Text("Lara",font,40));
    txt.emplace_back(sf::Text("John",font,40));
    txt.emplace_back(sf::Text("Jessica",font,40));
    for(size_t i=0;i<txt.size();i++)
    {
        txt[i].setFillColor(sf::Color::White);
        txt[i].setStyle(sf::Text::Bold);
        txt[i].setPosition(10.0f+i*200.0f,300.0f);
    }

}
//constructor
OptionsWindow::OptionsWindow():exitorplay(false)
{
    window=new sf::RenderWindow(sf::VideoMode(800,600),"Options");
    this->InitText();
    this->InitMusic();
    this->InitTexture();
}
//destructor
OptionsWindow::~OptionsWindow()
{
    delete this->texture;
    delete this->sprite;
    delete this->window;
}

bool OptionsWindow::Running()
{
    return this->window->isOpen();
}

void OptionsWindow::Update()
{
    for(size_t i=0;i<txt.size();i++)
    {
     sf::Vector2i v=sf::Mouse::getPosition(*window);
     if(txt[i].getGlobalBounds().contains(v.x,v.y))
     {
         contains_music.play();
         txt[i].setFillColor(sf::Color::Red);
     }
     else
     {
         txt[i].setFillColor(sf::Color::White);
     }
    }
}

void OptionsWindow::PollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type==sf::Event::Closed)
        {
            exitorplay=false;
            this->main_music.stop();
            this->window->close();
        }

        if(this->ev.type==sf::Event::MouseButtonPressed)
        {
            if(this->ev.mouseButton.button==sf::Mouse::Left)
            {
                click_sound.play();
                for(size_t i=0;i<txt.size();i++)
                {
                    sf::Vector2i v=sf::Mouse::getPosition(*window);
                    if(txt[i].getGlobalBounds().contains(v.x,v.y))
                    {
                        if(txt[i].getString()=="Jack")
                        {
                            exitorplay=true;
                        this->heroclass=HeroClass::MaleAdventure;
                        main_music.stop();
                        window->close();
                        break;
                        }
                        else if(txt[i].getString()=="Lara")
                        {
                            exitorplay=true;
                            this->heroclass=HeroClass::FemaleAdventure;
                            main_music.stop();
                            window->close();
                            break;
                        }
                        else if(txt[i].getString()=="John")
                        {
                            exitorplay=true;
                            this->heroclass=HeroClass::BlackMale;
                            main_music.stop();
                            window->close();
                            break;
                        }
                        else if(txt[i].getString()=="Jessica")
                        {
                            exitorplay=true;
                            this->heroclass=HeroClass::BlackFemale;
                            main_music.stop();
                            window->close();
                            break;
                        }
                    }
                }
            }
        }
    }
}

void OptionsWindow::PlayMusic()
{
    main_music.play();
}

void OptionsWindow::Drawing()
{
    this->window->clear(sf::Color::Black);
    this->window->draw(*this->sprite);
    for(size_t i=0;i<txt.size();i++)
    {
        this->window->draw(txt[i]);
    }
    this->window->display();
}
