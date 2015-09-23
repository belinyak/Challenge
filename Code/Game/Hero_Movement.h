#ifndef CHALLENGE_HERO_MOVEMENT_H
#define CHALLENGE_HERO_MOVEMENT_H

#include <Game/Wall.h>
#include <Game/Hero.h>
#include <Math/Rectangle.h>
#include <Game/World.h>
#include <Game/Monster.h>

//extern Wall::dWalls dynamicWalls; 
//extern Wall::sWalls staticWalls; 

extern world World;

extern GLFWwindow* window;
extern Hero hero;
extern Monster monster;
//extern Monster monster2;
//extern Monster monster3;
//extern Monster monster4;

Movement::Type Direction(GLFWwindow* window)
{
#if 1
    static std::vector<Vector2> left;
    left.push_back({ 0.0f, 0.515f });
    left.push_back({ 1.0f, 0.515f });
    left.push_back({ 1.0f, 1.0f });
    left.push_back({ 0.0f, 1.0f });
    
    static std::vector<Vector2> right;
    right.push_back({ 0.0f, 0.0f });
    right.push_back({ 1.0f, 0.0f });
    right.push_back({ 1.0f, 0.48f });
    right.push_back({ 0.0f, 0.48f });
#endif

    //TODO(mate): store previous direction, only change textcoord if
    //changed
    static int dir = 0;
    
    Movement::Type value = Movement::Type::None;

    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
    {
	value = (Movement::Type)((int)value + (int)Movement::Type::Jump);
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS)
    {
	value = (Movement::Type)((int)value + (int)Movement::Type::Left);
	if(dir != 1)
	{
	    hero.instance.asset->mesh->changeTextCoord(left);
	}
	dir = 1;
    }
    if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
	value = (Movement::Type)((int)value + (int)Movement::Type::Right);
	if(dir != 2)
	{
	    hero.instance.asset->mesh->changeTextCoord(right);	    
	}
	dir = 2;
    }      

    if( ((Movement::Type::Left & value) != 0 ) &&
	((Movement::Type::Right & value) != 0 ))
    {
	if((Movement::Type::Jump & value) != 0 )
	{
	    value = Movement::Type::Jump;
	}
	else
	{
	    value = Movement::Type::None;
	}
    }
    
    return(value);
}

Collision::Type Minkowski(Rectangle* hero, Rectangle* wall)
{
    Collision::Type value = Collision::Type::None;

    float w = 0.5f * (hero->width() + wall->width());
    float h = 0.5f * (hero->height()  + wall->height());

    Vector2 d = hero->center() - wall->center();

    if (fabs(d.x) <= w && fabs(d.y) <= h)
    {
	float wy = w * d.y;
	float hx = h * d.x;

	if (wy > hx)
	{
	    if (wy > -hx)
	    {
		value = Collision::Type::Top;
	    }
	    else
	    {
		value = Collision::Type::Left;
	    }
	}
	else 
	{
	    if (wy > -hx)
	    {
		value = Collision::Type::Right;
	    }
	    else
	    {
		value = Collision::Type::Bottom;
	    }
	}
    }	    
    return(value);
}

bool CollideWithMonster(Vector3 nextPos, Monster* monster)
{
    bool collide = false;

    Rectangle rHero = Rectangle(nextPos, hero.instance.transform.scale);
    Rectangle rMonster = Rectangle(monster->instance.transform.position,
				   monster->instance.transform.scale);

    hero.move.collisionType = Minkowski( &rHero, &rMonster);
    
    if( hero.move.collisionType != Collision::Type::None )
    {
	collide = true;
    }    
       
    return(collide);
}

Vector3 CollideWithDynamicWalls(Vector3 nextPos, Wall::dWalls* dynamicWalls )
{
    bool collide = false;
    Vector3 value;

    Rectangle rHero = Rectangle(nextPos, hero.instance.transform.scale);
    Rectangle rWall;
    
    for(int i=0;
	i<dynamicWalls->Walls.size();
	++i)
    {
	rWall = Rectangle(dynamicWalls->Walls[i].transform.position,
			  dynamicWalls->Walls[i].transform.scale);

	hero.move.collisionType = Minkowski( &rHero, &rWall);
	if(hero.move.collisionType != Collision::Type::None )
	{
	    collide = true;
	    value = dynamicWalls->velocity;
	    return value;
	}
    }
    return value;
}

bool CollideWithStaticWalls(Vector3 nextPos, Wall::sWalls* staticWalls )
{
    Vector3 value;

    Rectangle rHero = Rectangle(nextPos, hero.instance.transform.scale);
    Rectangle rWall;
      
    for(int i=0;
	i<staticWalls->Walls.size();
	++i)
    {
	rWall = Rectangle(staticWalls->Walls[i].transform.position,
			  staticWalls->Walls[i].transform.scale);
	hero.move.collisionType = Minkowski( &rHero, &rWall);
	if( hero.move.collisionType != Collision::Type::None )
	{
	    return(true);
	}
    }
    return false;
}

