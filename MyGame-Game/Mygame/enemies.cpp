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
                s->setTextureRect(this->vector_animationframe[0]);
                s->setScale(0.5f,0.5f);
                s->setPosition(j*tile_width*0.5f,i*tile_height*0.5f);
                s->setOrigin(s->getGlobalBounds().width/2.0f,s->getGlobalBounds().height/2.0f);
                sprites.emplace_back(std::move(s));
               this->veclocities.emplace_back(20.0f);
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
//init time enemies and view direction
void Enemies::InitTime()
{
    for(size_t i=0;i<this->sprites.size();i++)
    {
        float t=0.0f;
        bool f=true;
        this->time.emplace_back(t);
        this->faceright.emplace_back(f);
    }
}
//turn around view enemies
void Enemies::TurnAround()
{
    for(size_t i=0;i<this->veclocities.size();i++)
    {
        this->veclocities[i]=-1*(this->veclocities[i]);
        if(faceright[i]==true)
        {
            faceright[i]=false;
        }
        else
        {
            faceright[i]=true;
        }
    }

}

void Enemies::CheckTurnface()
{
    for(size_t i=0;i<sprites.size();i++)
    {
        if(veclocities[i]<0.0f)
        {
            faceright[i]=false;
        }
        else
        {
            faceright[i]=true;
        }
    }

}
//create enemies lifes
void Enemies::InitLifes()
{
    for(size_t i=0;i<this->sprites.size();i++)
    {
        this->lifes.emplace_back(int(2));
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
    InitTime();
    this->it=36;
    timelimit=0.1f;
    //time=0.0f;
    walktime=0.0f;
    walklimittime=16.8f;
    //faceright=true;
    stoptime=0.0f;
    InitLifes();
}

//public functions

//drawing everything
void Enemies::drawing(sf::RenderTarget &target)
{
    if(sprites.empty()==false)
    {
    for(size_t i=0;i<sprites.size();i++)
    {
        target.draw(*sprites[i]);
    }
    }
}

//animation of walking
void Enemies::walkingstep(const sf::Time &elapsed)
{
    if(sprites.empty()==false)
    {
    this->CheckTurnface();
    for(size_t i=0;i<sprites.size();i++)
    {
    sf::IntRect drect;
    time[i]+=elapsed.asSeconds();
    if(time[i]>=timelimit)
    {
        time[i]-=timelimit;
    if(it<43)
    {
        drect.top=this->vector_animationframe[it].top;
        drect.height=this->vector_animationframe[it].height;
        if(this->faceright[i]==true)
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
        it=36;
    }
    }
    }
    }

}

//walking
void Enemies::moving(const sf::Time &elapsed)
{
    if(sprites.empty()==false)
    {

    for(size_t i=0;i<sprites.size();i++)
    {
        this->sprites[i]->move(this->veclocities[i]*elapsed.asSeconds(),0);
    }
    walkingstep(elapsed);
    walktime+=elapsed.asSeconds();
    if(walktime>=walklimittime)
    {
        TurnAround();
        walktime-=walklimittime;
    }
    }

}
//collision with items events
void Enemies::OnCollision(const sf::Vector2f &direction,const size_t& i)
{
    if(direction.x <0.0f)
    {
        //Collision on the left
        this->veclocities[i]=-1*std::abs(this->veclocities[i]);

    }
    else if(direction.x >0.0f)
    {
        //Collision on the rigth
       this->veclocities[i]=std::abs(this->veclocities[i]);
    }
/*
    if(direction.y < 0.0f)
    {
        //Collision on the bottom

    }
    else if(direction.y >0.0f)
    {
        //Collision on the top

    }
*/
}
//erase one enemies with it iterator
void Enemies::Dead(const size_t& i)
{
     sf::IntRect drect;
     drect.top=this->vector_animationframe[4].top;
     drect.height=this->vector_animationframe[4].height;
     if(this->faceright[i]==true)
     {
         drect.width=std::abs(this->vector_animationframe[4].width);
         drect.left=this->vector_animationframe[4].left;
     }
     else
     {
         drect.width=-std::abs(this->vector_animationframe[4].width);
         drect.left=this->vector_animationframe[4+1].left;
     }
     this->sprites[i]->setTextureRect(drect);

     this->sprites.erase(sprites.begin()+i);
}


