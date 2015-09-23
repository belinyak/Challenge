#ifndef CHALLENGE_HERO_H
#define CHALLENGE_HERO_H

#include <Game/Hero_Movement.h>
#include <Game/Config.h>

const float speed = 0.0050f * 120.0f * TIME_STEP;
const float gravity = -0.0070f * 120.0f * TIME_STEP;
const float jumpSpeed = 60.0f * speed;
const float drag = 0.3f * TIME_STEP;
const Vector3 maxVelocity = {0.1f,0.22f,0} ;
const float minVelocity = 0.002f ;

const char* heroTexturePath = "c:\\Users\\Belinyak\\Documents\\GitHub\\Challenge\\Data\\Textures\\hero2.png";

namespace Movement
{
    enum Type
    {
	None  = 1 << 1,
	
	Left  = 1 << 2,
	Right = 1 << 3,
	Jump  = 1 << 4,
    }; 
}
namespace Collision
{
    enum Type
    {
	None,

	Left,
	Right,
	Top,
	Bottom,
    };
   
}

struct Move
{
    Movement::Type direction;
    Collision::Type collisionType = Collision::Type::None;
    
    Vector3 velocity;
    Vector3 acceleration;
    
    void update(Vector3 position);
};

struct Hero
{
    ModelInstance instance;
    Move move;
    void init(ShaderProgram* g_defaultShader);
    void update();
};   

GLOBAL Hero hero;
GLOBAL ModelAsset HeroAsset;
GLOBAL Material heroMaterial;


void Hero::init(ShaderProgram* g_defaultShader)
{
    heroMaterial = loadMaterial(heroTexturePath,g_defaultShader);
   
    HeroAsset = loadSpriteAsset(g_defaultShader);
    HeroAsset.material = &heroMaterial;
    
    hero.instance = loadHeroInstance(&HeroAsset);
    hero.instance.transform.position = { 1.5f,2.5f,0 };
}

void Hero::update()
{
    move.update(instance.transform.position);
}
#endif
