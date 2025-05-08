#pragma once
#include "Vec2f.h"

class Tile
{
private:
    Vec2f pos;
    bool walkable;
    int textureID;

public:
    /**
     * @brief Construct a new Tile object
     *
     */
    Tile();

    /**
     * @brief Construct a new Tile object
     *
     * @param p_pos the position of the tile
     * @param walk the walkable state of the tile
     * @param texID the id of the texture of the tile
     */
    Tile(Vec2f p_pos, bool walk, int texID);

    /**
     * @brief Get the Pos object
     *
     * @return Vec2f
     */
    Vec2f getPos() const;

    /**
     * @brief Get the Walkable object
     *
     * @return true if the tile is walkable and false otherwise
     */
    bool isWalkable() const;

    /**
     * @brief Get the Texture I D object
     *
     * @return int the id of the texture of the tile
     */
    int getTextureID() const;

    // void regressionTest();
};