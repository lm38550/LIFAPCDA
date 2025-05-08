#pragma once
#include "Entity.h"
#include "Utils.h"

class Map;

class Bomb : public Entity
{
private:
    float timer;
    bool exploding;

    void explode(Map &map);

public:
    /**
     * @brief Get the Type Bomb of the Entity object
     *
     * @return the type of the entity
     */
    virtual int type() const { return BOMB_ID; }

    /**
     * @brief Construct a new Bomb object
     *
     */
    Bomb();

    /**
     * @brief Construct a new Bomb object with position
     *
     * @param p_pos the position of the bomb
     */
    Bomb(Vec2f p_pos);

    /**
     * @brief Get the timer of the bomb
     *
     * @return the timer of the bomb in seconds (float)
     */
    float getTimer() const;

    /**
     * @brief Get if the bomb is exploding
     *
     * @return true if the bomb is exploding and false otherwise
     */
    virtual bool isExploding() const;

    /**
     * @brief Get to know if an entity is dead
     *
     * @return true if the bomb is dead and false otherwise
     */
    virtual bool isDead() const;

    /**
     * @brief update the Entity object
     *
     * @param dir a Vec2f object that contains the direction of the player
     * @param dt a float that contains the delta time
     * @param map a Map object that contains the map
     * @param curIndex an int that contains the current index of the player
     *
     * @return Vec2f(-1, -1)
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);
};