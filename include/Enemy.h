#pragma once
#include "Entity.h"
#include "Vec2f.h"
#include "Utils.h"
class Map;

class Enemy : public Entity
{
private:
    int health, maxHealth;
    float frameTimer, walkTimer, invincibilityTime;
    bool drop;
    Vec2f walkDir;

public:
    /**
     * @brief Get the Type Enemy of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const { return ENEMY_ID; }

    /**
     * @brief Construct a new Enemy object
     *
     */
    Enemy();

    /**
     * @brief Construct a new Enemy object with the given parameters
     *
     * @param p_pos the position of the enemy
     * @param p_health the health of the enemy
     * @param p_walkTimer the walk timer of the enemy(how many time will the enemy stay in place at the beginning)
     */
    Enemy(Vec2f p_pos, int p_health, float p_walkTimer);

    /**
     * @brief Get the Health of Enemy object
     *
     * @return int the health of the enemy
     */
    virtual int getHealth() const;

    /**
     * @brief Get the Max Health object
     *
     * @return int the max health of the enemy
     */
    virtual int getMaxHealth() const;

    /**
     * @brief Get the Frame Timer object
     *
     * @return float the frame timer of the enemy
     */
    float getFrameTimer() const;

    /**
     * @brief Set the Frame Timer object
     *
     * @param p_frameTimer the frame timer of the enemy
     */
    void setFrameTimer(float p_frameTimer);

    /**
     * @brief Damage the Entity object
     *
     * @param p_health the health of the enemy
     */
    virtual void damage(int p_health);

    /**
     * @brief get to know is the Enemy is dead
     *
     * @return bool true if the enemy is dead and false otherwise
     */
    virtual bool isDead() const;

    /**
     * @brief update the Enemy object
     *
     * @param p_health the health of the enemy
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);

    /**
     * @brief Get to know if entity can be walked on
     *
     * @return false
     */
    virtual bool isWalkable() const;
};