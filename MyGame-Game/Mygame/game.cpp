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
    this->hero->setposition(300.0f,300.0f);
    //this->hero->setPosition(this->level->pom);
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
        if(this->ev.key.code==sf::Keyboard::Space){
            this->hero->jump=true;
           // this->hero->jumpstep(); //jump hero animation frame
        }

    }
}
//funckja do sprawdzania kolizji gracza z otoczeniem
void Game::CheckCollision(sf::Vector2f &direction, float p)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem

    //sprawdzamy kolizje naszego bohatera z kazdym obiektem na naszej mapie
    for(size_t i=0;i<this->level->sprites.size();i++)
    {
        for(size_t j=0;j<this->level->sprites[i].size();j++)
        {


            sf::Vector2f thisposition=this->level->sprites[i][j]->getPosition(); //pozycja bohatera
            sf::Vector2f otherposition=this->hero->getPosition(); //pozycja aktualnego obiektu
            sf::Vector2f thishalfsize(this->level->sprites[i][j]->getGlobalBounds().width/2.0f,this->level->sprites[i][j]->getGlobalBounds().height/2.0f);
            //thishalfsize.x=this->level->sprites[i][j]->getGlobalBounds().width/2.0f;
            //thishalfsize.y=this->level->sprites[i][j]->getGlobalBounds().height/2.0f;
            sf::Vector2f otherhalfsize(this->hero->getGlobalBounds().width/2.0f,this->hero->getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         this->level->sprites[i][j]->move(intersectX*(1.0f-p),0.0f); //odbicia podczas zderzen kazdy w innym kierunku
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
        if(this->hero->vx<600.0f){
        this->hero->vx+=100.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
        this->hero->facerigth=true;

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(this->hero->vx>-600.0f){
        this->hero->vx-=100.0f;
        }
        this->hero->run=true;
        this->hero->runstep(this->elapsed);
       this->hero->facerigth=false;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->hero->canjump)
    {
        this->hero->canjump=false;
        //gravity
        this->hero->vy=-sqrtf(2.0f*981.0f*this->hero->jumpHeight); //float square root
        this->hero->jumpstep(); //jump hero animation frame


    }

    this->hero->vy+=981.0f*elapsed.asSeconds();

    this->CheckCollision(direction,1.0f); //sprawdzamy kolizje przed poruszeniem sie postaci aby sprawdzic czy moze ona sie poruszac

    this->hero->moving(elapsed); //poruszanie naszym bohaterem

     //animacja kiedy postac stoi
    if(this->hero->vx==0.0f&&this->hero->vy==0.0f){
        this->hero->stop(elapsed);
        this->hero->jump=false;
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

