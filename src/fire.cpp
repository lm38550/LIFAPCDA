#include "Fire.h"
#include "Map.h"
#include <math.h>
#include <iostream>

Fire::Fire() : Entity(), timer(1.5f) {}

Fire::Fire(Vec2f p_pos, float p_timer) : Entity(p_pos), timer(p_timer) {}

float Fire::getTimer() const
{
    return timer;
}

bool Fire::isDead() const
{
    return timer <= 0;
}

Vec2f Fire::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    timer -= dt;
    return Vec2f(-1, -1);
}