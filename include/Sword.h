#pragma once

class Sword
{
private:
    int ID;
    int SwordDamage;

public:
    /**
     * @brief Construct a new Sword object
     *
     */
    Sword();

    /**
     * @brief retourne l'ID de l'objet sword
     *
     * @return int l'ID de l'objet sword
     */
    int getID();

    /**
     * @brief Get the Damage object
     *
     * @return int the damage of the sword
     */
    int getSwordDamage();

    /**
     * @brief Set the Damage object
     *
     * @param p_damage the damage of the sword
     */
    void setSwordDamage(int p_damage);
};