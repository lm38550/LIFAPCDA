#include "Sword.h"
#include "Map.h"

Sword::Sword() : SwordDamage(SWORD_DAMAGE) {}

int Sword::getID()
{
    return ID;
}

int Sword::getSwordDamage()
{
    return SwordDamage;
}

void Sword::setSwordDamage(int p_SwordDamage)
{
    SwordDamage = p_SwordDamage;
}