#include "Chest.h"
#include "Utils.h"
#include "Map.h"
#include "BombBag.h"
#include "Bow.h"
#include "Lantern.h"
#include <cassert>

Chest::Chest() : Entity(), containID(-1), textureID(0), visible(true) {}

Chest::Chest(int p_containID, int p_texture_ID, Vec2f p_pos, bool p_visible) : Entity(p_pos), containID(p_containID), textureID(p_texture_ID), visible(p_visible) {}

int Chest::getContainID() const
{
    return containID;
}

void Chest::setContainID(int p_containID)
{
    containID = p_containID;
}

int Chest::getTextureID() const
{
    return textureID;
}

Vec2f Chest::getPos() const
{
    return pos;
}

bool Chest::isVisible() const
{
    return visible;
}

void Chest::setVisible(bool p_visible)
{
    visible = p_visible;
}

bool Chest::isWalkable() const
{
    return !visible;
}

bool Chest::isOpen()
{
    return containID == -1;
}

void Chest::Interact(Map &map)
{
    if(isOpen())
        return;
    switch (containID)
    {
    case CHEST_5_ABRICOT:
        map.getInventory().addAbricot(5);
        break;
    
    case CHEST_BOMBBAG:
        map.getInventory().addItem(new BombBag(0));
        break;

    case CHEST_BOW:
       map.getInventory().addItem(new Bow(0));
       break;

    case CHEST_LANTERN:
       map.getInventory().addItem(new Lantern(0));
       break;

    default:
        assert(false);
        break;
    }
    containID = -1;
}