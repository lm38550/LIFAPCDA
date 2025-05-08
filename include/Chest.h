#pragma once
#include "Vec2f.h"
#include "Utils.h"
#include "Entity.h"

class Chest : public Entity
{
private:
    int containID;
    int textureID;
    bool visible;

public:
    /**
     * @brief Get the Type Chest of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const { return CHEST_ID; }

    /**
     * @brief Construct a new Chest object
     *
     */
    Chest();

    /**
     * @brief Construct a new Chest object with the given parameters
     *
     * @param p_containID the id of the item contained in the chest
     * @param p_textureID the id of the texture of the chest
     * @param p_pos the position of the chest
     * @param p_visible the visibility of the chest
     */
    Chest(int p_containID, int p_textureID, Vec2f p_pos, bool p_visible);

    /**
     * @brief Get the Contain ID object
     *
     * @return int the id of the item contained in the chest
     */
    virtual int getContainID() const;

    /**
     * @brief Set the Contain ID object
     *
     * @param p_containID the id of the item contained in the chest
     */
    void setContainID(int p_containID);

    /**
     * @brief Get the Texture ID object
     *
     * @return int the id of the texture of the chest
     */
    int getTextureID() const;

    /**
     * @brief Get the Pos object
     *
     * @return Vec2f the position of the chest
     */
    Vec2f getPos() const;

    /**
     * @brief Get to know if the object is visible
     *
     * @return bool the visibility of the chest
     */
    virtual bool isVisible() const;

    /**
     * @brief Set the visibility of the object
     *
     * @param p_visible the visibility of the chest
     */
    void setVisible(bool p_visible);

    /**
     * @brief get to know if the entity can be walked on
     *
     * @return false
     */
    virtual bool isWalkable() const;

    /**
     * @brief Check if the chest is open
     *
     * @return bool true if the chest is open and false otherwise
     */
    bool isOpen();

    /**
     * @brief Receive an interaction from player
     *
     * @param map the map of the game
     */
    virtual void Interact(Map &map);
};