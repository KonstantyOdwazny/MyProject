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
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            this->vector_animationframe.emplace_back(sf::IntRect(j*95,i*130,95,130));
        }
    }
}

void MyCharacter::InitSprite(sf::IntRect r)
{
    this->setTexture(this->texture);
    this->setTextureRect(r);
    this->setScale(0.50f,0.50f);
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

void MyCharacter::runstep()
{
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
    if(this->run==true||this->jump==true){
    this->move(this->vx*elapsed.asSeconds()+ax*elapsed.asSeconds(),this->vy*elapsed.asSeconds()+ay*elapsed.asSeconds());
    }
}
