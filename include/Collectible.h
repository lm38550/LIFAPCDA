#pragma once
#include "Entity.h"
#include "Vec2f.h"

class Collectible : public Entity
{
private:
    int value, id;
    bool collected;

public:
    /**
     * @brief Get the Type Collectible of the Entity object
     *
     * @return int the type of the entity
     */
    int type() const;

    /**
     * @brief Construct a new Collectible object with the given parameters
     *
     * @param pos the position of the collectible
     * @param value the value of the collectible
     * @param id the id of the collectible
     */
    Collectible(Vec2f pos, int value, int id);

    /**
     * @brief Get the value of the Collectible object
     *
     * @return int the value of the collectible
     */
    int getValue();

    /**
     * @brief Get the id of the Collectible object
     *
     * @return int the id of the collectible
     */
    int getId();

    /**
     * @brief Get to know if an entity is dead
     *
     * @return bool true if the collectible is dead and false otherwise
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