#include "mapgame.h"
#include <string>
#include <fstream>
#include <iostream>

/*
 * cpp fail of our map
 * create textures and sprites
 * drawing elements
*/


//constructor and destructor
MapGame::MapGame()
{

}

MapGame::MapGame(std::string filename)
{
    this->loadfromfile(filename);
    this->createSprite();
}

MapGame::~MapGame()
{

}
//public functions

//load texture from the file
void MapGame::loadfromfile(std::string filename)
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
//create our sprites and get them to the containers
void MapGame::createSprite()
{

    for(int j=0;j<7;j++)
    {
    for(int i=0;i<16;i++){

        auto t=std::make_unique<sf::Texture>();
        t->loadFromFile("Spritesheets/spritesheet_ground.png",sf::IntRect(j*tile_width,i*tile_height,tile_width,tile_height));
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

                pom.x=j*tile_width*0.5f-155.0f;
                pom.y=i*tile_height*0.5f-255.0f;
                //std::cout<<pom.x<<"    "<<pom.y<<std::endl;

            s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);
            //std::cout<<s->getGlobalBounds().width/2.0f<<"  "<<s->getGlobalBounds().height/2.0f<<std::endl;

            sp.emplace_back(std::move(s));
            }
        }
        this->sprites.emplace_back(std::move(sp));
        sp.clear();
    }

    //backgrounds

    tex=new sf::Texture;
    tex->loadFromFile("C:/Users/konst/Desktop/MyGame-Game/MyProject/MyGame-Game/build-Mygame-Desktop_Qt_5_14_1_MinGW_64_bit-Debug/Spritesheets/bg_castle.png");
    tex->setRepeated(true);
    this->backgrounds=new sf::Sprite;
    this->backgrounds->setTexture(*tex);
    //this->backgrounds->setTextureRect(sf::IntRect(0,0,1000,1000));
    this->backgrounds->setScale(3.0f,3.0f);
    this->backgrounds->setPosition(0.0f,0.0f);
}

//draw all elements of the map
void MapGame::drawing(sf::RenderTarget &target)
{
    //target.draw(*this->backgrounds);
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {
            target.draw(*sprites[i][j]);
        }
    }

}






