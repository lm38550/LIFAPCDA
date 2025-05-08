#pragma once
#include "Entity.h"
#include "Utils.h"
#include "Vec2f.h"

class Map;

class Arrow : public Entity
{
private:
    Vec2f vel;
    bool m_isDead;

public:
    /**
     * @brief Get the Type Arrow of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const { return ARROW_ID; }

    /**
     * @brief Construct a new Arrow object
     *
     */
    Arrow();

    /**
     * @brief Construct a new Arrow object with position and velocity
     *
     * @param p_pos a Vec2f object that contains the position of the arrow
     * @param p_vel a Vec2f object that contains the velocity of the arrow
     */
    Arrow(Vec2f p_pos, Vec2f p_vel);

    /**
     * @brief Get the velocity of the arrow
     *
     * @return the velocity of the arrow
     */
    Vec2f getVel() const;

    /**
     * @brief Update Arrow
     *
     * @param dir a Vec2f object that contains the direction of the player
     * @param dt a float that contains the delta time
     * @param map a Map object that contains the map
     * @param curIndex an int that contains the current index of the player
     *
     * @return Vec2f(-1, -1)
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);

    /**
     * @brief Get to know if entity is dead
     *
     * @return true if the arrow is dead and false otherwise
     */
    bool isDead() const;

    /**
     * @brief Get to know if entity can be walked on
     *
     * @return return false
     */
    virtual bool isWalkable() const;
};