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
                std::string txt;
                //file>>pom;
                file>>txt;
                if(txt!="c" && txt!="ck")
                {
                   pom=std::atoi(txt.c_str());
                   poz_coin[i][j].iswall=false;
                   poz_key[i][j].iswall=false;

                }
                else if(txt=="c")
                {
                    pom=0;
                    poz_coin[i][j].iswall=true;
                    poz_coin[i][j].type=23;

                    poz_key[i][j].iswall=false;
                }
                else if(txt=="ck")
                {
                    pom=0;
                    poz_key[i][j].iswall=true;
                    poz_key[i][j].type=15;
                    poz_coin[i][j].iswall=false;
                    //keycolors.emplace_back("red");
                }
                else
                {
                    pom=std::atoi(txt.c_str());
                }



                if(pom==0)
                {
                    poziom[i][j].iswall=false;
                }
                else
                {

                    if(pom>=42 && pom <= 45)
                    {
                        position_doors.emplace_back(pom-1);
                        poziom[i][j].iswall=false;

                    }
                    else
                    {
                        poziom[i][j].iswall=true;
                    }
                }
                poziom[i][j].type=pom-1;
                txt.clear();
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

    for(int j=0;j<6;j++)
    {
        for(int i=0;i<4;i++)
        {
            auto st=std::make_unique<sf::Texture>();
            st->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/spritesheet_items.png",
                             sf::IntRect(j*tile_width,i*tile_height,tile_width,tile_height));
            st->setRepeated(true);
            this->coins_tex.emplace_back(std::move(st));
        }
    }

     std::vector<std::unique_ptr<sf::Sprite>> sp;
     std::vector<item_type> itemname;


     for(int i=0;i<height;i++)
     {
         for(int j=0;j<width;j++)
         {
             if(poziom[i][j].iswall==true && poziom[i][j].type!=80){


                if(poziom[i][j].type>=0 && poziom[i][j].type<=9){

                    item_type it;
                    it.name="pudelko";
                    it.dynamic=true;
                    it.velocity.x=0.0f;
                    it.velocity.y=0.0f;
                    it.dangerous=false;
                    itemname.emplace_back(it);

                }
                else if(poziom[i][j].type==15||poziom[i][j].type==17)
                    {
                        item_type it;
                        it.name="woda";
                        it.dynamic=false;
                        it.velocity.x=0.0f;
                        it.velocity.y=0.0f;
                        it.dangerous=true;
                        itemname.emplace_back(it);
                    }
                    else if(poziom[i][j].type==19)
                        {
                            item_type it;
                            it.name="fire";
                            it.dynamic=false;
                            it.velocity.x=0.0f;
                            it.velocity.y=0.0f;
                            it.dangerous=false;
                            itemname.emplace_back(it);
                        }
                    else{
                        item_type it;
                        it.name="nic";
                        it.dynamic=false;
                        it.velocity.x=0.0f;
                        it.velocity.y=0.0f;
                        it.dangerous=false;
                        itemname.emplace_back(it);
                    }



             auto s=std::make_unique<sf::Sprite>();
             s->setTexture(*textures[poziom[i][j].type]);
             s->setScale(0.5f,0.5f);
             s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
             if(poziom[i][j].type==19)
             {
                sf::Vector2f vec2f(j*tile_width*0.5f,i*tile_height*0.5f);
                pochodnie_pozycja.emplace_back(vec2f);
             }
             s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);

             sp.emplace_back(std::move(s));
             }
              if(poziom[i][j].type>=41 && poziom[i][j].type <=44)
              {
                  //doors.emplace_back(std::make_unique<sf::Sprite>(*textures[poziom[i][j].type]));
                  auto d=std::make_unique<sf::Sprite>();
                  d->setTexture(*textures[poziom[i][j].type]);
                  d->setScale(0.5f,0.5f);
                  d->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                  d->setOrigin(d->getGlobalBounds().width/2.0f,d->getGlobalBounds().height/2.0f);
                  doors.emplace_back(std::move(d));
                  door_colors.emplace_back(KeyColor(poziom[i][j].type-27));
              }
              //create coins

             if(this->poz_coin[i][j].iswall==true)
             {
                 auto sprit=std::make_unique<sf::Sprite>();
                 sprit->setTexture(*coins_tex[poz_coin[i][j].type]);
                 sprit->setScale(0.5f,0.5f);
                 sprit->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                 sprit->setOrigin(sprit->getGlobalBounds().width/2.0f,sprit->getGlobalBounds().height/2.0f);
                 this->coinsy.emplace_back(std::move(sprit));
             }
             //create keys

             if(this->poz_key[i][j].iswall==true)
             {
                 auto spri=std::make_unique<sf::Sprite>();
                 spri->setTexture(*coins_tex[poz_key[i][j].type]);
                 spri->setScale(0.5f,0.5f);
                 spri->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                 spri->setOrigin(spri->getGlobalBounds().width/2.0f,spri->getGlobalBounds().height/2.0f);
                 this->keys.emplace_back(std::move(spri));
                 std::pair<KeyColor,bool> p;
                 p.first=KeyColor(poz_key[i][j].type);
                 p.second=false;
                 this->iskeycollect.emplace_back(p);
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

    for(size_t a=0;a<this->coinsy.size();a++)
    {
        target.draw(*coinsy[a]);
    }
    for(size_t i=0;i<this->keys.size();i++)
    {
        target.draw(*keys[i]);
    }
    for(size_t i=0;i<doors.size();i++)
    {
        target.draw(*doors[i]);
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
//erase keys[i] and change this activity to true
void Items::Collectkeys(const size_t &i)
{
    this->keys.erase(keys.begin()+i);
    this->iskeycollect[i].second=true;
    //this->iskeycollect[i]=true;
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








