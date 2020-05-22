#include "game.h"
#include <cmath>
//constructor
Game::Game()
{
    //view.setViewport(sf::FloatRect(0.0f,0.0f,800.0f,600.0f));
    view.setSize(800.0f,600.0f);
    view.setCenter(0.0f,0.0f);
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    this->level=new MapGame("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/map.level");
    hero=new MyCharacter;
    this->hero->InitTexture("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_maleAdventurer_sheet.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(400.0f,420.0f);
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
//funckja do sprawdzania kolizji gracza z otoczeniem
void Game::CheckCollision(sf::Vector2f &direction, float p)
{


    //std::vector<sf::Vector2f> thispositions;
    //std::vector<sf::Vector2f> thishalfsizes;
    //sf::Vector2f thishalfsize(this->level->sprites[0][0]->getGlobalBounds().width/2.0f,this->level->sprites[0][0]->getGlobalBounds().height/2.0f);
    float deltax;
    float deltay;
    float intersectX;
    float intersectY;

    //musze sprawdzic dla kazdego z osobna
    for(size_t i=0;i<this->level->sprites.size();i++)
    {
        for(size_t j=0;j<this->level->sprites[i].size();j++)
        {


            sf::Vector2f thisposition=this->level->sprites[i][j]->getPosition();
            sf::Vector2f otherposition=this->hero->getPosition();
            sf::Vector2f thishalfsize(this->level->sprites[i][j]->getGlobalBounds().width/2.0f,this->level->sprites[i][j]->getGlobalBounds().height/2.0f);
            //thishalfsize.x=this->level->sprites[i][j]->getGlobalBounds().width/2.0f;
            //thishalfsize.y=this->level->sprites[i][j]->getGlobalBounds().height/2.0f;
            sf::Vector2f otherhalfsize(this->hero->getGlobalBounds().width/2.0f,this->hero->getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(intersectX<0.0f && intersectY<0.0f)
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         this->level->sprites[i][j]->move(intersectX*(1.0f-p),0.0f);
                         hero->move(-intersectX*p,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     this->level->sprites[i][j]->move(-intersectX*(1.0f-p),0.0f);
                     hero->move(intersectX*p,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         this->level->sprites[i][j]->move(0.0f,intersectY*(1.0f-p));
                         hero->move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     this->level->sprites[i][j]->move(0.0f,-intersectY*(1.0f-p));
                     hero->move(0.0f,intersectY*p);

                     direction.x=0.0f;
                     direction.y=-1.0f;
                    }
                 }
                 //return true;
                 t=true;

             }
             else{
                 t=false;
             }
            if(t==true)
            {
                this->hero->Oncollision(direction);
            }
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
    this->hero->vx=0.0f;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(this->hero->vx<300.0f){
        this->hero->vx+=30.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
        //this->hero->moving(elapsed);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(this->hero->vx>-300.0f){
        this->hero->vx-=30.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
        //this->hero->moving(elapsed);

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        this->hero->vy+=30.0f;
    }
    /*
    else{
        this->hero->run=false;
        this->hero->vx=0.0f;
        //this->hero->stop();
    }
    */

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->hero->canjump)
    {
        this->hero->canjump=false;
        //gravity
        this->hero->vy=-sqrtf(2.0f*981.0f*this->hero->jumpHeight); //float square root
    }

    this->hero->vy+=981.0f*elapsed.asSeconds();

    this->CheckCollision(direction,1.0f);
    this->hero->moving(elapsed); //poruszanie naszym bohaterem
     //animacja kiedy postac stoi
    if(this->hero->vx==0.0f&&this->hero->vy==0.0f){
        this->hero->stop();
    }

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

