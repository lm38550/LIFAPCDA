#include "Bow.h"
#include "Utils.h"
#include "Player.h"
#include "Arrow.h"

#include <cmath>

Bow::Bow(int quantity) : Item(quantity) {}

int Bow::id()
{
    return BOW_ID;
}

void Bow::use(Map &map)
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
    map.addEntity(new Arrow(temp, player->getPlayerDir() * ARROW_SPEED));
}

Bow::~Bow()
{
}