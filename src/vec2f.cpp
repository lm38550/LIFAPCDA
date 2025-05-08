#include "Vec2f.h"
#include <cassert>
#include <cmath>

Vec2f::Vec2f() : x(0.0f), y(0.0f) {}

Vec2f::Vec2f(float p_x, float p_y) : x(p_x), y(p_y) {}

Vec2f operator+(Vec2f v, Vec2f u)
{
    return Vec2f(v.x + u.x, v.y + u.y);
}

Vec2f operator-(Vec2f v, Vec2f u)
{
    return Vec2f(v.x - u.x, v.y - u.y);
}

Vec2f operator*(Vec2f v, float n)
{
    return Vec2f(v.x * n, v.y * n);
}

Vec2f operator/(Vec2f v, float n)
{
    assert(n != 0.0f);
    return Vec2f(v.x / n, v.y / n);
}

Vec2f operator+=(Vec2f v, Vec2f u)
{
    return Vec2f(v.x += u.x, v.y += u.y);
}

Vec2f operator-=(Vec2f v, Vec2f u)
{
    return Vec2f(v.x -= u.x, v.y -= u.y);
}

Vec2f operator*=(Vec2f v, float n)
{
    return Vec2f(v.x *= n, v.y *= n);
}

Vec2f operator/=(Vec2f v, float n)
{
    assert(n != 0.0f);
    return Vec2f(v.x /= n, v.y /= n);
}

bool operator==(Vec2f v, Vec2f u)
{
    return v.x == u.x && v.y == u.y;
}

bool operator!=(Vec2f v, Vec2f u)
{
    return !(v == u);
}

float distance(Vec2f v, Vec2f u)
{
    return sqrt(pow(v.x - u.x, 2) + pow(v.y - u.y, 2));
}