#pragma once

class Map;

class Item
{
protected:
    int m_quantity;

public:
    /**
     * @brief Construct a new Item object with quantity
     *
     * @param quantity the quantity of the item
     */
    Item(int quantity);

    /**
     * @brief Get the Type of the Item object
     *
     * @return int the type of the item
     */
    virtual int id() = 0;

    /**
     * @brief Get the Quantity of the Item object
     *
     * @return int the quantity of the item
     */
    int getQuantity();

    /**
     * @brief Set the Quantity of the Item object
     *
     * @param quantity the quantity of the item
     */
    void setQuantity(int quantity);

    /**
     * @brief Use the item
     *
     * @param map the map
     */
    virtual void use(Map &map) = 0;

    /**
     * @brief Destroy the Item object
     *
     */
    virtual ~Item();
};