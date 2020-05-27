#include "items.h"
#include <string>
#include <fstream>
#include <iostream>


//private functions
//load texture from file
void Items::loadfromfile(const std::string &filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                int pom;
                file>>pom;

                if(pom==0)
                {
                    poziom[i][j].iswall=false;
                }
                else
                {
                    poziom[i][j].iswall=true;
                }
                poziom[i][j].type=pom-1;
            }
        }
    }
    else
    {
        std::cout<<"Nie otwarl sie";
    }
    file.close();
}
//create a items sprite
void Items::createSprite()
{

    for(int j=0;j<4;j++)
    {
    for(int i=0;i<16;i++){

        auto t=std::make_unique<sf::Texture>();
        t->loadFromFile("Spritesheets/spritesheet_tiles.png",sf::IntRect(j*tile_width,i*tile_height,tile_width,tile_height));
        t->setRepeated(true);
        this->textures.emplace_back(std::move(t));
    }
    }
     std::vector<std::unique_ptr<sf::Sprite>> sp;
     std::vector<item_type> itemname;


     for(int i=0;i<height;i++)
     {
         for(int j=0;j<width;j++)
         {
             if(poziom[i][j].iswall==true){


                if(poziom[i][j].type>=0 && poziom[i][j].type<=9){
                    item_type it;
                    it.name="pudelko";
                    it.dynamic=true;
                    it.velocity.x=0.0f;
                    it.velocity.y=0.0f;
                    itemname.emplace_back(it);
                }
                else{
                    item_type it;
                    it.name="nic";
                    it.dynamic=false;
                    it.velocity.x=0.0f;
                    it.velocity.y=0.0f;
                    itemname.emplace_back(it);
                }

             auto s=std::make_unique<sf::Sprite>();
             s->setTexture(*textures[poziom[i][j].type]);
             s->setScale(0.5f,0.5f);
             s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
             s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);

             sp.emplace_back(std::move(s));
             }
         }
         this->items.emplace_back(std::move(sp));
         this->typeofitem.emplace_back(itemname);


         itemname.clear();
         sp.clear();
     }

}
//constructors
Items::Items()
{

}

Items::Items(std::string filename)
{
    loadfromfile(filename);
    createSprite();
}
//public functions
void Items::drawing(sf::RenderTarget &target)
{
    for(size_t i=0;i<this->items.size();i++)
    {
        for(size_t j=0;j<this->items[i].size();j++)
        {
            target.draw(*items[i][j]);
        }
    }
}
//what hapen when items collider
void Items::Collision_events(sf::Vector2f &direction,const size_t& i,const size_t& j)
{
    if(direction.x <0.0f)
    {
        //Collision on the left
        this->typeofitem[i][j].velocity.x=0.0f;
        //vx=0.0f;
    }
    else if(direction.x >0.0f)
    {
        //Collision on the rigth
        //vx=0.0f;
        this->typeofitem[i][j].velocity.x=0.0f;
    }

    if(direction.y < 0.0f)
    {
        //Collision on the bottom
        //vy=0.0f;
        this->typeofitem[i][j].velocity.y=0.0f;

    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        //vy=0.0f;
        this->typeofitem[i][j].velocity.y=98.0f;
    }
}

