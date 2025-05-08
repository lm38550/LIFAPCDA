#include "Inventory.h"
#include "BombBag.h"
#include "Bow.h"
#include "Lantern.h"

Inventory::Inventory() : m_items(), abricot(0) {}

Item *Inventory::getItem(int id) const
{
    if (id < 0 || id >= (int)m_items.size())
    {
        return nullptr;
    }
    return m_items[id];
}

void Inventory::addItem(Item *item)
{
    m_items.push_back(item);
}

void Inventory::addToItem(int id, int nb)
{
    for (int i = 0; i < (int)m_items.size(); i++)
    {
        if (m_items[i]->id() == id)
        {
            m_items[i]->setQuantity(m_items[i]->getQuantity() + nb);
            return;
        }
    }
}

void Inventory::addAbricot(int nb)
{
    abricot += nb;
}

int Inventory::getAbricot() const
{
    return abricot;
}

void Inventory::setAbricot(int abricot)
{
    this->abricot = abricot;
}

bool Inventory::hasItem(int id) const
{
    for (int i = 0; i < (int)m_items.size(); i++)
    {
        if (m_items[i]->id() == id)
        {
            return true;
        }
    }
    return false;
}

Inventory::~Inventory()
{
    for (int i = 0; i < (int)m_items.size(); i++)
    {
        delete m_items[i];
    }
}