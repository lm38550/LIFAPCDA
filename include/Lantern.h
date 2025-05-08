#pragma once

#include "Item.h"

class Lantern : public Item
{
public:
    /**
     * @brief Construct a new Lantern object with quantity
     *
     * @param quantity the quantity of lanterns
     */
    Lantern(int quantity);

    /**
     * @brief Get the Type Lantern of the Item object
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
     * @brief Destroy the Lantern object
     *
     */
    virtual ~Lantern();
};