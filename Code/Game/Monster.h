#ifndef CHALLENGE_MONSTER_H
#define CHALLENGE_MONSTER_H

GLOBAL Material monsterMaterial;
GLOBAL ModelAsset monsterAsset;

const char* monsterPath = "c:\\Users\\Belinyak\\Documents\\GitHub\\Challenge\\Data\\Textures\\hero2.png";
static std::vector<Vector2> left;   
static std::vector<Vector2> right;

namespace MonsterMovemet
{
    enum Type
    {
	Left = -1,
	Right = 1,
    };
}

struct Monster
{
    MonsterMovemet::Type direction = MonsterMovemet::Type::Right;
    ModelInstance instance;
    Vector3 initPos;
    int distance ;
    float velocity;

    
    void init(ShaderProgram* g_defaultShader, Vector3 _initPos, float _distance, float _velocity);
    void update();
};

GLOBAL Monster monster;


void Monster::update()
{
    if( instance.transform.position.x <= initPos.x )
    {
	direction = MonsterMovemet::Type::Right;
	instance.asset->mesh->changeTextCoord(right);	    
    }
    if( instance.transform.position.x >= initPos.x + distance )
    {
	direction = MonsterMovemet::Type::Left;
	instance.asset->mesh->changeTextCoord(left);	    
    }
    
    instance.transform.position.x += (int)direction * velocity;	
}

void Monster::init(ShaderProgram* g_defaultShader, Vector3 _initPos, float _distance, float _velocity)
{
    distance = _distance;
    initPos = _initPos;
    velocity = _velocity;
    
    monsterMaterial.shaders = g_defaultShader;
    monsterMaterial.texture = new Texture();
    monsterMaterial.texture->loadFromFile( monsterPath);
    
    monsterAsset = loadSpriteAsset(g_defaultShader);
    monsterAsset.material = &monsterMaterial;
    
    instance = loadHeroInstance(&monsterAsset);
    instance.transform.position = initPos;
    instance.transform.scale.y = 0.7f;
    
    left.push_back({ 0.0f, 0.515f });
    left.push_back({ 1.0f, 0.515f });
    left.push_back({ 1.0f, 1.0f });
    left.push_back({ 0.0f, 1.0f });
    
    right.push_back({ 0.0f, 0.0f });
    right.push_back({ 1.0f, 0.0f });
    right.push_back({ 1.0f, 0.48f });
    right.push_back({ 0.0f, 0.48f });    
}
#endif CHALLENGE_MONSTER_H
 
