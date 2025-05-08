#pragma once

#include "Item.h"

#include <vector>

class Inventory
{
private:
    std::vector<Item *> m_items;
    int abricot;

public:
    Inventory();

    /**
     * @brief Get the Item object
     *
     * @param id the id of the item
     * @return Item* the item object
     */
    Item *getItem(int id) const;

    /**
     * @brief add item to inventory
     *
     * @param item the item to add
     */
    void addItem(Item *item);

    /**
     * @brief Add to an item the number of item
     *
     * @param id the id of the item
     * @param nb the number of item to add
     */
    void addToItem(int id, int nb);

    /**
     * @brief add nb abricot in the inventory
     *
     * @param nb the number of abricot to add
     */
    void addAbricot(int nb);

    /**
     * @brief Get the Abricot object
     *
     * @return int the number of abricot in the inventory
     */
    int getAbricot() const;

    /**
     * @brief Set the Abricot object
     *
     * @param abricot the number of abricot to set
     */
    void setAbricot(int abricot);

    /**
     * @brief Get to know if an item is in the inventory
     *
     * @param id the id of the item
     *
     * @return true if the item is in the inventory and false otherwise
     */
    bool hasItem(int id) const;

    /**
     * @brief Destroy the Inventory object
     *
     */
    ~Inventory();
};