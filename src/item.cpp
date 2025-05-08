#include "Item.h"
#include "Map.h"

Item::Item(int quantity) : m_quantity(quantity) {}

int Item::getQuantity()
{
    return m_quantity;
}

void Item::setQuantity(int quantity)
{
    m_quantity = quantity;
}

Item::~Item() {}