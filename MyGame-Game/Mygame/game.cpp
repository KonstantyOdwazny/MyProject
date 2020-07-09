#include "game.h"
#include <cmath>
#include <windows.h>
#include <iostream>
//private functions
//Create game textures like hearts and coin
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
    for(int i=0;i<4;i++)
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

        this->game_sprites.emplace_back(std::move(sp));
    }
}
//create game text like game over and number of coins
void Game::InitText()
{
    //coinsy
    coins_licz=0;
    font.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Mecha.ttf");
    std::string ctext="0";
    this->coin_text.setString(ctext);
    this->coin_text.setFont(font);
    this->coin_text.setCharacterSize(30);
    this->coin_text.setFillColor(sf::Color::White);
    this->coin_text.setStyle(sf::Text::Bold);

    this->gameover.setString("GAME OVER");
    this->gameover.setFont(font);
    this->gameover.setCharacterSize(72);
    this->gameover.setFillColor(sf::Color::Yellow);
    this->gameover.setStyle(sf::Text::Bold);

    this->again.setString("Click ENTER to start again");
    this->again.setFont(font);
    this->again.setCharacterSize(40);
    this->again.setFillColor(sf::Color::Yellow);
    this->again.setStyle(sf::Text::Bold);
}
//create main light hero
void Game::InitLight()
{
    //light
    this->lightingTex.create(2900,3000);
    this->light.setRadius(200.0f);
    this->light.setPointCount(30);
    this->light.setFillColor(sf::Color(255,255,255));
}
//create lightings
void Game::InitLightings()
{
    kolor_licz=0;
    //pochodnie
    for(size_t i=0;i<this->things->pochodnie_pozycja.size();i++)
    {
        sf::CircleShape circle(220.0f,30);
        if(kolor_licz==0)
        {
            kolor_licz++;
        circle.setFillColor(sf::Color(255,105,105));
        }
        else if(kolor_licz==1)
        {
            kolor_licz++;
            circle.setFillColor(sf::Color(105,255,105));
        }
        else if(kolor_licz==2)
        {
            kolor_licz=0;
            circle.setFillColor(sf::Color(105,105,255));
        }
        circle.setPosition(things->pochodnie_pozycja[i].x-100.0f,things->pochodnie_pozycja[i].y-50.0f);
        pochodnie.emplace_back(circle);
    }
}
//create constructor other classes
void Game::CreateOtherClasses()
{
    this->level=new MapGame("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/map.level");
    //create hero
    hero=new MyCharacter;
    this->hero->InitTexture("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_maleAdventurer_sheet.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(250.0f,280.0f);
    this->hero->start_position.x=250.0f;
    this->hero->start_position.y=280.0f;
    //this->weapon=new Weapons;
    //this->weapon->setPosition(250.0f,280.0f);
    //this->hero->setPosition(this->level->pom);
    //create items
    this->things=new Items("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/item.level");
    //create enemies
    this->enemies=new Enemies("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/enemies.level");
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
    this->coin_text.setPosition(game_sprites[game_sprites.size()-1]->getGlobalBounds().left+game_sprites[game_sprites.size()-1]->getGlobalBounds().width,this->view.getCenter().y-290.0f);
    if(this->hero->life==2)
    {
        this->game_sprites[0]->setTextureRect(this->game_rect[3]);
    }
    if(this->hero->life==1)
    {
        this->game_sprites[1]->setTextureRect(this->game_rect[3]);
    }
    if(this->hero->life==0)
    {
        this->game_sprites[2]->setTextureRect(this->game_rect[3]);
    }
    this->coin_text.setString(std::to_string(this->coins_licz));

    this->gameover.setPosition(this->view.getCenter().x-100.0f,this->view.getCenter().y);
    this->again.setPosition(this->view.getCenter().x-100.0f,this->view.getCenter().y+100.0f);
}
//Update Keybord
void Game::UpdateKeybordInput()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        time_to_foot_step_sound+=elapsed.asSeconds();
        if(time_to_foot_step_sound>=0.3f)
        {
            time_to_foot_step_sound-=0.3f;
        foot_step_sound.play();
        }
        if(this->hero->vx<900.0f){
        this->hero->vx+=200.0f;

        }
        this->hero->run=true;
        //this->hero->runstep(this->elapsed);
        this->hero->facerigth=true;
        this->hero->begin_stop=0;
        //this->hero->jump_it=1;


    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        //foot_step_sound.play();
        time_to_foot_step_sound+=elapsed.asSeconds();
        if(time_to_foot_step_sound>=0.3f)
        {
            time_to_foot_step_sound-=0.3f;
        foot_step_sound.play();
        }
        if(this->hero->vx>-900.0f){
        this->hero->vx-=200.0f;

        }
        this->hero->run=true;
        //this->hero->runstep(this->elapsed);
       this->hero->facerigth=false;
        this->hero->begin_stop=0;
        //this->hero->jump_it=1;

    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->hero->canjump)
    {
        this->hero->canjump=false;
        //gravity
        this->hero->vy=-sqrtf(2.0f*981.0f*this->hero->jumpHeight); //float square root
        this->hero->jump=true;
        this->hero->begin_stop=0;

    }

    /*
    for(size_t i=0;i<enemies->enemies_statistic.size();i++)
    {
        std::cout<<"Enemy "<<i+1<<" lives: "<<enemies->enemies_statistic[i].lives<<std::endl;
    }
    */
    //hero hit and use weapon animation
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->hero->run==false && this->hero->jump==false && this->hero->weapon->canhit==true)
    {
        //this->hero->weapon->canhit=false;
        this->hero->HitAnimation(elapsed);
        this->WeaponHit(*this->hero->weapon,*this->enemies);
        licznikuderzen++;
        time_to_foot_step_sound+=elapsed.asSeconds();
        if(time_to_foot_step_sound>=0.3f)
        {
            time_to_foot_step_sound-=0.3f;
            hit_sound.play();
        }


    }
    else
    {
        this->hero->weapon->setScale(0.3f,0.3f);
        this->hero->weapon->setPosition(this->hero->getPosition());

    }
    if(licznikuderzen==50)
    {
        this->hero->weapon->canhit=false;
        czasdouderzenia+=elapsed.asSeconds();
        if(czasdouderzenia>=1.5f)
        {
            czasdouderzenia-=1.5f;
            licznikuderzen=0;
            this->hero->weapon->canhit=true;
        }
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->hero->KickAnimation();
    }


}
//Update Collision
void Game::UpdateCollision()
{
    this->CheckCollisions(this->level->sprites,*this->hero,direction,1.0f);
    this->CheckCollisions(this->level->sprites,*this->things,direction,1.0f);
    this->CheckCollisions(*this->things,*this->hero,direction,1.0f,elapsed);
    this->things->Collider_items();
    if(enemies->sprites.empty()==false)
    {
    this->CheckCollisions(this->enemies->sprites,*this->hero,direction,0.0f,elapsed);
    //this->EnemiesWithItems_collision();
    this->CheckCollisions(*enemies,*things,direction);
    }
    this->CollectCoins();
    this->CollectKeys();
    this->OpenDoors();
    this->BulletsCollision(enemies->bullets,*things,*hero,this->level->sprites,elapsed);
    this->hero->moving(elapsed); //poruszanie naszym bohaterem
    this->things->moving(elapsed); //poruszanie sie przedmiotow dynamicznych
}
//constructor
Game::Game()
{
    this->startagain=false;
    this->InitText();
    this->InitLight();
    this->InitTextures();
    set_lighthings_position=0;
    view.setSize(800.0f,600.0f);
    view.setCenter(0.0f,0.0f);
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    //this->equipment=new sf::RenderWindow(sf::VideoMode(800,600),"Equimpent");
    //this->equipment->setVisible(false);
    //this->equipment->setActive(false);
    this->CreateOtherClasses();
    this->InitLightings();
    licznikuderzen=0;
    czasdouderzenia=0.0f;
    collect_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/handleCoins.ogg");
    collect_music.setBuffer(collect_buffer);
    foot_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/footstep00.ogg");
    foot_step_sound.setBuffer(foot_buffer);
    time_to_foot_step_sound=0.0f;
    hit_buffer.loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/knifeSlice.ogg");
    hit_sound.setBuffer(hit_buffer);

}
//destructor
Game::~Game()
{
    delete this->window;
    delete  this->level;
    delete this->hero;
    delete this->things;
    delete  this->enemies;
    //delete menu;
    //delete weapon;
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
            //this->equipment->close();
        }
        if(this->hero->life<=0 && this->ev.key.code==sf::Keyboard::Enter)
        {
            this->startagain=true;
        }

    }

}
//Collect Coins
void Game::CollectCoins()
{
    for(size_t i=0;i<this->things->coinsy.size();i++)
    {
        if(this->hero->getGlobalBounds().intersects(this->things->coinsy[i]->getGlobalBounds()))
        {

            collect_music.play();
            this->coins_licz++;
            this->things->coinsy.erase(this->things->coinsy.begin()+i);
            break;
        }
    }
}
//functions where we check is key collect
void Game::CollectKeys()
{
    for(size_t i=0;i<this->things->keys.size();i++)
    {
    if(this->hero->getGlobalBounds().intersects(this->things->keys[i]->getGlobalBounds()))
    {
        collect_music.play();
        this->things->Collectkeys(i);
    }
    }
}
//function when check collision with doors and check can we open it
void Game::OpenDoors()
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem
    for(size_t i=0;i<things->doors.size();i++)
    {
        sf::Vector2f thisposition=this->things->doors[i]->getPosition(); //pozycja przedmiotu
        sf::Vector2f otherposition=this->hero->getPosition(); //pozycja aktualna bohatera
        sf::Vector2f thishalfsize(this->things->doors[i]->getGlobalBounds().width/2.0f,this->things->doors[i]->getGlobalBounds().height/2.0f);
        sf::Vector2f otherhalfsize(this->hero->getGlobalBounds().width/2.0f,this->hero->getGlobalBounds().height/2.0f);
        bool t;

         deltax=otherposition.x-thisposition.x;
         deltay=otherposition.y-thisposition.y;

         intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
         intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);
         if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
         {
             if(intersectX > intersectY)
             {
                 if(deltax > 0.0f)
                 {
                     this->things->doors[i]->move(0.0f,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                     hero->move(-intersectX,0.0f);

                     direction.x=1.0f;
                     direction.y=0.0f;
                     this->hero->vx=0.0f;
                 }
                 else
                {
                 this->things->doors[i]->move(0.0f,0.0f);
                 hero->move(intersectX,0.0f);

                 direction.x=-1.0f;
                 direction.y=0.0f;
                 this->hero->vx=0.0f;
                }
             }
             else
             {
                 if(deltay > 0.0f)
                 {
                     this->things->doors[i]->move(0.0f,0.0f);
                     hero->move(0.0f,-intersectY);

                     direction.x=0.0f;
                     direction.y=1.0f;
                 }
                 else
                {
                 this->things->doors[i]->move(0.0f,0.0f);
                 hero->move(0.0f,intersectY);


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
             /*
             if(this->things->iskeycollect[i].first==this->things->door_colors[i])
             {
                 if(this->things->iskeycollect[i].second==true)
                 {
                     this->things->doors.erase(this->things->doors.begin()+i);
                 }
             }
             */
             for(size_t j=0;j<things->iskeycollect.size();j++)
             {
                 if(this->things->iskeycollect[j].first==this->things->door_colors[i])
                 {
                     if(this->things->iskeycollect[j].second==true)
                     {
                        this->things->doors.erase(this->things->doors.begin()+i);
                        this->things->door_colors.erase(this->things->door_colors.begin()+i);
                     }
                 }
             }
         }
    }
}

//funkcja update gdzie zmieniamy pozycje obiektow i dodajemy zdarzenia przyciskow wejscia np klawiatury
void Game::update()
{


    if(this->hero->life>0 )
    {
    //running
    this->window->setFramerateLimit(60); //limit fps-ow
    this->elapsed=this->clock.restart(); //restart a clock
    this->hero->vx=0.0f;
    this->hero->run=false;
    this->UpdateKeybordInput();

    //animation update
    this->hero->jumpstep(elapsed); //jump hero animation frame
    this->hero->runstep(this->elapsed); //run hero animation

    //grvity update
    for(size_t i=0;i<this->things->typeofitem.size();i++){
        for(size_t j=0;j<things->typeofitem[i].size();j++)
        {
            if(things->typeofitem[i][j].dynamic==true)
            {
                things->typeofitem[i][j].velocity.y+=981.0f*elapsed.asSeconds(); //sila grawitacji dzialajaca na przedmioty
                things->typeofitem[i][j].velocity.x=0.0f;
            }
        }
    }

    this->hero->vy+=981.0f*elapsed.asSeconds(); //sila grawitacji dzialajaca na bohatera

    this->UpdateCollision();

    if(enemies->sprites.empty()==false)
    {
    this->enemies->moving(elapsed); //poruszanie sie wrogow
    }
    this->enemies->SpecialAtack(elapsed);

     //animacja kiedy postac stoi
    if(this->hero->vx==0.0f&&this->hero->vy==0.0f){
        this->hero->stop(elapsed);
        this->hero->jump=false;
        this->hero->jump_it=1;
    }

    }

    //this->weapon->setPosition(this->hero->getPosition().x+20.0f,this->hero->getPosition().y);
}
//function where we draw everything and set the view options
void Game::render()
{


    window->clear(sf::Color::Black);
    //light
    this->view.setCenter(this->hero->getPosition());
    lightingTex.clear( sf::Color( 0, 0, 0, 0 ) );
    lightingTex.draw( light, sf::BlendAdd ); //tworzenie swiatla na czarnej teksturze
    //pochodnie
    for(size_t i=0;i<this->pochodnie.size();i++)
    {
        lightingTex.draw(pochodnie[i], sf::BlendAdd); //tworzenie swiatel pochodni
    }

    lightingTex.display(); // wywołanie tekstury, zapieczętowanie
    lighting.setTexture( lightingTex.getTexture() );
    if(set_lighthings_position==0)
    {
    lighting.setPosition(this->view.getCenter().x-400.0f,this->view.getCenter().y-300.0f);
    this->level->backgrounds->setPosition(this->view.getCenter().x-600.0f,this->view.getCenter().y-800.0f);
    this->hero->setPosition(250.0f,250.0f);
    //this->coin_text.setPosition(this->view.getCenter());
     set_lighthings_position=1;
    }
    light.setPosition(this->hero->getPosition().x-50.0f,this->hero->getPosition().y-60.0f);

    this->Update_TexturesPosition();
    window->clear(sf::Color::Black);
    //equipment->clear(sf::Color::Red);
    //view
    window->setView(this->view);
    //draw game object
    level->drawing(*window);

    things->drawing(*window);
    if(enemies->sprites.empty()==false)
    {
    enemies->drawing(*window);
    }
    //this->window->draw(*weapon);
    this->hero->render(*window);
    this->window->draw( lighting, sf::BlendMultiply );
    for(size_t i=0;i<this->game_sprites.size();i++)
    {
        this->window->draw(*this->game_sprites[i]);
    }
    this->window->draw(this->coin_text);
    if(this->hero->life<=0)
    {
        this->window->draw(gameover);
        this->window->draw(again);
    }

    this->window->display();
    //this->equipment->display();


}
//bool functions return true if our windows is open
bool Game::running()
{
    return this->window->isOpen();
}