void Items::moving(sf::Time& elapsed)
{
    for(size_t i=0;i<items.size();i++)
    {
        for(size_t j=0;j<items[i].size();j++)
        {
            if(typeofitem[i][j].dynamic==true){
            items[i][j]->move(typeofitem[i][j].velocity.x*elapsed.asSeconds(),typeofitem[i][j].velocity.y*elapsed.asSeconds());
            //std::cout<<items[i][j]->getPosition().x<<"  "<<items[i][j]->getPosition().y<<std::endl;
            }
        }
    }
}
//collision items with another items
void Items::Collider_items()
{
    for(size_t i=0;i<items.size();i++)
    {
        for(size_t j=0;j<items[i].size();j++)
        {
            for(size_t a=0;a<items.size();a++)
            {
                for(size_t b=0;b<items[a].size();b++)
                {
                    if(typeofitem[i][j].dynamic==true && typeofitem[a][b].dynamic==true && (a!=i || b!=j)){
                    sf::Vector2f thisposition=items[i][j]->getPosition();
                    sf::Vector2f thishalfsize(items[i][j]->getGlobalBounds().width/2.0f,items[i][j]->getGlobalBounds().height/2.0f);
                    sf::Vector2f otherposition=items[a][b]->getPosition();
                    sf::Vector2f otherhalfsize(items[a][b]->getGlobalBounds().width/2.0f,items[a][b]->getGlobalBounds().height/2.0f);
                    bool t;
                    float deltax; //zmienna odleglosc miedzy pozycja x jednego przedmiotu i pozycja x innego przedmiotu
                    float deltay; //zmienna odleglosc miedzy pozycja y jednego przedmiotu i pozycja y innego przedmiotu
                    float intersectX; //przeciecie w osi X przedmiotu z innym przedmiotem
                    float intersectY; //przeciecie w osi Y przedmiotu z innym przedmiotem

                    sf::Vector2f direction;
                    deltax=otherposition.x-thisposition.x;
                    deltay=otherposition.y-thisposition.y;

                    intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
                    intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

                    if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
                    {
                        //p=std::min(std::max(p,0.0f),1.0f);
                        float p=0.0f;

                        if(intersectX > intersectY)
                        {
                            if(deltax > 0.0f)
                            {
                                items[i][j]->move(intersectX*(1.0f-p),0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                                items[a][b]->move(-intersectX*(1.0f-p),0.0f);

                                direction.x=1.0f;
                                direction.y=0.0f;
                            }
                            else
                           {
                            items[i][j]->move(-intersectX*(1.0f-p),0.0f);
                            items[a][b]->move(intersectX*(1.0f-p),0.0f);

                            direction.x=-1.0f;
                            direction.y=0.0f;
                           }
                        }
                        else
                        {
                            if(deltay > 0.0f)
                            {
                                //items[i][j]->move(0.0f,intersectY*(1.0f-p));
                                //items[a][b]->move(0.0f,-intersectY*p);

                                direction.x=0.0f;
                                direction.y=1.0f;
                            }
                            else
                           {
                           // items[i][j]->move(0.0f,-intersectY*(1.0f-p));
                           // items[a][b]->move(0.0f,intersectY*p);

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

                        this->Collision_events(direction,a,b);
                    }
                    }

                }
            }
        }
    }
}



/*

//private functions
//load from file positions our enemies
void Enemies::InitSprite()
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(poziom[i][j].iswall==true)
            {
                auto s=std::make_unique<sf::Sprite>();
                s->setTexture(*textures[poziom[i][j].type]);
                s->setTextureRect(this->vector_animationframe[0]);
                s->setScale(0.5f,0.5f);
                s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);
                sprites.emplace_back(std::move(s));
               // this->veclocities.emplace_back(sf::Vector2f(200.0f,0.0f));
            }
        }
    }
}
//set animation frame
void Enemies::animationframe()
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            this->vector_animationframe.emplace_back(sf::IntRect(j*tile_width,i*tile_height,tile_width,tile_height));
        }
    }
}
//load from file position enemies
void Enemies::loadfromfile(const std::string &filename)
{
    std::ifstream file(filename);
    if(file.is_open())
    {
        for(int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                int pom;
                file>>pom;

                if(pom==0)
                {
                    poziom[i][j].iswall=false;
                }
                else
                {
                    poziom[i][j].iswall=true;
                }
                poziom[i][j].type=pom-1;
            }
        }
    }
    file.close();
}
//create textures enemies
void Enemies::InitTextures()
{
    for(size_t i=0;i<2;i++)
    {
        if(i==0)
        {
            auto t=std::make_unique<sf::Texture>();
            t->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_robot_sheet.png");
            textures.emplace_back(std::move(t));
        }
        else
        {
            auto te=std::make_unique<sf::Texture>();
            te->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/character_zombie_sheet.png");
            textures.emplace_back(std::move(te));
        }
    }
}

void Enemies::TurnAround()
{
    for(size_t i=0;i<this->veclocities.size();i++)
    {
        this->veclocities[i].x=-std::abs(this->veclocities[i].x);
    }
}

//constructors

Enemies::Enemies()
{

}

Enemies::Enemies(std::string filename)
{
    loadfromfile(filename);
    animationframe();
    InitTextures();
    InitSprite();
    //timelimit=0.2f;
    //time=0.0f;
    //walktime=0.0f;
    //walklimittime=1.8f;
    //faceright=true;
}

//public functions

//drawing everything
void Enemies::drawing(sf::RenderTarget &target)
{
    for(size_t i=0;i<sprites.size();i++)
    {
        target.draw(*sprites[i]);
    }
}

//animation of walking
void Enemies::walkingstep(const sf::Time &elapsed,const size_t& i)
{

    sf::IntRect drect;
    time+=elapsed.asSeconds();
    if(time>=timelimit)
    {
        time-=timelimit;
    if(it<27)
    {
        drect.top=this->vector_animationframe[it].top;
        drect.height=this->vector_animationframe[it].height;
        if(this->faceright==true)
        {
            drect.width=std::abs(this->vector_animationframe[it].width);
            drect.left=this->vector_animationframe[it].left;
        }
        else
        {
            drect.width=-std::abs(this->vector_animationframe[it].width);
            drect.left=this->vector_animationframe[it+1].left;
        }
        this->sprites[i]->setTextureRect(drect);
        it++;
    }
    else
    {
        it=24;
    }
    }

}
//walking
void Enemies::moving(const sf::Time &elapsed)
{
    for(size_t i=0;i<sprites.size();i++)
    {
        this->sprites[i]->move(this->veclocities[i].x*elapsed.asSeconds(),this->veclocities[i].y*elapsed.asSeconds());
        walkingstep(elapsed,i);
    }
    walktime+=elapsed.asSeconds();
    if(walktime>=walklimittime)
    {
        TurnAround();
        walktime=0.0f;
    }
}

*/






