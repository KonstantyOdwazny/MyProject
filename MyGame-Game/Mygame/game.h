#ifndef GAME_H
#define GAME_H
#include "mapgame.h"
#include "collision.h"
//#include "enemies.h"
//#include "items.h"

/*
 Main game class
 create game loop and renderwindow
*/
class Game :public Collision
{
private:
    //window
    sf::RenderWindow* window;
    //sf::RenderWindow* equipment;
    //events
    sf::Event ev;
    //sf::Event event;

    //private properties
    std::unique_ptr<sf::Texture> tex_hud;
    std::vector<std::unique_ptr<sf::Sprite>> game_sprites;
    std::vector<sf::IntRect> game_rect;

    //private functions
    void InitTextures();
    void InitText();
    void InitLight();
    void InitLightings();
    void CreateOtherClasses();
    void Update_TexturesPosition();
    void UpdateKeybordInput();
    void UpdateCollision();
public:
    //constructor and destructor
    Game();
    virtual ~Game();
    //public functions
    void update();
    void render();
    bool running();
    void pollevent();
    //public properties
    Enemies* enemies;
    Items* things;
    MapGame* level;
    MyCharacter* hero;
    //Weapons* weapon;
    sf::Vector2f direction;
    //time
    sf::Clock clock;
    sf::Time elapsed;
    //view
    sf::View view;
    int licz_pom;
    //coins
    int coins_licz;
    sf::Font font;
    sf::Text coin_text;
    sf::Text gameover;
    sf::Text again;
    //start again
    bool startagain;

    //light
    sf::CircleShape light;
    sf::RenderTexture lightingTex;
    sf::Sprite lighting;
    std::vector<sf::CircleShape> pochodnie;
    std::vector<sf::Sprite> sp_pochodnie;
    int kolor_licz;

    //Collision functions

    //collision enemies with items
    void EnemiesWithItems_collision();
    //collect coins
    void CollectCoins();
    //collect keys
    void CollectKeys();
    //open the doors
    void OpenDoors();

};

#endif // GAME_H
