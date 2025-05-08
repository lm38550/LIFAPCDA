#include "Door.h"
#include "Map.h"
#include "Utils.h"

Door::Door(int p_ID, int p_destinationID, bool p_locked, Vec2f p_pos)
    : ID(p_ID), destinationID(p_destinationID), locked(p_locked), pos(p_pos) {}

Door::Door() : ID(0), destinationID(0), locked(false), pos(Vec2f(0.0f, 0.0f)) {}

int Door::getID() const
{
    return ID;
}

int Door::getDestinationID() const
{
    return destinationID;
}

bool Door::isLocked() const
{
    return locked;
}

void Door::setLocked(bool p_locked)
{
    locked = p_locked;
}

Vec2f Door::getPos() const
{
    return pos;
}

void Door::exploded()
{
    locked = false;
}

void Door::update(Map &map)
{
    if (locked)
    {
        bool allEnemiesDead = true;
        for (int i = 0; i < (int)map.getEntities().size(); i++)
        {
            if (map.getEntities()[i]->type() == ENEMY_ID)
            {
                allEnemiesDead = false;
                break;
            }
        }
        locked = !allEnemiesDead;
    }
}