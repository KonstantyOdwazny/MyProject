#include "collision.h"

Collision::Collision(sf::Sprite& body) : body(body)
{

}

bool Collision::Checkcollision(Collision &other, float p)
{
    sf::Vector2f otherposition=other.Getposition();
    sf::Vector2f otherhalfsize=other.Gethalfsize();
    sf::Vector2f thisposition=this->Getposition();
    sf::Vector2f thishalfsize=this->Gethalfsize();

    float deltax=otherposition.x-thisposition.x;
    float deltay=otherposition.y-thisposition.y;

    float intersectX=std::abs(deltax)-(otherhalfsize.x+thishalfsize.x);
    float intersectY=std::abs(deltay)-(otherhalfsize.y+thishalfsize.y);

     if(intersectX<0.0f&&intersectY<0.0f)
     {
         p=std::min(std::max(p,0.0f),1.0f);

         if(intersectX > intersectY)
         {
             if(deltax > 0.0f)
             {
                 Move(intersectX*(1.0f-p),0.0f);
                 other.Move(-intersectX*p,0.0f);
             }
             else
            {
             Move(-intersectX*(1.0f-p),0.0f);
             other.Move(intersectX*p,0.0f);
            }
         }
         else
         {
             if(deltay > 0.0f)
             {
                 Move(0.0f,intersectY*(1.0f-p));
                 other.Move(0.0f,-intersectY*p);
             }
             else
            {
             Move(0.0f,-intersectY*(1.0f-p));
             other.Move(0.0f,intersectY*p);
            }
         }
         return true;
     }
     return false;
}

sf::Vector2f Collision::Gethalfsize()
{
    sf::Vector2f v;
    v.x=float(body.getGlobalBounds().width)/2.0f;
    v.y=float(body.getGlobalBounds().height)/2.0f;
    return v;
}
