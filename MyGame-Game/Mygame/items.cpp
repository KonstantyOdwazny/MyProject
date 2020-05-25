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

     for(int i=0;i<height;i++)
     {
         for(int j=0;j<width;j++)
         {
             if(poziom[i][j].iswall==true){

             auto s=std::make_unique<sf::Sprite>();
             s->setTexture(*textures[poziom[i][j].type]);
             s->setScale(0.5f,0.5f);
             s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
             s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);

             sp.emplace_back(std::move(s));
             }
         }
         this->items.emplace_back(std::move(sp));
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
