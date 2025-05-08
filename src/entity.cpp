#include "Entity.h"
#include "Utils.h"
#include <cassert>

int Entity::getHealth() const
{
    assert(false);
    return 0;
}

int Entity::getMaxHealth() const
{
    assert(false);
    return 0;
}

Entity::Entity() {}

Entity::Entity(Vec2f p_pos) : pos(p_pos) {}

Vec2f Entity::getPos() const
{
    return pos;
}

bool Entity::isVisible() const
{
    return true;
}

void Entity::setPos(Vec2f new_pos)
{
    pos = new_pos;
}

void Entity::exploded()
{
    damage(BOMB_DAMAGE);
}

Vec2f Entity::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    return Vec2f(-1, -1);
}

bool Entity::isWalkable() const
{
    return true;
}

void Entity::damage(int p_health) {}

bool Entity::isDead() const
{
    return false;
}

int Entity::getEquipped() const
{
    assert(false);
    return 0;
}

void Entity::setEquipped(int p_equipped)
{
    assert(false);
}

bool Entity::isExploding() const
{
    assert(false);
    return false;
}

float Entity::getTimer() const
{
    assert(false);
    return 0.0f;
}

Vec2f Entity::getPlayerDir()
{
    assert(false);
    return Vec2f();
}

float Entity::getFrameTimer() const
{
    assert(false);
    return 0.0f;
}

void Entity::setFrameTimer(float p_frameTimer)
{
    assert(false);
}

int Entity::getContainID() const
{
    assert(false);
    return 0;
}

void Entity::Interact(Map &map) {}