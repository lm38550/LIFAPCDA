#pragma once

#include "Item.h"

class Bow : public Item
{
public:
    /**
     * @brief Construct a new Bow object with quantity
     *
     * @param quantity the quantity of arrows in the bow
     */
    Bow(int quantity);

    /**
     * @brief Get the Type Bow of the Item object
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
     * @brief Destroy the Bow object
     *
     */
    virtual ~Bow();
};