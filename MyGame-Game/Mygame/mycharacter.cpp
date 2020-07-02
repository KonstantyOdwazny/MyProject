#include "mycharacter.h"
#include <windows.h>
#include <cmath>

//private functions
void MyCharacter::InitTexture(std::string filename)
{
    if(!texture.loadFromFile(filename)){
        std::cout<<"Blad otwarcia pliku"<<std::endl;
    }
    this->texture.setRepeated(true);
}
//constructor
MyCharacter::MyCharacter() : sf::Sprite(){
    vx=0;
    vy=0;
    ax=0;
    ay=0;
    x=0;
    y=0;
    run=false;
    it=24;
    jump_it=1;
    jump=false;
    is_colission=true;
    timelimit=0.2f;
    time=0.0f;
    jumpHeight=200.0f;
    stay_it=21;
    facerigth=true;
    //canjump =true;
    life=3;
    coins=0;
    begin_stop=0;
    stop_time=0.0f;
    jump_time=0.0f;
    hit_it=11;
    //this->weapon=new Weapons(10.0f,"kilof",44);
    this->weapon=CreateWeapons(10,"kilof",6);
    this->weapon->setPosition(250.0f,260.0f);
}
//create a vector of animation frame
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
//create a Sprite hero
void MyCharacter::InitSprite(sf::IntRect r)
{
    this->setTexture(this->texture);
    this->setTextureRect(r);
    this->setScale(0.50f,0.50f);
    //this->setOrigin(64.0f,64.0f);
    this->setOrigin(this->getGlobalBounds().width/2.0f,this->getGlobalBounds().height/2.0f);
    //this->setPosition(100.0f*0.4f,300.0f*0.4f);
}
//draw hero
void MyCharacter::render(sf::RenderTarget &window)
{
    window.draw(*this->weapon);
    window.draw(*this);
}
//set the hero position
void MyCharacter::setposition(float x_,float y_)
{
    this->setPosition(x_,y_);
    this->x=x_;
    this->y=y_;
}
//animation of running hero
void MyCharacter::runstep(const sf::Time& elapsed)
{
    if(this->run==true && jump==false)
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
        if(facerigth)
        {
            drect.width=std::abs(this->vector_animationframe[it].width);
            drect.left=this->vector_animationframe[it].left;
        }
        else
        {
            drect.width=-std::abs(this->vector_animationframe[it].width);
            drect.left=this->vector_animationframe[it+1].left;
        }
        this->setTextureRect(drect);
        it++;
    }
    else
    {
        it=24;
    }
    }
    }

}
//animmation of jumping hero
void MyCharacter::jumpstep(const sf::Time& elapsed)
{
    sf::IntRect drect;
    if(jump==true){
        time+=elapsed.asSeconds();
        if(time>=timelimit && time<=1.9f*timelimit)
        {
            jump_it=1;
            drect.top=this->vector_animationframe[jump_it].top;
            drect.height=this->vector_animationframe[jump_it].height;
            if(facerigth)
            {
                drect.width=std::abs(this->vector_animationframe[jump_it].width);
                drect.left=this->vector_animationframe[jump_it].left;
            }
            else
            {
                drect.width=-std::abs(this->vector_animationframe[jump_it].width);
                drect.left=this->vector_animationframe[jump_it+1].left;
            }
            //jump_it++;
            this->setTextureRect(drect);
        }else if(time>=1.9f*timelimit && time<=2.5f*timelimit)
        {
            jump_it=2;
            drect.top=this->vector_animationframe[jump_it].top;
            drect.height=this->vector_animationframe[jump_it].height;
            if(facerigth)
            {
                drect.width=std::abs(this->vector_animationframe[jump_it].width);
                drect.left=this->vector_animationframe[jump_it].left;
            }
            else
            {
                drect.width=-std::abs(this->vector_animationframe[jump_it].width);
                drect.left=this->vector_animationframe[jump_it+1].left;
            }
            //jump_it++;
            this->setTextureRect(drect);

        }

   }


}
//animation when hero stay
void MyCharacter::stop(const sf::Time& elapsed)
{
    if(this->begin_stop==0)
    {
    this->setTextureRect(this->vector_animationframe[21]);
        begin_stop++;
    }

    time+=elapsed.asSeconds();
    if(time>=2.0f*timelimit)
    {
        time-=2.0f*timelimit;
    if(stay_it<24){
        this->setTextureRect(this->vector_animationframe[stay_it]);
        stay_it++;
    }
    else
    {
        stay_it=21;
    }
    }


}
//move
void MyCharacter::moving(const sf::Time& elapsed)
{
    //std::cout<<1/elapsed.asSeconds()<<std::endl;
    //if(this->run==true||this->jump==true){
    this->move(this->vx*elapsed.asSeconds()+ax*elapsed.asSeconds(),this->vy*elapsed.asSeconds()+ay*elapsed.asSeconds());

    //this->weapon->setPosition(this->getPosition());
    //}
}
//dead animation frame
void MyCharacter::Deadstep()
{
    sf::IntRect drect;

        drect.top=this->vector_animationframe[4].top;
        drect.height=this->vector_animationframe[4].height;
        if(facerigth)
        {
            drect.width=std::abs(this->vector_animationframe[4].width);
            drect.left=this->vector_animationframe[4].left;
        }
        else
        {
            drect.width=-std::abs(this->vector_animationframe[4].width);
            drect.left=this->vector_animationframe[4+1].left;
        }
            this->setTextureRect(drect);

}
//animation when hero hit something/somebody
void MyCharacter::HitAnimation(const sf::Time& elapsed)
{
    sf::IntRect drect;
    time+=elapsed.asSeconds();

    if(time>=timelimit)
    {
        time-=timelimit;

    if(this->hit_it<14)
    {
    drect.top=this->vector_animationframe[hit_it].top;
    drect.height=this->vector_animationframe[hit_it].height;
    if(facerigth)
    {
        drect.width=std::abs(this->vector_animationframe[hit_it].width);
        drect.left=this->vector_animationframe[hit_it].left;
        this->weapon->setScale(0.3f,0.3f);
        if(hit_it==11)
        {
            this->weapon->setPosition(this->getPosition().x+28.0f,this->getPosition().y-20.0f);
        }
        else if(hit_it==12)
        {
            this->weapon->setPosition(this->getPosition().x+28.0f,this->getPosition().y);
        }
        else if(hit_it==13)
        {
            this->weapon->setPosition(this->getPosition().x+28.0f,this->getPosition().y+20.0f);
        }

    }
    else
    {
        drect.width=-std::abs(this->vector_animationframe[hit_it].width);
        drect.left=this->vector_animationframe[hit_it+1].left;
       this->weapon->setScale(-0.3f,0.3f);
        if(hit_it==11)
        {
            this->weapon->setPosition(this->getPosition().x-5.0f,this->getPosition().y-20.0f);
        }
        else if(hit_it==12)
        {
            this->weapon->setPosition(this->getPosition().x-5.0f,this->getPosition().y);
        }
        else if(hit_it==13)
        {
            this->weapon->setPosition(this->getPosition().x-5.0f,this->getPosition().y+20.0f);
        }

    }
    this->setTextureRect(drect);

    hit_it++;
    }
    else
    {
    hit_it=11;

    }
    }
}

