#ifndef CHALLENGE_RECTANGLE_H
#define CHALLENGE_RECTANGLE_H

#include <Math/Vector2.h>
#include <Math/Vector3.h>

//NOTE(mate): union,data[4]??
struct Rectangle
{    
    Vector2 bl;
    Vector2 br;
    Vector2 tl;
    Vector2 tr;

    Vector2 center();
    float width();
    float height();

    Rectangle() = default;
    Rectangle( Vector3 pos, Vector3 scale);
    Rectangle(const Rectangle& _other) = default;
    bool operator==(const Rectangle& _other) const;
};

Rectangle::Rectangle( Vector3 pos, Vector3 scale)
{
    bl = {pos.x, pos.y};
    br = {pos.x + scale.x,pos.y};
    tl = {pos.x,pos.y + scale.y};
    tr = {pos.x + scale.x,pos.y + scale.y};
}

Vector2 Rectangle::center()
{
    Vector2 center;
    center.x = bl.x + width()/2.0f;
    center.y = bl.y + height()/2.0f;
    return(center);
}

float Rectangle::width()
{
    float width;
    width = br.x - bl.x;    
    return(width);
}

float Rectangle::height()
{
    float height;
    height = tl.y - bl.y;
    return(height);
}

bool Rectangle::operator==(const Rectangle& _other) const
{
    bool value = false;
    if( (bl == _other.bl) &&
	(br == _other.br) &&
	(tl == _other.tl) &&
	(tr == _other.tr) )
    {
	value = true;
    }
    return(value);
}
#endif
