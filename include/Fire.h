#pragma once
#include "Entity.h"
#include "Utils.h"

class Map;

class Fire : public Entity
{
private:
    float timer;

public:
    /**
     * @brief Get the Type Fire of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const { return FIRE_ID; }

    /**
     * @brief Construct a new Fire object
     *
     */
    Fire();

    /**
     * @brief Construct a new Fire object
     *
     * @param p_pos the position of the fire
     * @param p_timer the timer of the fire
     */
    Fire(Vec2f p_pos, float p_timer);

    /**
     * @brief Get the Timer object
     *
     * @return float the timer of the fire in seconds
     */
    float getTimer() const;

    /**
     * @brief Get to know if fire is dead
     *
     * @return true if the fire is dead and false otherwise
     */
    virtual bool isDead() const;

    /**
     * @brief Update fire
     *
     * @param p_map a Map object that contains the map
     * @param p_deltaTime a float that contains the delta time
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);
};