#include "Tile.h"
#include <cassert>
#include <iostream>

Tile::Tile() : pos(Vec2f()), walkable(true), textureID(0) {}

Tile::Tile(Vec2f p_pos, bool walk, int texID) : pos(p_pos), walkable(walk), textureID(texID) {}

Vec2f Tile::getPos() const
{
    return pos;
}

bool Tile::isWalkable() const
{
    return walkable;
}

int Tile::getTextureID() const
{
    return textureID;
}

/*
void Tile::regressionTest()
{
    Tile t1;
    assert(t1.getPos().x==0);
    assert(t1.getPos().y==0);
    assert(t1.getTextureID()==0);
    assert(t1.getWalkable()==true);
    Tile t2(Vec2f(5,6), false, 4);
    assert(t2.getPos().x==5);
    assert(t2.getPos().y==6);
    assert(t2.getTextureID()==4);
    assert(t2.getWalkable()==false);
    std::cout << "ALL OK";
}
*/