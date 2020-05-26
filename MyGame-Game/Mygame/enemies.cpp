#include "enemies.h"
#include <string>
#include <fstream>


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
                s->setScale(0.5f,0.5f);
                s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);
                sprites.emplace_back(std::move(s));
            }
        }
    }
}

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

void Enemies::InitTextures()
{
    for(size_t i=0;i<2;i++)
    {
        if(i==0)
        {
            auto t=std::make_unique<sf::Texture>();
            t->loadFromFile("Spritesheets/character_robot_sheet.png");
            textures.emplace_back(std::move(t));
        }
        else
        {
            auto te=std::make_unique<sf::Texture>();
            te->loadFromFile("Spritesheets/character_zombie_sheet.png");
            textures.emplace_back(std::move(te));
        }
    }
}
//constructors
Enemies::Enemies()
{

}

Enemies::Enemies(std::string filename)
{
    loadfromfile(filename);
    InitTextures();
}
