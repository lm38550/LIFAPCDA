#include "Lantern.h"
#include "Utils.h"
#include "Map.h"
#include "Player.h"
#include "Fire.h"

#include <cmath>

Lantern::Lantern(int quantity) : Item(quantity) {}

int Lantern::id()
{
    return LANTERN_ID;
}

void Lantern::use(Map &map)
{

    Player *player = map.getPlayer();
    if (player == nullptr)
    {
        return;
    }
    if (m_quantity <= 0)
    {
        return;
    }
    Vec2f temp = (player->getPlayerDir() * 0.9f) + player->getPos();
    if (!map.getTile(std::floor(temp.x), std::floor(temp.y)).isWalkable())
    {
        return;
    }
    m_quantity--;
    map.addEntity(new Fire(temp, FIRE_TIME));
}

Lantern::~Lantern()
{
}