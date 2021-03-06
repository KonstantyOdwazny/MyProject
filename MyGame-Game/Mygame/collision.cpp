#include "collision.h"
#include <windows.h>
Collision::Collision()
{

}

void Collision::CheckCollisions(std::vector<std::unique_ptr<sf::Sprite> > &sprites, MyCharacter &hero, sf::Vector2f direction, float p,sf::Time& elapsed)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x wroga
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y wroga
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem


        for(size_t i=0;i<sprites.size();i++)
        //for(auto it=enemies->sprites.begin();it!=enemies->sprites.end();it++)
        {
            //size_t i=std::distance(enemies->sprites.begin(),it);
            sf::Vector2f thisposition=sprites[i]->getPosition(); //pozycja przedmiotu
            sf::Vector2f otherposition=hero.getPosition(); //pozycja aktualna bohatera
            sf::Vector2f thishalfsize(sprites[i]->getGlobalBounds().width/2.0f,sprites[i]->getGlobalBounds().height/2.0f);
            sf::Vector2f otherhalfsize(hero.getGlobalBounds().width/2.0f,hero.getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         sprites[i]->move(intersectX,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                         hero.move(-0.0f,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     sprites[i]->move(-intersectX,0.0f);
                     hero.move(0.0f,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         sprites[i]->move(0.0f,0.0f);
                         hero.move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     sprites[i]->move(0.0f,0.0f);
                     hero.move(0.0f,intersectY*p);

                     //this->enemies->Dead(i);
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
                 hero.dead_sound.play();
                 hero.OnEnemiesCollision(direction,elapsed);
             }

        }
}
//hero with map collision
void Collision::CheckCollisions(std::vector<std::vector<std::unique_ptr<sf::Sprite> > > &v, MyCharacter &s, sf::Vector2f& direction, float p)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem

    //sprawdzamy kolizje naszego bohatera z kazdym obiektem na naszej mapie
    for(size_t i=0;i<v.size();i++)
    {
        for(size_t j=0;j<v[i].size();j++)
        {


            sf::Vector2f thisposition=v[i][j]->getPosition(); //pozycja bohatera
            sf::Vector2f otherposition=s.getPosition(); //pozycja aktualnego obiektu
            sf::Vector2f thishalfsize(v[i][j]->getGlobalBounds().width/2.0f,v[i][j]->getGlobalBounds().height/2.0f);
            sf::Vector2f otherhalfsize(s.getGlobalBounds().width/2.0f,s.getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         v[i][j]->move(intersectX*(1.0f-p),0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                         s.move(-intersectX*p,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     v[i][j]->move(-intersectX*(1.0f-p),0.0f);
                     s.move(intersectX*p,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         v[i][j]->move(0.0f,intersectY*(1.0f-p));
                         s.move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     v[i][j]->move(0.0f,-intersectY*(1.0f-p));
                     s.move(0.0f,intersectY*p);

                     direction.x=0.0f;
                     direction.y=-1.0f;
                    }
                 }
                 //return true;
                 t=true;

             }
             else{
                 t=false;
             }
             if(t==true)
             {
                 s.Oncollision(direction);
             }

        }

    }
}
//hero with items collisions
void Collision::CheckCollisions(Items &things, MyCharacter &hero, sf::Vector2f &direction, float p,sf::Time& elapsed)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem

    for(size_t i=0;i<things.items.size();i++)
    {
        for(size_t j=0;j<things.items[i].size();j++)
        {
            sf::Vector2f thisposition=things.items[i][j]->getPosition(); //pozycja przedmiotu
            sf::Vector2f otherposition=hero.getPosition(); //pozycja aktualna bohatera
            sf::Vector2f thishalfsize(things.items[i][j]->getGlobalBounds().width/2.0f,things.items[i][j]->getGlobalBounds().height/2.0f);
            sf::Vector2f otherhalfsize(hero.getGlobalBounds().width/2.0f,hero.getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(things.typeofitem[i][j].dynamic==true){

             if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
             {
                 p=std::min(std::max(p,0.0f),1.0f);

                 if(intersectX > intersectY)
                 {
                     if(deltax > 0.0f)
                     {
                         things.items[i][j]->move(intersectX,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                         hero.move(-0.0f,0.0f);

                         direction.x=1.0f;
                         direction.y=0.0f;
                     }
                     else
                    {
                     things.items[i][j]->move(-intersectX,0.0f);
                     hero.move(0.0f,0.0f);

                     direction.x=-1.0f;
                     direction.y=0.0f;
                    }
                 }
                 else
                 {
                     if(deltay > 0.0f)
                     {
                         things.items[i][j]->move(0.0f,intersectY*(1.0f-p));
                         hero.move(0.0f,-intersectY*p);

                         direction.x=0.0f;
                         direction.y=1.0f;
                     }
                     else
                    {
                     things.items[i][j]->move(0.0f,-intersectY*(1.0f-p));
                     hero.move(0.0f,intersectY*p);


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
                 hero.OnitemCollision(direction);
             }
           }
           else
            {
                if((things.typeofitem[i][j].dangerous==true)&&(hero.getGlobalBounds().intersects(things.items[i][j]->getGlobalBounds()))){
                    hero.vy=0.0f;
                    hero.life--;
                    hero.dead_sound.play();
                    hero.Deadstep(elapsed);
                    Sleep(1000);
                    hero.setPosition(hero.start_position);
                 }
            }
        }
    }
}
//enemies with items collision
void Collision::CheckCollisions(std::vector<std::vector<std::unique_ptr<sf::Sprite> > > &sprites, Items &things, sf::Vector2f &direction, float p)
{
    for(size_t i=0;i<sprites.size();i++)
    {
        for(size_t j=0;j<sprites[i].size();j++)
        {

            for(size_t a=0;a<things.items.size();a++){
                for(size_t b=0;b<things.items[a].size();b++)
                {
                    if(things.typeofitem[a][b].dynamic==true){
                    sf::Vector2f thisposition=sprites[i][j]->getPosition();
                    sf::Vector2f thishalfsize(sprites[i][j]->getGlobalBounds().width/2.0f,sprites[i][j]->getGlobalBounds().height/2.0f);
                    sf::Vector2f otherposition=things.items[a][b]->getPosition();
                    sf::Vector2f otherhalfsize(things.items[a][b]->getGlobalBounds().width/2.0f,things.items[a][b]->getGlobalBounds().height/2.0f);
                    bool t;

                    float deltax; //zmienna odleglosc miedzy pozycja x przedmiotu i pozycja x innych obiektow
                    float deltay; //zmienna odleglosc miedzy pozycja y przedmiotu i pozycja y innych obiektow
                    float intersectX; //przeciecie w osi X obiektu z przedmiotem
                    float intersectY; //przeciecie w osi Y obiektu z przedmiotem

                     deltax=otherposition.x-thisposition.x;
                     deltay=otherposition.y-thisposition.y;

                     intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
                     intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

                     if(intersectX<1.0f && intersectY<1.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
                     {
                         p=std::min(std::max(p,0.0f),1.0f);

                         if(intersectX > intersectY)
                         {
                             if(deltax > 0.0f)
                             {
                                 sprites[i][j]->move(intersectX*(1.0f-p),0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                                 things.items[a][b]->move(-intersectX*p,0.0f);

                                 direction.x=1.0f;
                                 direction.y=0.0f;
                             }
                             else
                            {
                             sprites[i][j]->move(-intersectX*(1.0f-p),0.0f);
                             things.items[a][b]->move(intersectX*p,0.0f);

                             direction.x=-1.0f;
                             direction.y=0.0f;
                            }
                         }
                         else
                         {
                             if(deltay > 0.0f)
                             {
                                 sprites[i][j]->move(0.0f,intersectY*(1.0f-p));
                                 things.items[a][b]->move(0.0f,-intersectY*p);

                                 direction.x=0.0f;
                                 direction.y=1.0f;
                             }
                             else
                            {
                             sprites[i][j]->move(0.0f,-intersectY*(1.0f-p));
                             things.items[a][b]->move(0.0f,intersectY*p);

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

                        things.Collision_events(direction,a,b);
                    }
                    }
                }
            }
        }
    }
}
//enemy with items collision
void Collision::CheckCollisions(Enemies &enemies, Items &things, sf::Vector2f &direction)
{
    float deltax; //zmienna odleglosc miedzy pozycja x bohatera i pozycja x innych obiektow
    float deltay; //zmienna odleglosc miedzy pozycja y bohatera i pozycja y innych obiektow
    float intersectX; //przeciecie w osi X obiektu z bohaterem
    float intersectY; //przeciecie w osi Y obiektu z bohaterem

    for(size_t i=0;i<things.items.size();i++)
    {
        for(size_t j=0;j<things.items[i].size();j++)
        {
            for(size_t a=0;a<enemies.sprites.size();a++)
            {
            sf::Vector2f thisposition=things.items[i][j]->getPosition(); //pozycja przedmiotu
            sf::Vector2f otherposition=enemies.sprites[a]->getPosition(); //pozycja aktualna bohatera
            sf::Vector2f thishalfsize(things.items[i][j]->getGlobalBounds().width/2.0f,things.items[i][j]->getGlobalBounds().height/2.0f);
            sf::Vector2f otherhalfsize(enemies.sprites[a]->getGlobalBounds().width/2.0f,enemies.sprites[a]->getGlobalBounds().height/2.0f);
            bool t;

             deltax=otherposition.x-thisposition.x;
             deltay=otherposition.y-thisposition.y;

             intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
             intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

             if(things.typeofitem[i][j].dynamic==true){

                 if(intersectX<0.0f && intersectY<0.0f) //jesli obie osie przeciecia obiektu sa mniejsze od 0 to znaczy ze obiekty na siebie nachodza i nastepuje zderzenie
                 {
                     //p=std::min(std::max(p,0.0f),1.0f);

                     if(intersectX > intersectY)
                     {
                         if(deltax > 0.0f)
                         {
                             things.items[i][j]->move(0.0f,0.0f); //odbicia podczas zderzen kazdy w innym kierunku
                             enemies.sprites[a]->move(-intersectX,0.0f);

                             direction.x=1.0f;
                             direction.y=0.0f;
                         }
                         else
                        {
                         things.items[i][j]->move(0.0f,0.0f);
                         enemies.sprites[a]->move(intersectX,0.0f);

                         direction.x=-1.0f;
                         direction.y=0.0f;
                        }
                     }
                     else
                     {
                         if(deltay > 0.0f)
                         {
                             things.items[i][j]->move(0.0f,0.0f);
                             enemies.sprites[a]->move(0.0f,0.0f);

                             direction.x=0.0f;
                             direction.y=1.0f;
                         }
                         else
                        {
                         things.items[i][j]->move(0.0f,0.0f);
                         enemies.sprites[a]->move(0.0f,0.0f);


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
                     enemies.OnCollision(a,direction);
                 }

             }
            }
        }
    }
}


//collison weapons with enemies
void Collision::WeaponHit(Weapons &weapon, Enemies &enemy)
{
    for(size_t i=0;i<enemy.sprites.size();i++)
    {
        if(enemy.sprites[i]->getGlobalBounds().intersects(weapon.getGlobalBounds()))
        {
            enemy.enemies_statistic[i].lives-=weapon.damage;
            if(weapon.getScale().x<=0.0f)
            {
                enemy.sprites[i]->move(-20.0f,0.0f);
            }
            else
            {
                enemy.sprites[i]->move(20.0f,0.0f);
            }
            if(enemy.enemies_statistic[i].lives<=0.0f)
            {
                enemy.Dead(i);
            }
            break;
        }
    }
}

void Collision::WinCollision(MyCharacter &hero, Items &things)
{
    for(size_t i=0;i<things.items.size();i++)
    {
        for(size_t j=0;j<things.items[i].size();j++)
        {
            if(things.typeofitem[i][j].name=="win")
            {
            if(things.items[i][j]->getGlobalBounds().intersects(hero.getGlobalBounds()))
            {
                hero.win=true;
            }
            }
        }
    }
}
//bullets collision events and destroy
void Collision::BulletsCollision(std::vector<RobotsBullet*>& bullets, Items &things, MyCharacter &hero,std::vector<std::vector<std::unique_ptr<sf::Sprite>>>& map,sf::Time& elapsed)
{
    if(bullets.empty()==false)
    {
    for(size_t a=0;a<bullets.size();a++)
    {
        for(size_t i=0;i<things.items.size();i++)
        {
            for(size_t j=0;j<things.items[i].size();j++)
            {
                if(things.typeofitem[i][j].dynamic==true)
                {
                    if(bullets.empty()==false)
                    {
                    if(bullets[a]->getGlobalBounds().intersects(things.items[i][j]->getGlobalBounds()))
                    {
                        //bullets.clear();
                        bullets.erase(bullets.begin()+a);
                        break;
                    }
                    }
                }

            }
            if(bullets.empty())
            {
                break;
            }

        }

    if(hero.getGlobalBounds().intersects(bullets[a]->getGlobalBounds()))
    {
        //bullets.clear();
        bullets.erase(bullets.begin()+a);
        hero.vy=0.0f;
        hero.life--;
        hero.dead_sound.play();
        hero.Deadstep(elapsed);
        break;
    }

    for(size_t i=0;i<map.size();i++)
    {
        for(size_t j=0;j<map[i].size();j++)
        {
            if(bullets[a]->getGlobalBounds().intersects(map[i][j]->getGlobalBounds()))
            {
                //bullets.clear();
                bullets.erase(bullets.begin()+a);
            }
        }
    }
    if(bullets.empty())
    {
        break;
    }
    }
    }



}
