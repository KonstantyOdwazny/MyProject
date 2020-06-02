#include "game.h"
#include <cmath>
//private functions
void Game::InitTextures()
{
    tex_hud=std::make_unique<sf::Texture>();
    tex_hud->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/spritesheet_hud.png");

    sf::Vector2u v=this->tex_hud->getSize();
    v.x/=8;
    v.y/=8;
    tex_hud->setRepeated(true);

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<8;j++)
        {
            this->game_rect.emplace_back(sf::IntRect(i*v.x,j*v.y,v.y,v.x));
        }
    }
    for(int i=0;i<6;i++)
    {
        auto sp=std::make_unique<sf::Sprite>();
        if(i==3)
        {
            sp->setTexture(*this->tex_hud);
            sp->setTextureRect(this->game_rect[4]);
            sp->setScale(0.3f,0.3f);
        }
        else if(i<3)
        {
            sp->setTexture(*this->tex_hud);
            sp->setTextureRect(this->game_rect[2]);
            sp->setScale(0.3f,0.3f);
        }
        else if(i>3)
        {
            sp->setTexture(*this->tex_hud);
            sp->setTextureRect(this->game_rect[14]);
            sp->setScale(0.3f,0.3f);
        }
        this->game_sprites.emplace_back(std::move(sp));
    }
}
//change game textures position to textures always be in the top left corner
void Game::Update_TexturesPosition()
{
    for(size_t i=0;i<this->game_sprites.size();i++)
    {
        if(i==0)
        {
            this->game_sprites[i]->setPosition(this->view.getCenter().x-400.0f,this->view.getCenter().y-290.0f);
        }
        else
        {
            this->game_sprites[i]->setPosition(game_sprites[i-1]->getGlobalBounds().left+game_sprites[i-1]->getGlobalBounds().width,this->view.getCenter().y-290.0f);
        }

    }
}
//constructor
Game::Game()
{

    this->InitTextures();
    licz_pom=0;
    //view.setViewport(sf::FloatRect(0.0f,0.0f,800.0f,600.0f));
    view.setSize(800.0f,600.0f);
    view.setCenter(0.0f,0.0f);
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    this->level=new MapGame("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/map.level");
    //create hero
    hero=new MyCharacter;
    this->hero->InitTexture("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_maleAdventurer_sheet.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(300.0f,300.0f);
    this->hero->start_position.x=300.0f;
    this->hero->start_position.y=280.0f;
    //this->hero->setPosition(this->level->pom);
    //create items
    this->things=new Items("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/item.level");
    //create enemies
    this->enemies=new Enemies("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/enemies.level");
}
//destructor
Game::~Game()
{
    delete this->window;
    delete  this->level;
    delete this->hero;
    delete this->things;
    delete  this->enemies;
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
//detection collision hero witch items
void Game::hero_and_itemsCollision(sf::Vector2f &direction, float p)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem

    for(size_t i=0;i<this->things->items.size();i++)
    {
        for(size_t j=0;j<this->things->items[i].size();j++)
        {
            sf::Vector2f thisposition=this->things->items[i][j]->getPosition(); //pozycja przedmiotu
            sf::Vector2f otherposition=this->hero->getPosition(); //pozycja aktualna bohatera
            sf::Vector2f thishalfsize(this->things->items[i][j]->getGlobalBounds().width/2.0f,this->things->items[i][j]->getGlobalBounds().height/2.0f);
            sf::Vector2f otherhalfsize(this->hero->getGlobalBounds().width/2.0f,this->hero->getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(this->things->typeofitem[i][j].dynamic==true){

             if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         this->things->items[i][j]->move(intersectX,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                         hero->move(-0.0f,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     this->things->items[i][j]->move(-intersectX,0.0f);
                     hero->move(0.0f,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         this->things->items[i][j]->move(0.0f,intersectY*(1.0f-p));
                         hero->move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     this->things->items[i][j]->move(0.0f,-intersectY*(1.0f-p));
                     hero->move(0.0f,intersectY*p);


                     direction.x=0.0f;
                     direction.y=-1.0f;
                    }
                 }
                 t=true;

             }
             else{
                 t=false;
             }
             if(t==true)
             {
                 this->hero->OnitemCollision(direction);
             }
           }
        }
    }
}
//detection collision map with items
void Game::map_collision_items(sf::Vector2f &direction, float p)
{


    for(size_t i=0;i<this->level->sprites.size();i++)
    {
        for(size_t j=0;j<this->level->sprites[i].size();j++)
        {

            for(size_t a=0;a<things->items.size();a++){
                for(size_t b=0;b<things->items[a].size();b++)
                {
                    if(things->typeofitem[a][b].dynamic==true){
                    sf::Vector2f thisposition=this->level->sprites[i][j]->getPosition();
                    sf::Vector2f thishalfsize(this->level->sprites[i][j]->getGlobalBounds().width/2.0f,this->level->sprites[i][j]->getGlobalBounds().height/2.0f);
                    sf::Vector2f otherposition=this->things->items[a][b]->getPosition();
                    sf::Vector2f otherhalfsize(things->items[a][b]->getGlobalBounds().width/2.0f,things->items[a][b]->getGlobalBounds().height/2.0f);
                    bool t;

                    float deltax; //zmienna odleglosc miedzy pozycja x przedmiotu i pozycja x innych obiektow
                    float deltay; //zmienna odleglosc miedzy pozycja y przedmiotu i pozycja y innych obiektow
                    float intersectX; //przeciecie w osi X obiektu z przedmiotem
                    float intersectY; //przeciecie w osi Y obiektu z przedmiotem

                     deltax=otherposition.x-thisposition.x;
                     deltay=otherposition.y-thisposition.y;

                     intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
                     intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

                     if(intersectX<1.0f && intersectY<1.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
                     {
                         p=std::min(std::max(p,0.0f),1.0f);

                         if(intersectX > intersectY)
                         {
                             if(deltax > 0.0f)
                             {
                                 this->level->sprites[i][j]->move(intersectX*(1.0f-p),0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                                 things->items[a][b]->move(-intersectX*p,0.0f);

                                 direction.x=1.0f;
                                 direction.y=0.0f;
                             }
                             else
                            {
                             this->level->sprites[i][j]->move(-intersectX*(1.0f-p),0.0f);
                             things->items[a][b]->move(intersectX*p,0.0f);

                             direction.x=-1.0f;
                             direction.y=0.0f;
                            }
                         }
                         else
                         {
                             if(deltay > 0.0f)
                             {
                                 this->level->sprites[i][j]->move(0.0f,intersectY*(1.0f-p));
                                 things->items[a][b]->move(0.0f,-intersectY*p);

                                 direction.x=0.0f;
                                 direction.y=1.0f;
                             }
                             else
                            {
                             this->level->sprites[i][j]->move(0.0f,-intersectY*(1.0f-p));
                             things->items[a][b]->move(0.0f,intersectY*p);

                             direction.x=0.0f;
                             direction.y=-1.0f;
                            }
                         }

                         t=true;

                     }
                     else{
                         t=false;
                     }

                    if(t==true)
                    {

                        this->things->Collision_events(direction,a,b);
                    }
                    }
                }
            }
        }
    }

}

void Game::EnemiesWithItems_collision(sf::Vector2f &direction, float p)
{
    if(enemies->sprites.empty()==false)
    {
    float deltax; //zmienna odleglosc miedzy pozycja x wroga i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y wroga i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z wrogiem
    float intersectY; //przeciecie w osi Y obiektu z wrogiem

    for(size_t a=0;a<this->enemies->sprites.size();a++)
    {
        for(size_t i=0;i<this->things->items.size();i++)
        {
            for(size_t j=0;j<this->things->items[i].size();j++)
            {
                sf::Vector2f thisposition=this->things->items[i][j]->getPosition(); //pozycja przedmiotu
                sf::Vector2f otherposition=this->enemies->sprites[a]->getPosition(); //pozycja aktualna wroga
                sf::Vector2f thishalfsize(this->things->items[i][j]->getGlobalBounds().width/2.0f,this->things->items[i][j]->getGlobalBounds().height/2.0f);
                sf::Vector2f otherhalfsize(this->enemies->sprites[a]->getGlobalBounds().width/2.0f,this->enemies->sprites[a]->getGlobalBounds().height/2.0f);
                bool t;
                deltax=otherposition.x-thisposition.x;
                deltay=otherposition.y-thisposition.y;

                intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
                intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

                if(this->things->typeofitem[i][j].dynamic==true){

                if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
                {
                    p=std::min(std::max(p,0.0f),1.0f);

                    if(intersectX > intersectY)
                    {
                        if(deltax > 0.0f)
                        {
                            this->things->items[i][j]->move(intersectX,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                            enemies->sprites[a]->move(-0.0f,0.0f);

                            direction.x=1.0f;
                            direction.y=0.0f;
                        }
                        else
                       {
                        this->things->items[i][j]->move(-intersectX,0.0f);
                        enemies->sprites[a]->move(0.0f,0.0f);

                        direction.x=-1.0f;
                        direction.y=0.0f;
                       }
                    }
                    else
                    {
                        if(deltay > 0.0f)
                        {
                            this->things->items[i][j]->move(0.0f,intersectY*(1.0f-p));
                            enemies->sprites[a]->move(0.0f,-intersectY*p);

                            direction.x=0.0f;
                            direction.y=1.0f;
                        }
                        else
                       {
                        this->things->items[i][j]->move(0.0f,-intersectY*(1.0f-p));
                        enemies->sprites[a]->move(0.0f,intersectY*p);


                        direction.x=0.0f;
                        direction.y=-1.0f;
                       }
                    }
                    t=true;

                }
                else{
                    t=false;
                }
                if(t==true)
                {
                    this->enemies->OnCollision(direction,a);
                }
                }
            }
        }

    }
    }
}

void Game::Hero_Enemies_Collision(sf::Vector2f &direction, float p)
{
    if(enemies->sprites.empty()==false)
    {
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x wroga
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y wroga
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem


        for(size_t i=0;i<this->enemies->sprites.size();i++)
        //for(auto it=enemies->sprites.begin();it!=enemies->sprites.end();it++)
        {
            //size_t i=std::distance(enemies->sprites.begin(),it);
            sf::Vector2f thisposition=this->enemies->sprites[i]->getPosition(); //pozycja przedmiotu
            sf::Vector2f otherposition=this->hero->getPosition(); //pozycja aktualna bohatera
            sf::Vector2f thishalfsize(this->enemies->sprites[i]->getGlobalBounds().width/2.0f,this->enemies->sprites[i]->getGlobalBounds().height/2.0f);
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
                         this->enemies->sprites[i]->move(intersectX,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                         hero->move(-0.0f,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     this->enemies->sprites[i]->move(-intersectX,0.0f);
                     hero->move(0.0f,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         this->enemies->sprites[i]->move(0.0f,intersectY*(1.0f-p));
                         hero->move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     this->enemies->sprites[i]->move(0.0f,-intersectY*(1.0f-p));
                     hero->move(0.0f,intersectY*p);

                     this->enemies->Dead(i);
                     direction.x=0.0f;
                     direction.y=-1.0f;
                    }
                 }
                 t=true;

             }
             else{
                 t=false;
             }
             if(t==true)
             {
                 this->hero->OnEnemiesCollision(direction);
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

    for(size_t i=0;i<this->things->typeofitem.size();i++){
        for(size_t j=0;j<things->typeofitem[i].size();j++)
        {
            if(things->typeofitem[i][j].dynamic==true)
            {
                things->typeofitem[i][j].velocity.y+=981.0f*elapsed.asSeconds();
                things->typeofitem[i][j].velocity.x=0.0f;
            }
        }
    }

    this->hero->vy+=981.0f*elapsed.asSeconds();

    this->CheckCollision(direction,1.0f); //sprawdzamy kolizje przed poruszeniem sie postaci aby sprawdzic czy moze ona sie poruszac
    this->map_collision_items(direction,1.0f); //sprawdzamy kolizje przedmiotow z elementami mapy
    this->hero_and_itemsCollision(direction,1.0f); //sprawdzamy kolizje gracza z przedmiotami
    this->things->Collider_items();
    if(enemies->sprites.empty()==false)
    {
    this->Hero_Enemies_Collision(direction,0.0f);
    this->EnemiesWithItems_collision(direction,0.0f);
    }

    this->hero->moving(elapsed); //poruszanie naszym bohaterem
    this->things->moving(elapsed);
    if(enemies->sprites.empty()==false)
    {
    this->enemies->moving(elapsed);
    }

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
    if(licz_pom==0)
    {
    this->level->backgrounds->setPosition(this->view.getCenter().x-600.0f,this->view.getCenter().y-800.0f);
    }
    licz_pom++;
    this->Update_TexturesPosition();
    window->clear(sf::Color::Black);
    //view
    window->setView(this->view);
    //draw game object
    level->drawing(*window);
    things->drawing(*window);
    if(enemies->sprites.empty()==false)
    {
    enemies->drawing(*window);
    }
    this->hero->render(*window);
    for(size_t i=0;i<this->game_sprites.size();i++)
    {
        this->window->draw(*this->game_sprites[i]);
    }
    this->window->display();
}
//bool functions return true if our windows is open
bool Game::running()
{
    return this->window->isOpen();
}

