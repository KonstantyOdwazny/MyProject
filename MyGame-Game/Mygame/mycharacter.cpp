#include "mycharacter.h"

//private functions
void MyCharacter::InitTexture(std::string filename)
{
    if(!texture.loadFromFile(filename)){
        std::cout<<"Blad otwarcia pliku"<<std::endl;
    }
    this->texture.setRepeated(true);
}

void MyCharacter::animation_frame()
{
    sf::Vector2u v=this->texture.getSize();
    v.x/=9;
    v.y/=5;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            this->vector_animationframe.emplace_back(sf::IntRect(j*v.x,i*v.y,v.x,v.y));
        }
    }
}

void MyCharacter::InitSprite(sf::IntRect r)
{
    this->setTexture(this->texture);
    this->setTextureRect(r);
    this->setScale(0.50f,0.50f);
    this->setOrigin(64.0f,64.0f);
    //this->setPosition(100.0f*0.4f,300.0f*0.4f);
}

void MyCharacter::render(sf::RenderTarget &window)
{
    window.draw(*this);
}

void MyCharacter::setposition(float x_,float y_)
{
    this->setPosition(x_,y_);
    this->x=x_;
    this->y=y_;
}

void MyCharacter::runstep(const sf::Time& elapsed)
{
    time+=elapsed.asSeconds();
    if(time>=timelimit)
    {
        time-=timelimit;
    if(it<27)
    {
        this->setTextureRect(this->vector_animationframe[it]);
        it++;
    }
    else
    {
        it=24;
    }
    }

}

void MyCharacter::jumpstep()
{
    if(jump_it<4)
    {
        this->setTextureRect(this->vector_animationframe[jump_it]);
        jump_it++;
    }
    else
    {
        jump_it=1;
    }
}

void MyCharacter::stop()
{
    this->setTextureRect(this->vector_animationframe[0]);
}

void MyCharacter::moving(const sf::Time& elapsed)
{
    //std::cout<<1/elapsed.asSeconds()<<std::endl;
    //if(this->run==true||this->jump==true){
    this->move(this->vx*elapsed.asSeconds()+ax*elapsed.asSeconds(),this->vy*elapsed.asSeconds()+ay*elapsed.asSeconds());
   // }
}

bool MyCharacter::colission(const std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& sp)
{
    for(size_t i=0;i<sp.size();i++)
    {
        for(size_t j=0;j<sp[i].size();j++)
        {
            if((this->getGlobalBounds().intersects(sp[i][j]->getGlobalBounds()))&&(this->vy<=0)){
                this->is_colission=true;
                return true;
            }
            else if(!(this->getGlobalBounds().intersects(sp[i][j]->getGlobalBounds())))
            {
                this->is_colission=false;
            }
        }
    }
    return false;
}

void MyCharacter::Oncollision(sf::Vector2f direction)
{
    if(direction.x <0.0f)
    {
        //Collision on the left
        vx=0.0f;
    }
    else if(direction.x >0.0f)
    {
        //Collision on the rigth
        vx=0.0f;
    }

    if(direction.y < 0.0f)
    {
        //Collision on the bottom
        vy=0.0f;
        canjump=true;
    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        vy=0.0f;
    }
}