Vector3 Move(Vector3 prevPos, Vector3 move)
{
    int tryCount = 0;
    Vector3 value;
    //TODO(mate): this is the worst solution ever!
    while(tryCount<3)
    {
	Vector3 value = move * pow(0.5f,tryCount);
	Vector3 nextPos = prevPos + value;
	if(CollideWithStaticWalls(nextPos,&World.maps[World.activeMap].staticWalls) == false)
	{
	    if( (CollideWithMonster(nextPos,&monster) == false))
	    {
		Vector3 temp = CollideWithDynamicWalls(nextPos, &World.maps[World.activeMap].dynamicWalls );

		//NOTE(mate): horizontal movement
		{
		    if(0.0f < temp.x)
		    {
			if(0.0f < value.x)
			{
			    value.x = -4 * temp.x;
			}
			else if( 0.0f > value.x)
			{
			    value.x = 4 * temp.x;
			}
			else
			{
			    value.x = 4 * temp.x;
			}
			if(move.y>0)
			{
			    value.y = 0.00001f;
			}
			else
			{
			    value.y = 0.0f;
			}
		    }
		    else if(0.0f > temp.x)
		    {
			if(0.0f < value.x)
			{
			    value.x = 4 *temp.x;
			}
			else if( 0.0f > value.x)
			{
			    value.x = -4 *temp.x;
			}
			else
			{
			    value.x = 4 *temp.x;
			}
			if(move.y>0)
			{
			    value.y = 0.00001f;
			}
			else
			{
			    value.y = 0.0f;
			}
		    }
		}
		//TODO(mate): vertical movement NOTE(mate): az a baj, hogy
		//a jump akkor engedélyezett, ha value.y == 0, itt meg nem
		//annyi, kell valami jumpEnabled flag
		    
		return(value);
	    }
	     else
	    {
		//NOTE(mate): monster collision
	    	hero.instance.transform.position = {1.0f,2.0f,0};
		return(value);

	    }
	}
	tryCount++;
    }
    //NOTE(mate): "befejeli a plafont" attól ne ugorhasson :D
    if(move.y>0)
    {
	value.y = minVelocity;
    }
    return(value);
}   

Vector3 VelocityBound(Vector3 oldVelocity, Vector3 maxVelocity)
{
    Vector3 velocity = oldVelocity ;

    if(oldVelocity.x > maxVelocity.x)
    {
	velocity.x = maxVelocity.x;
    }

    if(oldVelocity.x < -maxVelocity.x)
    {
	velocity.x = -maxVelocity.x;
    }
	
    if(oldVelocity.y > maxVelocity.y )
    {
	velocity.y = maxVelocity.y;
    }

    if(oldVelocity.y < -maxVelocity.y )
    {
	velocity.y = -maxVelocity.y;
    }
	
    return(velocity);
}
   
Vector3 Acceleration(Movement::Type direction, Vector3 velocity)
{
    Vector3 acceleration = {0,gravity,0};

    if( (direction & Movement::Type::Jump) != 0 )
    {
	if( velocity.y == 0  )
	{
	    acceleration += Vector3{0,jumpSpeed,0};    	
	}
    }
    if( (direction & Movement::Type::Left) != 0 )
    {
	acceleration += Vector3{-1   * speed,0, 0};
    }
    if( (direction & Movement::Type::Right) != 0 )
    {
	acceleration += Vector3{1  * speed,0, 0};
    }
    if( (direction & Movement::Type::None) != 0 )
    {
	if( velocity.x > 0 )
	{
	    acceleration.x -= drag;
	}
	else if( velocity.x < 0 )
	{
	    acceleration.x += drag;
	}
    }	
    return(acceleration);
}

Vector3 Velocity(Vector3 velocity, Vector3 position)
{
    //TODO(mate): collision typpal egyben a move!!
    Vector3 value;

    Vector3 movex;
    Vector3 movey;

    //NOTE(mate): külön vertical/horizontal movement, ha mondjuk ugrás
    //közben jobbra nekimegy a falnak, attól ne álljon meg a levegõben

    movex =  Move(position, {velocity.x,0.0f,velocity.z});
    movey =  Move(position, {0.0f,velocity.y,velocity.z});
	
    value.x = movex.x;
    value.y = movey.y;

    return(value);
}

void Move::update(Vector3 position)
{
    Move move;

    move.direction = direction;
    move.velocity = velocity;
	
    move.acceleration = {0,gravity,0};


    move.direction = Direction(window);
	
    move.acceleration = Acceleration(move.direction,move.velocity);
		
    move.velocity += move.acceleration;
    move.velocity = VelocityBound(move.velocity,maxVelocity);
    move.velocity = Velocity(move.velocity,position);
	
    direction = move.direction;
    velocity = move.velocity;
    acceleration = move.acceleration;

    if(velocity.x < minVelocity &&  velocity.x > -minVelocity )
    {
	velocity.x = 0;
    }
    
    hero.instance.transform.position += velocity;
}

#endif