void MyCharacter::KickAnimation()
{
    sf::IntRect drect;

    drect.top=this->vector_animationframe[14].top;
    drect.height=this->vector_animationframe[14].height;
    if(facerigth)
    {
        drect.width=std::abs(this->vector_animationframe[14].width);
        drect.left=this->vector_animationframe[14].left;
    }
    else
    {
        drect.width=-std::abs(this->vector_animationframe[14].width);
        drect.left=this->vector_animationframe[14+1].left;
    }
    this->setTextureRect(drect);
}


//funkcja do sprawdzania z ktorej strony obiektu nastepuje kolizja gracza z obiektem
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
        jump=false;
    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        vy=0.0f;
    }
}
//funkcja ktora wywoluje zdarzenia podczas kolizji z przedmiotem
void MyCharacter::OnitemCollision(sf::Vector2f &direction)
{
    if(direction.y < 0.0f)
    {
        //Collision on the bottom
        vy=0.0f;
        canjump=true;
        jump=false;
    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        vy=0.0f;
    }
}
//special box collision
void MyCharacter::OnSpecialBoxCollision(sf::Vector2f &direction)
{
    if(direction.y < 0.0f)
    {
        //Collision on the bottom
        this->vy=-sqrtf(2.0f*981.0f*this->jumpHeight); //float square root
    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        vy=0.0f;
    }
}
//collision with enemies events
void MyCharacter::OnEnemiesCollision(sf::Vector2f &direction)
{
    if(direction.x <0.0f)
    {
        //Collision on the left
        vx=0.0f;
        life--;
        this->Deadstep();
        Sleep(1000);
        this->setPosition(this->start_position);
    }
    else if(direction.x >0.0f)
    {
        //Collision on the rigth
        vx=0.0f;
        life--;
        this->Deadstep();
        Sleep(1000);
        this->setPosition(this->start_position);
    }
    if(direction.y < 0.0f)
    {
        //Collision on the bottom
        //this->vy=-sqrtf(2.0f*981.0f*this->jumpHeight); //float square root
        vy=0.0f;
        life--;
        this->Deadstep();
        Sleep(1000);
        this->setPosition(this->start_position);
    }
    else if(direction.y >0.0f)
    {
        //Collision on the top
        vy=0.0f;
        life--;
        this->Deadstep();
        Sleep(1000);
        this->setPosition(this->start_position);
    }
}
//function when we create and equip new weapons
Weapons *MyCharacter::CreateWeapons(float damage_, std::string name_, size_t it_)
{
    return new Weapons(damage_,name_,it_);
}




