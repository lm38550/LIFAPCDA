#pragma once
#include "Vec2f.h"

class Map;
class Door
{
private:
    int ID, destinationID;
    bool locked;
    Vec2f pos;

public:
    /**
     * @brief Construct a new Door object with the given parameters
     *
     * @param p_ID the ID of the door
     * @param p_destinationID the ID of the destination room
     * @param p_locked the locked state of the door
     * @param p_pos the position of the door
     */
    Door(int p_ID, int p_destinationID, bool p_locked, Vec2f p_pos);

    Door();

    /**
     * @brief Get the ID of the door
     *
     * @return int the ID of the door
     */
    int getID() const;

    /**
     * @brief Get the ID of the destination room
     *
     * @return int the ID of the destination room
     */
    int getDestinationID() const;

    /**
     * @brief Check if the door is locked
     *
     * @return bool true if the door is locked and false otherwise
     */
    bool isLocked() const;

    /**
     * @brief Set the locked state of the door
     *
     * @param p_locked the locked state of the door
     */
    void setLocked(bool p_locked);

    /**
     * @brief Get the position of the door
     *
     * @return Vec2f the position of the door
     */
    Vec2f getPos() const;

    /**
     * @brief Explode the door
     *
     */
    void exploded();

    /**
     * @brief Update the door
     *
     * @param map the map
     */
    void
    update(Map &map);
};