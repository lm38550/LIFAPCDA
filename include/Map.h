#pragma once
#include <vector>

#include "Tile.h"
#include "Chest.h"
#include "Entity.h"
#include "Door.h"
#include "Inventory.h"

class Player;

class Map
{
private:
    std::vector<std::vector<Tile>> tiles;
    std::vector<Entity *> entities;
    std::vector<Door> doors;
    Inventory inventory;
    int ID;
    int width;
    int height;

public:
    bool win;
    bool GameOver;
    /**
     * @brief Construct a new Map object
     *
     */
    Map();

    /**
     * @brief Destroy the Map object
     *
     */
    ~Map();

    /**
     * @brief Set the Tile object at the given position
     *
     * @param x the x position of the tile
     * @param y the y position of the tile
     * @param Tile the tile object
     */
    void setTile(int x, int y, const Tile &tile);

    /**
     * @brief Get the Tile object at the given position
     *
     * @param x the x position of the tile
     * @param y the y position of the tile
     *
     * @return tile the tile object
     */
    Tile getTile(int x, int y) const;

    /**
     * @brief Set the ID of the map
     *
     * @param p_ID the ID of the map
     */
    void setID(int p_ID);

    /**
     * @brief Get the ID of the map
     *
     * @return int the ID of the map
     */
    int getID() const;

    /**
     * @brief Set the width of the map
     *
     * @param p_width the width of the map
     */
    void setWidth(int p_width);

    /**
     * @brief Set the height of the map
     *
     * @param p_height the height of the map
     */
    void setHeight(int p_height);

    /**
     * @brief Get the width of the map
     *
     * @return int the width of the map
     */
    int getWidth() const;

    /**
     * @brief Get the height of the map
     *
     * @return int the height of the map
     */
    int getHeight() const;

    /**
     * @brief Add an Entity to the map
     *
     * @param entity the entity to add
     */
    void addEntity(Entity *entity);

    /**
     * @brief Add a door to the map
     *
     * @param door the door to add
     */
    void addDoor(const Door &door);

    /**
     * @brief Get the entities of the map
     *
     * @return std::vector<Entity *> the entities of the map
     */
    const std::vector<Entity *> &getEntities() const;

    /**
     * @brief Get the doors of the map
     *
     * @return std::vector<Door> the doors of the map
     */
    std::vector<Door> &getDoors();

    /**
     * @brief Get the inventory of the map
     *
     * @return Inventory the inventory of the player
     */
    Inventory &getInventory();

    /**
     * @brief Get the player health
     *
     * @return Vec2f the player health and max health
     */
    Vec2f getPlayerHealth() const;

    /**
     * @brief Get the player
     *
     * @return Player * the player
     */
    Player *getPlayer() const;

    /**
     * @brief Update the map
     *
     * @param playerDir the direction of the player
     */
    void update(Vec2f playerDir, float dt);

    /**
     * @brief whip the save
     *
     */
    void whipSave();

    /**
     * @brief save the map
     *
     */
    void saveMap();

    /**
     * @brief Draw the map
     *
     */
    void loadMap(Vec2f mapID);

    /**
     * @brief tue les entités qui doivent mourir
     *
     */
    void killEntity(int e);
};

/**
 * @brief Run the regression test for the Map class
 *
 */
void regressionTest();