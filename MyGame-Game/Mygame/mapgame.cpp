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
            s->setScale(0.25f,0.25f);
            s->setPosition(j*tile_width*0.25f,i*tile_height*0.25f);
            s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f); //*
            sp.emplace_back(std::move(s));
            auto b=std::make_unique<bounds>();
            b->top=i*tile_height*0.25f;
            b->left=j*tile_width*0.25f;
            b->width=128.0f*0.25f;
            b->height=128.0f*0.25f;
            this->bounds_vector.emplace_back(std::move(*b));
            }
        }
        this->sprites.emplace_back(std::move(sp));
        sp.clear();
    }
}

//draw all elements of the map
void MapGame::drawing(sf::RenderTarget &target)
{
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {
            target.draw(*sprites[i][j]);
        }
    }
}

void MapGame::getposition(size_t it)
{
    std::cout<<bounds_vector[it].left<<" "<<bounds_vector[it].top<<std::endl;
    /*
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {
            std::cout<<sprites[i][j]->getGlobalBounds().left<<std::endl;
        }
    }
    */
}
//check the collision with other sprite and return true or false

bool MapGame::CheckCollision(sf::Sprite &other,sf::Vector2f& direction ,float p)
{
    sf::Vector2f otherposition=other.getPosition();
    sf::Vector2f otherhalfsize;
    otherhalfsize.x=other.getGlobalBounds().width/2.0f;
    otherhalfsize.y=other.getGlobalBounds().height/2.0f;
    //sf::Vector2f thisposition;

    std::vector<sf::Vector2f> thispositions;
    std::vector<sf::Vector2f> thishalfsizes;
    float deltax;
    float deltay;
    float intersectX;
    float intersectY;

    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {
            sf::Vector2f thisposition=this->sprites[i][j]->getPosition();
            sf::Vector2f thishalfsize(this->sprites[i][j]->getGlobalBounds().width/2.0f,this->sprites[i][j]->getGlobalBounds().height/2.0f);
            //thishalfsize.x=this->sprites[i][j]->getGlobalBounds().width/2.0f;
            //thishalfsize.y=this->sprites[i][j]->getGlobalBounds().height/2.0f;
            thispositions.emplace_back(thisposition);
            thishalfsizes.emplace_back(thishalfsize);
        }
    }

    //musze sprawdzic dla kazdego z osobna
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {


            //thisposition=this->sprites[i][j]->getPosition();
            //thishalfsize.x=this->sprites[i][j]->getGlobalBounds().width/2.0f;
            //thishalfsize.y=this->sprites[i][j]->getGlobalBounds().height/2.0f;

             deltax=otherposition.x-thispositions[i+j].x;
             deltay=otherposition.y-thispositions[i+j].y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsizes[i+j].x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsizes[i+j].y);

             if(intersectX<0.0f && intersectY<0.0f)
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         this->sprites[i][j]->move(intersectX*(1.0f-p),0.0f);
                         other.move(-intersectX*p,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     this->sprites[i][j]->move(-intersectX*(1.0f-p),0.0f);
                     other.move(intersectX*p,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         this->sprites[i][j]->move(0.0f,intersectY*(1.0f-p));
                         other.move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     this->sprites[i][j]->move(0.0f,-intersectY*(1.0f-p));
                     other.move(0.0f,intersectY*p);

                     direction.x=0.0f;
                     direction.y=-1.0f;
                    }
                 }
                 return true;
             }

        }

    }
    return false;
}

/*
std::vector<Collision> MapGame::GetColissions()
{
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {
            auto c=std::make_unique<Collision>();

        }
    }
}
*/
//funkcja do sprawdzania kolizji
/*
std::vector<std::vector<Collision>> MapGame::GetColider()
{
    std::vector<Collision> v;
    for(size_t i=0;i<this->sprites.size();i++)
    {
        for(size_t j=0;j<this->sprites[i].size();j++)
        {

        }
    }
}
*/
