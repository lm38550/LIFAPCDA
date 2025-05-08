#include "Player.h"
#include "Utils.h"
#include <cmath>

#include <iostream>

Player::Player() : Entity(), life(1), maxLife(1), equipped(-1), invincibilityTime(0.0f), dir(0, 1) {}

Player::Player(int p_life, int p_maxLife, int p_equipped, Vec2f p_pos, Vec2f p_dir) : Entity(p_pos), life(p_life), maxLife(p_maxLife), equipped(p_equipped), invincibilityTime(0.0f), dir(p_dir) {}

int Player::getHealth() const
{
    return life;
}

void Player::setHealth(int p_life)
{
    life = p_life;
}

int Player::getMaxHealth() const
{
    return maxLife;
}

void Player::setMaxHealth(int p_maxLife)
{
    maxLife = p_maxLife;
}

void Player::heal(int amount)
{
    life += amount;
    if (life > maxLife)
        life = maxLife;
}

int Player::getEquipped() const
{
    return equipped;
}

void Player::setEquipped(int p_equipped)
{
    equipped = p_equipped;
}

Vec2f Player::update(Vec2f p_dir, float dt, Map &map, int curIndex)
{
    Vec2f temp = pos + (p_dir * dt * 4.0f);
    if (p_dir != Vec2f(0, 0))
    {
        dir = p_dir;
    }
    if (invincibilityTime > 0.0f)
    {
        invincibilityTime -= dt;
    }
    if (!(map.getTile(round(temp.x - 0.3), round(temp.y)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y)).isWalkable() &&
          map.getTile(round(temp.x), round(temp.y + 0.3)).isWalkable() &&
          map.getTile(round(temp.x), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x - 0.3), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y - 0.3)).isWalkable() &&
          map.getTile(round(temp.x - 0.3), round(temp.y + 0.3)).isWalkable() &&
          map.getTile(round(temp.x + 0.3), round(temp.y + 0.3)).isWalkable()))
    {
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
                    if (e->type() == ENEMY_ID)
                        damage(ENEMY_DAMAGE);
                    return Vec2f(-1, -1);
                }
                else
                {
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
        if (map.getDoors()[i].isLocked())
        {
            if (round(map.getDoors()[i].getPos().x) == round(temp.x) && round(map.getDoors()[i].getPos().y) == round(temp.y))
            {
                return Vec2f(-1, -1);
            }
        }
        else
        {
            if (round(map.getDoors()[i].getPos().x) == round(temp.x) && round(map.getDoors()[i].getPos().y) == round(temp.y))
            {
                pos = temp;
                return Vec2f(map.getDoors()[i].getID(), map.getDoors()[i].getDestinationID());
            }
        }
    }
    pos = temp;
    return Vec2f(-1, -1);
}

bool Player::isWalkable() const
{
    return false;
}

bool Player::getIsWalking() const
{
    return isWalking;
}

void Player::setIsWalking(bool p_isWalking)
{
    isWalking = p_isWalking;
}

float Player::getFrameTimer() const
{
    return frameTimer;
}

void Player::setFrameTimer(float p_frameTimer) 
{
    frameTimer = p_frameTimer;
}

void Player::damage(int p_health)
{
    if (invincibilityTime <= 0.0f)
    {
        life -= p_health;
        invincibilityTime = PLAYER_INVINCIBILITY_TIME;
    }
}

bool Player::isDead() const
{
    if (getHealth() <= 0)
    {
        return true;
    }
    return false;
}

Vec2f Player::getPlayerDir()
{
    return dir;
}

Sword Player::getSword() const
{
    return sword;
}

void Player::attack(const std::vector<Entity *> &entities)
{
    for (int i = 0; i < (int)entities.size(); i++)
    {
        if(distance((pos+(dir*=SWORD_SIZE)), entities[i]->getPos()) <= (2*ENTITY_RADIUS) + 0.5f)
        {
            if( distance( (pos+(dir*=SWORD_SIZE)), entities[i]->getPos() ) <= 0.5f)
            {
                entities[i]->damage(getSword().getSwordDamage()); 
            }
        }
    }
}

void Player::Interacting(Map &map)
{
    for(int i=0; i<(int)map.getEntities().size(); i++)
    {
        if( distance(pos, map.getEntities()[i]->getPos()) <= (2*ENTITY_RADIUS) + 0.1f)
        {
            if( distance(pos + (dir*(ENTITY_RADIUS*2)), map.getEntities()[i]->getPos()) <= 0.1f)
            {
                if(map.getEntities()[i]->isVisible())
                {
                    map.getEntities()[i]->Interact(map);
                }
            }
        }
    }
}