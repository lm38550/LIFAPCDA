#include "Arrow.h"
#include "Entity.h"
#include "Map.h"
#include <math.h>

Arrow::Arrow() : Entity(), vel(Vec2f()), m_isDead(false) {}

Arrow::Arrow(Vec2f p_pos, Vec2f p_vel) : Entity(p_pos), vel(p_vel), m_isDead(false) {}

Vec2f Arrow::getVel() const
{
    return vel;
}

Vec2f Arrow::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    Vec2f temp = pos + (vel * dt);

    if (!(map.getTile(round(temp.x - 0.3), round(temp.y)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y)).isWalkable() &&
          map.getTile(round(temp.x), round(temp.y + 0.3)).isWalkable() &&
          map.getTile(round(temp.x), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x - 0.3), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x - 0.3), round(temp.y + 0.3)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y + 0.3)).isWalkable()))
    {
        m_isDead = true;
        return Vec2f(-1, -1);
    }

    for (int i = 0; i < (int)map.getEntities().size(); i++)
    {
        if (i != curIndex)
        {
            Entity *e = map.getEntities()[i];
            if ((round(e->getPos().x) == round(temp.x) && round(e->getPos().y) == round(temp.y)))
            {
                if (!e->isWalkable())
                {
                    if (e->type() == PLAYER_ID || e->type() == ENEMY_ID)
                        e->damage(ARROW_DAMAGE);
                    m_isDead = true;
                    return Vec2f(-1, -1);
                }
            }
        }
    }

    for (int i = 0; i < (int)map.getDoors().size(); i++)
    {
        if (round(map.getDoors()[i].getPos().x) == round(temp.x) && round(map.getDoors()[i].getPos().y) == round(temp.y))
        {
            m_isDead = true;
            return Vec2f(-1, -1);
        }
    }
    pos = temp;
    return Vec2f(-1, -1);
}

bool Arrow::isDead() const
{
    return m_isDead;
}

bool Arrow::isWalkable() const
{
    return true;
}