#pragma once
#include "Entity.h"
#include "Door.h"
#include "Map.h"
#include "Utils.h"
#include "Sword.h"
#include "Inventory.h"

class Player : public Entity
{
private:
    int life, maxLife, equipped;
    float frameTimer, invincibilityTime;
    bool isWalking;
    Vec2f dir;
    Sword sword;

public:
    /**
     * @brief Get the Type Player of the Entity object
     *
     * @return int the type of the entity
     */
    virtual int type() const { return PLAYER_ID; }

    /**
     * @brief Construct a new Player object
     *
     */
    Player();

    /**
     * @brief Construct a new Player object with the given parameters
     *
     * @param p_life the life of the player
     * @param p_maxLife the max life of the player
     * @param p_equipped the equipped item of the player
     * @param p_pos the position of the player
     */
    Player(int p_life, int p_maxLife, int p_equipped, Vec2f p_pos, Vec2f dir);

    /**
     * @brief Get the Life object
     *
     * @return int the life of the player
     */
    virtual int getHealth() const;

    /**
     * @brief Set the Life object
     *
     * @param p_life the life of the player
     */
    void setHealth(int p_life);

    /**
     * @brief Get the Max Life object
     *
     * @return int the max life of the player
     */
    virtual int getMaxHealth() const;

    /**
     * @brief Set the Max Life object
     *
     * @param p_maxLife the max life of the player
     */
    void setMaxHealth(int p_maxLife);

    /**
     * @brief heal the player
     *
     * @param p_health the health to add to the player
     */
    void heal(int p_health);

    /**
     * @brief Get the Equipped object
     *
     * @return int the equipped item of the player
     */
    virtual int getEquipped() const;

    /**
     * @brief Set the Equipped object
     *
     * @param p_equipped the equipped item of the player
     */
    virtual void setEquipped(int p_equipped);

    /**
     * @brief update the Player object
     *
     * @param p_life the life of the player
     */
    virtual Vec2f update(Vec2f dir, float dt, Map &map, int curIndex);

    /**
     * @brief Get to know if entity can be walked on
     *
     * @return false
     */
    virtual bool isWalkable() const;

    /**
     * @brief Get the Is Walking object
     *
     * @return true if the player is walking and false otherwise
     */
    virtual bool getIsWalking() const;

    /**
     * @brief Set the Is Walking object
     *
     * @param p_isWalking true if the player is walking and false otherwise
     */
    virtual void setIsWalking(bool p_isWalking);

    /**
     * @brief Get the Frame Timer object
     *
     * @return float the frame timer of the player
     */
    float getFrameTimer() const;

    /**
     * @brief Set the Frame Timer object
     *
     * @param p_frameTimer the frame timer of the player
     */
    void setFrameTimer(float p_frameTimer);

    /**
     * @brief do damage to the player
     *
     * @param p_health the health to remove to the player
     */
    virtual void damage(int p_health);

    /**
     * @brief get to know is the playter is dead
     *
     * @return true if the player is dead and false otherwise
     */
    virtual bool isDead() const;

    /**
     * @brief Get the Sword object
     *
     * @return Sword the sword of the player
     */
    Sword getSword() const;

    /**
     * @brief Use the sword to attack
     *
     * @param entities a vector of Entity pointers that contains all the entities
     */
    void attack(const std::vector<Entity *> &entities);

    /**
     * @brief Get the player direction
     *
     * @return Vec2f the direction of the player
     */
    virtual Vec2f getPlayerDir();

    /**
     * @brief Make the player interact with the map
     *
     * @param map a Map object that contains the map
     */
    void Interacting(Map &map);

    /**
     * @brief destroy the player
     *
     */
    ~Player();
};