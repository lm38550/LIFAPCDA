#pragma once

#include "Vec2f.h"
#include "Tile.h"
#include "Door.h"

#include <vector>
class Map;

class Map;

class Entity
{
protected:
    Vec2f pos;

public:
    /**
     * @brief Get the Type of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const = 0;

    /**
     * @brief Get the Health of the Entity object
     *
     * @return crash if the entity doesn't have health
     */
    virtual int getHealth() const;

    /**
     * @brief Get the Max Health object
     *
     * @return crash if the entity doesn't have health
     */
    virtual int getMaxHealth() const;

    /**
     * @brief Construct a new Entity object
     *
     */
    Entity();

    /**
     * @brief Construct a new Entity object with the given parameters
     *
     * @param p_pos the position of the entity
     */
    Entity(Vec2f p_pos);

    /**
     * @brief Get the Pos object
     *
     * @return Vec2f the position of the entity
     */
    Vec2f getPos() const;

    /**
     * @brief see if the entity is visible
     *
     * @return true by default
     */
    bool isVisible() const;

    /**
     * @brief Set the Pos object
     *
     * @param new_pos the new position of the entity
     */
    void setPos(Vec2f new_pos);

    /**
     * @brief Exploded the Entity object
     *
     */
    virtual void exploded();

    /**
     * @brief update the Entity object
     *
     * @param dir the direction of the entity
     * @param dt the time since the last update
     * @param map the map of the game
     * @param curIndex the index of the entity in the map
     *
     * @return Vec2f(-1, -1) by default
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);

    /**
     * @brief Get to know if entity can be walked on
     *
     * @return true by default
     */
    virtual bool isWalkable() const;

    /**
     * @brief Damage the Entity object
     *
     * @param p_health the amount of health to remove
     */
    virtual void damage(int p_health);

    /**
     * @brief Get to know if an entity is dead
     *
     * @return true if the entity is dead and false otherwise
     */
    virtual bool isDead() const;

    /**
     * @brief Get the Equipped object
     *
     * @return crash if the entity doesn't have equipped
     */
    virtual int getEquipped() const;

    /**
     * @brief Set the Equipped object
     *
     * @param p_equipped the new equipped
     *
     * @return crash if the entity doesn't have equipped
     */
    virtual void setEquipped(int p_equipped);

    /**
     * @brief Get if the bomb is exploding
     *
     * @return crash if the entity isn't a bomb
     */
    virtual bool isExploding() const;

    /** @brief Get timer of Fire
     *
     * @return crash if the entity doesn't have timer
     */
    virtual float getTimer() const;

    /**
     * @brief Get the Player Dir object
     *
     * @return Vec2f the direction of the player (crash if the entity isn't a player)
     */
    virtual Vec2f getPlayerDir();

    /**
     * @brief Get the Frame Timer object
     *
     * @return crash if the entity doesn't have frame timer
     */
    virtual float getFrameTimer() const;

    /**
     * @brief Set the Frame Timer object
     *
     * @param p_frameTimer the new frame timer
     *
     * @return crash if the entity doesn't have frame timer
     */
    virtual void setFrameTimer(float p_frameTimer);

    /**
     * @brief Get the Contain ID object
     *
     * @return int the id of the item contained in the entity (crash if the entity doesn't contain an item)
     */
    virtual int getContainID() const;

    /**
     * @brief Receive an interaction from player
     *
     * @param map the map of the game
     *
     * @return do nothing by default
     */
    virtual void Interact(Map &map);
};
