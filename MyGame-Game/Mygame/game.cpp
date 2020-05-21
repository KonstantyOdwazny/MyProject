#include "game.h"
//constructor
Game::Game()
{
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    this->level=new MapGame("map.level");
    hero=new MyCharacter;
    this->hero->InitTexture("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_maleAdventurer_sheet.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(0.0f,390.0f);
}
//destructor
Game::~Game()
{
    delete this->window;
    delete  this->level;
    delete this->hero;
}
//functions
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
void Game::update()
{
    //level->getposition(10);
    //running
    this->window->setFramerateLimit(60);
    this->elapsed=this->clock.restart();
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
    if(this->hero->vx==0.0f&&this->hero->vy==0.0f){
        this->hero->stop();
    }
    this->hero->moving(elapsed);


}
void Game::render()
{
    window->clear(sf::Color::Black);
    //draw game object
    level->drawing(*window);
    this->hero->render(*window);
    this->window->display();
}

bool Game::running()
{
    return this->window->isOpen();
}

