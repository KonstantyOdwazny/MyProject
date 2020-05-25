#include "items.h"
#include <string>
#include <fstream>
#include <iostream>


//private functions
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
         this->typeofitem[i][j].velocity.y=0.0f;
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
