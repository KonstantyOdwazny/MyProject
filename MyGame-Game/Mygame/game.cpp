#include "game.h"
//constructor
Game::Game()
{
    //view.setViewport(sf::FloatRect(0.0f,0.0f,800.0f,600.0f));
    view.setSize(800.0f,600.0f);
    view.setCenter(0.0f,0.0f);
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    this->level=new MapGame("map.level");
    hero=new MyCharacter;
    this->hero->InitTexture("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_maleAdventurer_sheet.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(0.0f,420.0f);
}
//destructor
Game::~Game()
{
    delete this->window;
    delete  this->level;
    delete this->hero;
}
//functions

//functions of event in game
void Game::pollevent()
{
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type==sf::Event::Closed || this->ev.key.code==sf::Keyboard::Escape)
        {
            this->window->close();
        }
        if(this->ev.key.code==sf::Keyboard::Left){
            this->hero->setScale(-0.5f,0.5f);
        }
        if(this->ev.key.code==sf::Keyboard::Right){
            this->hero->setScale(0.5f,0.5f);
        }
    }
}
//funkcja update gdzie zmieniamy pozycje obiektow i dodajemy zdarzenia przyciskow wejscia np klawiatury
void Game::update()
{
    //level->getposition(10);
    //running
    this->window->setFramerateLimit(60); //limit fps-ow
    this->elapsed=this->clock.restart(); //restart a clock
    /*
     * Zdarzenia klawiatury
     *
     *
     */
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(this->hero->vx<100.0f){
        this->hero->vx+=10.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
        //this->hero->moving(elapsed);

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(this->hero->vx>-100.0f){
        this->hero->vx-=10.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
        //this->hero->moving(elapsed);

    }
    else{
        this->hero->run=false;
        this->hero->vx=0.0f;
        //this->hero->stop();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if((this->hero->y - this->hero->getPosition().y)<70.0f){
             this->hero->ay=-9.81f;
             this->hero->vy+=this->hero->ay;

        }else if((this->hero->y - this->hero->getPosition().y)>0.0f){
            this->hero->ay=9.81f;
            this->hero->vy+=this->hero->ay;
        }

        this->hero->jump=true;
        this->hero->jumpstep();
    }
    else{
        if(this->hero->colission(this->level->sprites))
        {
            this->hero->ay=0;
            this->hero->vy=0;
        }
        else if((this->hero->y - this->hero->getPosition().y)>0.0f)
        {
             this->hero->ay=9.81f;
             this->hero->vy+=this->hero->ay;
             this->hero->jumpstep();
        }
        else
        {
        this->hero->jump=false;
        this->hero->vy=0.0f;
        this->hero->ay=0.0f;
        }

    }
    //animacja kiedy postac stoi
    if(this->hero->vx==0.0f&&this->hero->vy==0.0f){
        this->hero->stop();
    }
    this->hero->moving(elapsed); //poruszanie naszym bohaterem

    this->level->CheckCollision(*this->hero,1.0f);

}
//function where we draw everything and set the view options
void Game::render()
{
    this->view.setCenter(this->hero->getPosition());
    window->clear(sf::Color::Black);
    //view
    window->setView(this->view);
    //draw game object
    level->drawing(*window);
    this->hero->render(*window);
    this->window->display();
}
//bool functions return true if our windows is open
bool Game::running()
{
    return this->window->isOpen();
}

