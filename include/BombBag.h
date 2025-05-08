#pragma once

#include "Item.h"
#include "Utils.h"

class BombBag : public Item
{
public:
    /**
     * @brief Construct a new Bomb Bag object with quantity
     *
     * @param quantity the quantity of bombs in the bag
     */
    BombBag(int quantity);

    /**
     * @brief Get the Type Bomb Bag of the Item object
     *
     * @return int the type of the item
     */
    virtual int id();

    /**
     * @brief Use the item
     *
     * @param map the map
     */
    virtual void use(Map &map);

    /**
     * @brief Destroy the Bomb Bag object
     *
     */
    virtual ~BombBag();
};