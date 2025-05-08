#include "BombBag.h"
#include "Bomb.h"
#include "Map.h"
#include "Player.h"
#include <cmath>
#include <iostream>

BombBag::BombBag(int quantity) : Item(quantity) {}

int BombBag::id()
{
    return BOMBBAG_ID;
}

void BombBag::use(Map &map)
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
    map.addEntity(new Bomb(temp));
}

BombBag::~BombBag()
{
}