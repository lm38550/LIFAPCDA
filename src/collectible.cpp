#include "Map.h"
#include "Player.h"
#include "Collectible.h"
#include "Utils.h"
#include <iostream>

int Collectible::type() const
{
    return COLLECTIBLE_ID;
}

Collectible::Collectible(Vec2f pos, int value, int id) : Entity(pos), value(value), id(id), collected(false) {}

int Collectible::getValue()
{
    return value;
}

int Collectible::getId()
{
    return id;
}

bool Collectible::isDead() const
{
    return collected;
}

Vec2f Collectible::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    if (map.getPlayer() == nullptr)
        return Vec2f(-1, -1);
    if (distance(pos, map.getPlayer()->getPos()) < 2 * ENTITY_RADIUS)
    {
        switch (id)
        {
        case COLLECTIBLE_HEALTH:
            map.getPlayer()->heal(value);
            collected = true;
            break;
        case COLLECTIBLE_ABRICOT:
            map.getInventory().addAbricot(value);
            collected = true;
            break;
        case COLLECTIBLE_BOMB:
            if (map.getInventory().hasItem(BOMBBAG_ID))
            {
                map.getInventory().addToItem(BOMBBAG_ID, value);
                collected = true;
            }
            break;
        case COLLECTIBLE_ARROW:
            if (map.getInventory().hasItem(BOW_ID))
            {
                map.getInventory().addToItem(BOW_ID, value);
                collected = true;
            }
            break;
        case COLLECTIBLE_OIL:
            if (map.getInventory().hasItem(LANTERN_ID))
            {
                map.getInventory().addToItem(LANTERN_ID, value);
                collected = true;
            }
            break;
        case COLLECTIBLE_CROWN:
            map.win = true;
            break;
        }
        return Vec2f(-1, -1);
    }
    return Vec2f(-1, -1);
}