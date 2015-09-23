#ifndef CHALLENGE_WORLD_H
#define CHALLENGE_WORLD_H

//NOTE(mate): map test
struct Map
{
    Wall::sWalls staticWalls;
    Wall::dWalls dynamicWalls;
};

struct world
{
    std::vector<Map> maps;
    int activeMap;
};

#endif CHALLENGE_WORLD_H
 
