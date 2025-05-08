#pragma once

class Vec2f
{
public:
    /**
     * @brief The x and y coordinates of the vector
     */
    float x, y;

    /**
     * @brief Construct a new Vec2f object (default valors are 0)
     *
     */
    Vec2f();

    /**
     * @brief Construct a new Vec2f object with the parameters
     *
     * @param p_x value of the x coordinate
     * @param p_y value of the y coordinate
     */
    Vec2f(float p_x, float p_y);
};

/**
 * @brief Overload of the operator +
 *
 * @param v vector
 * @param u vector
 * @return Vec2f
 */
Vec2f operator+(Vec2f v, Vec2f u);

/**
 * @brief Overload of the operator -
 *
 * @param v vector
 * @param u vector
 * @return Vec2f
 */
Vec2f operator-(Vec2f v, Vec2f u);

/**
 * @brief Overload of the operator *
 *
 * @param v vector
 * @param n float
 * @return Vec2f
 */
Vec2f operator*(Vec2f v, float n);

/**
 * @brief Overload of the operator /
 *
 * @param v vector
 * @param n float
 * @return Vec2f
 */
Vec2f operator/(Vec2f v, float n);

/**
 * @brief Overload of the operator +=
 *
 * @param v vector
 * @param u vector
 * @return Vec2f&
 */
Vec2f operator+=(Vec2f v, Vec2f u);

/**
 * @brief Overload of the operator -=
 *
 * @param v vector
 * @param u vector
 * @return Vec2f&
 */
Vec2f operator-=(Vec2f v, Vec2f u);

/**
 * @brief Overload of the operator *=
 *
 * @param v vector
 * @param n float
 * @return Vec2f&
 */
Vec2f operator*=(Vec2f v, float n);

/**
 * @brief Overload of the operator /=
 *
 * @param v vector
 * @param n float
 * @return Vec2f&
 */
Vec2f operator/=(Vec2f v, float n);

/**
 * @brief Overload of the operator ==
 *
 * @param v vector
 * @param u vector
 * @return true if the vectors are equal false otherwise
 */
bool operator==(Vec2f v, Vec2f u);

/**
 * @brief Overload of the operator !=
 *
 * @param v vector
 * @param u vector
 * @return true if the vectors are not equal false otherwise
 */
bool operator!=(Vec2f v, Vec2f u);

/**
 * @brief Calculate the distance between two Vec2f
 *
 * @param v vector
 * @param u vector
 * @return float the distance between the two vectors
 */
float distance(Vec2f v, Vec2f u);