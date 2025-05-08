#include "Bomb.h"
#include "Map.h"
#include "Utils.h"

#include <iostream>

void Bomb::explode(Map &map)
{
    for (int i = 0; i < (int)map.getEntities().size(); i++)
    {
        if (distance(map.getEntities()[i]->getPos(), pos) < BOMB_EXPLOSION_RADIUS + ENTITY_RADIUS)
        {
            map.getEntities()[i]->exploded();
        }
    }
    for (int i = 0; i < (int)map.getDoors().size(); i++)
    {
        if (distance(map.getDoors()[i].getPos(), pos) < BOMB_EXPLOSION_RADIUS + ENTITY_RADIUS)
        {
            map.getDoors()[i].exploded();
        }
    }
}

Bomb::Bomb() : Entity(), timer(BOMB_TIME), exploding(false) {}

Bomb::Bomb(Vec2f p_pos) : Entity(p_pos), timer(BOMB_TIME), exploding(false) {}

float Bomb::getTimer() const
{
    return timer;
}

bool Bomb::isExploding() const
{
    return exploding;
}

bool Bomb::isDead() const
{
    return (exploding && timer <= 0);
}

Vec2f Bomb::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    // std::cout << "a" << timer << std::endl;
    timer -= dt;
    if (timer <= 0)
    {
        if (!exploding)
        {
            exploding = true;
            explode(map);
            timer = BOMB_EXPLOSION_TIME;
        }
    }
    if (exploding)
    {
        explode(map);
    }
    return Vec2f(-1, -1);
}