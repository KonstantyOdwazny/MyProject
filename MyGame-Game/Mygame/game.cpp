#include "game.h"
//constructor
Game::Game()
{
    this->window=new sf::RenderWindow(sf::VideoMode(800,600),"My Game");
    this->level=new MapGame("map.level");
    hero=new MyCharacter;
    this->hero->InitTexture("Spritesheets/spritesheet_players.png");
    this->hero->animation_frame();
    this->hero->InitSprite(this->hero->vector_animationframe[0]);
    this->hero->setposition(100.0f,300.0f);
}
//destructor
Game::~Game()
{
    delete this->window;
    delete  this->level;
    delete this->hero;
}
//functions
void Game::pollevent()
{
    while(this->window->pollEvent(this->ev))
    {
        if(this->ev.type==sf::Event::Closed || this->ev.key.code==sf::Keyboard::Escape)
        {
            this->window->close();
        }
    }
}
void Game::update()
{
    level->getposition(10);
}
void Game::render()
{
    window->clear(sf::Color::Black);
    //draw game object
    level->drawing(*window);
    this->hero->render(*window);
    this->window->display();
}

bool Game::running()
{
    return this->window->isOpen();
}

