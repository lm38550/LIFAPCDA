#include "Enemy.h"
#include "Collectible.h"
#include "Map.h"
#include "Utils.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>

#include <iostream>

Enemy::Enemy() : Entity(), health(0), maxHealth(0), frameTimer(2.0f), walkTimer(0.0f), invincibilityTime(0.0f), drop(false), walkDir() {}

Enemy::Enemy(Vec2f p_pos, int p_health, float p_walkTimer) : Entity(p_pos), health(p_health), maxHealth(p_health), frameTimer(2.0f), walkTimer(p_walkTimer), invincibilityTime(0.0f), drop(false), walkDir() {}

int Enemy::getHealth() const
{
    return health;
}

int Enemy::getMaxHealth() const
{
    return maxHealth;
}

float Enemy::getFrameTimer() const
{
    return frameTimer;
}

void Enemy::setFrameTimer(float p_frameTimer)
{
    frameTimer = p_frameTimer;
}

void Enemy::damage(int p_health)
{
    if (invincibilityTime <= 0.0f)
    {
        health -= p_health;
        invincibilityTime = ENEMY_INVINCIBILITY_TIME;
    }
}

bool Enemy::isDead() const
{
    return health <= 0 && drop;
}

Vec2f Enemy::update(Vec2f dir, float dt, Map &map, int curIndex)
{
    srand(time(NULL));
    if (health <= 0.0f)
    {
        if (rand() % 100 < ENEMY_DROP_CHANCE)
        {
            int type = rand() % 5;
            if (
                (type == COLLECTIBLE_BOMB && map.getInventory().hasItem(BOMBBAG_ID)) ||
                (type == COLLECTIBLE_ARROW && map.getInventory().hasItem(BOW_ID)) ||
                (type == COLLECTIBLE_OIL && map.getInventory().hasItem(LANTERN_ID)) ||
                type == COLLECTIBLE_HEALTH || type == COLLECTIBLE_ABRICOT)
                map.addEntity(new Collectible(pos, type, rand() % 10 + 1));
        }
        drop = true;
        return Vec2f(-1, -1);
    }
    if (walkTimer <= 0.0f)
    {
        walkTimer = (float)(rand() % 100 + 1) / 100.0f;
        do
        {
            walkDir = Vec2f((float)(rand() % 3 - 1), (float)(rand() % 3 - 1));
        } while (!(walkDir.x == 0 || walkDir.y == 0));
    }
    else
    {
        Vec2f temp = pos + (walkDir * dt);
        if (!(map.getTile(round(temp.x - 0.3), round(temp.y)).isWalkable() &&
              map.getTile(round(temp.x + 0.3), round(temp.y)).isWalkable() &&
              map.getTile(round(temp.x), round(temp.y + 0.3)).isWalkable() &&
              map.getTile(round(temp.x), round(temp.y - 0.3)).isWalkable() &&
              map.getTile(round(temp.x - 0.3), round(temp.y - 0.3)).isWalkable() &&
              map.getTile(round(temp.x + 0.3), round(temp.y - 0.3)).isWalkable() &&
              map.getTile(round(temp.x - 0.3), round(temp.y + 0.3)).isWalkable() &&
              map.getTile(round(temp.x + 0.3), round(temp.y + 0.3)).isWalkable()))
        {
            walkTimer = 0.0f;
            return Vec2f(-1, -1);
        }

        for (int i = 0; i < (int)map.getEntities().size(); i++)
        {
            if (i != curIndex)
            {
                Entity *e = map.getEntities()[i];
                if (distance(e->getPos(), temp) <= 0.6f)
                {
                    if (!e->isWalkable())
                    {
                        walkTimer = 0.0f;
                        if (e->type() == PLAYER_ID)
                            e->damage(ENEMY_DAMAGE);
                        return Vec2f(-1, -1);
                    }
                    else
                    {
                        walkTimer = 0.0f;
                        if (e->type() == FIRE_ID)
                            damage(FIRE_DAMAGE);
                        pos = temp;
                        return Vec2f(-1, -1);
                    }
                }
            }
        }

        for (int i = 0; i < (int)map.getDoors().size(); i++)
        {
            if (round(map.getDoors()[i].getPos().x) == round(temp.x) && round(map.getDoors()[i].getPos().y) == round(temp.y))
            {
                walkTimer = 0.0f;
                return Vec2f(-1, -1);
            }
        }
        pos = temp;
        walkTimer -= dt;
        invincibilityTime -= dt;
    }
    return Vec2f(-1, -1);
}

bool Enemy::isWalkable() const
{
    return false;
}