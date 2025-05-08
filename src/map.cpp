#include <cassert>
#include <iostream>
#include <fstream>
#include <iostream>

#include "Map.h"
#include "Enemy.h"
#include "Utils.h"
#include "Player.h"
#include "Chest.h"
#include "Collectible.h"
#include "Enemy.h"
#include "Arrow.h"
#include "Fire.h"
#include "Bomb.h"
#include "Door.h"

// external library
#include "json.hpp"

using json = nlohmann::json;

Map::Map() : ID(0), width(0), height(0), win(false), GameOver(false)
{
    whipSave();
    loadMap(Vec2f(0, 0));
}

Map::~Map() {}

void Map::setTile(int x, int y, const Tile &tile)
{
    tiles[x][y] = tile;
}

Tile Map::getTile(int x, int y) const
{
    return tiles[x][y];
}

void Map::setID(int p_ID)
{
    ID = p_ID;
}

int Map::getID() const
{
    return ID;
}

void Map::setWidth(int p_width)
{
    width = p_width;
}

void Map::setHeight(int p_height)
{
    height = p_height;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

void Map::addEntity(Entity *entity)
{
    entities.push_back(entity);
}

void Map::addDoor(const Door &door)
{
    doors.push_back(door);
}

const std::vector<Entity *> &Map::getEntities() const
{
    return entities;
}

std::vector<Door> &Map::getDoors()
{
    return doors;
}

Inventory &Map::getInventory()
{
    return inventory;
}

Vec2f Map::getPlayerHealth() const
{
    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (entities[i]->type() == PLAYER_ID)
        {
            return Vec2f(entities[i]->getHealth(), entities[i]->getMaxHealth());
        }
    }
    return Vec2f(-1, -1);
}

Player *Map::getPlayer() const
{
    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (entities[i]->type() == PLAYER_ID)
        {
            return (Player *)entities[i];
        }
    }
    return nullptr;
}

void Map::killEntity(int e)
{
    if (entities[e]->type() == PLAYER_ID)
    {
        GameOver = true;
    }
    entities.erase(entities.begin() + e);
}

void Map::update(Vec2f playerDir, float dt)
{
    Vec2f temp(-1, -1);

    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (entities[i]->type() == PLAYER_ID)
            temp = entities[i]->update(playerDir, dt, *this, i);
        else
            entities[i]->update(playerDir, dt, *this, i);
        if (entities[i]->isDead())
        {
            killEntity(i);
        }
    }
    for (int i = 0; i < (int)doors.size(); i++)
    {
        doors[i].update(*this);
    }
    if (temp != Vec2f(-1, -1))
    {
        saveMap();
        loadMap(temp);
    }
}

void Map::whipSave()
{
    std::fstream save("data/save.json");

    if (save.is_open())
    {
        // delete file
        save.close();
        std::remove("data/save.json");
    }
    save.close();
    std::fstream save2("data/save.json", std::ios::out);
    save2 << "[]" << std::endl;
    save2.close();
}

void Map::saveMap()
{
    std::fstream save("data/save.json");
    if (!save.is_open())
    {
        whipSave();
    }

    json json = json::parse(save);
    save.close();
    bool clear = true;
    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (entities[i]->type() == ENEMY_ID)
        {
            clear = false;
            break;
        }
    }

    int Key = -1;

    for (int i = 0; i < (int)json.size(); i++)
    {
        if (json[i]["id"] == ID)
        {
            Key = i;
            break;
        }
    }
    if (Key == -1)
    {
        Key = json.size();
    }
    json[Key]["clear"] = clear;
    json[Key]["id"] = ID;
    json[Key]["Entities"] = json::array();

    int entityKey = 0;
    for (int i = 0; i < (int)entities.size(); i++)
    {
        if (entities[i]->type() == BOMB_ID)
        {
            json[Key]["Entities"][entityKey]["type"] = "Bomb";
            json[Key]["Entities"][entityKey]["x"] = entities[i]->getPos().x;
            json[Key]["Entities"][entityKey]["y"] = entities[i]->getPos().y;

            entityKey++;
        }
        else if (entities[i]->type() == CHEST_ID)
        {
            json[Key]["Entities"][entityKey]["type"] = "Chest";
            json[Key]["Entities"][entityKey]["id"] = entities[i]->getContainID();
            json[Key]["Entities"][entityKey]["texture"] = 0;
            json[Key]["Entities"][entityKey]["x"] = entities[i]->getPos().x;
            json[Key]["Entities"][entityKey]["y"] = entities[i]->getPos().y;
            json[Key]["Entities"][entityKey]["visible"] = entities[i]->isVisible();

            entityKey++;
        }
        else if (entities[i]->type() == COLLECTIBLE_ID)
        {
            json[Key]["Entities"][entityKey]["type"] = "Collectible";
            json[Key]["Entities"][entityKey]["x"] = entities[i]->getPos().x;
            json[Key]["Entities"][entityKey]["y"] = entities[i]->getPos().y;
            json[Key]["Entities"][entityKey]["value"] = ((Collectible *)entities[i])->getValue();
            json[Key]["Entities"][entityKey]["id"] = ((Collectible *)entities[i])->getId();

            entityKey++;
        }
    }

    // push the save
    std::ofstream saves("data/save.json");
    saves << json.dump(4);
    saves.close();
}

void Map::loadMap(Vec2f mapID)
{
    std::ifstream maps("data/maps.json");
    if (!maps.is_open())
    {
        std::cout << "Error: file not found" << std::endl;
        exit(1);
    }

    std::ifstream save("data/save.json");
    if (!save.is_open())
    {
        whipSave();
    }

    int saveKey = -1;
    json jSave = json::parse(save);
    save.close();

    for (int i = 0; i < (int)jSave.size(); i++)
    {
        if (jSave.at(i).at("id") == mapID.y)
        {
            saveKey = i;
            break;
        }
    }

    json json = json::parse(maps);
    maps.close();

    ID = mapID.y;
    width = json.at(ID).at("width");
    height = json.at(ID).at("height");

    tiles.clear();

    for (int i = 0; i < width; i++)
    {
        tiles.push_back(std::vector<Tile>());
        for (int j = 0; j < height; j++)
        {
            tiles[i].push_back(Tile(Vec2f(i, j), (json.at(ID).at("tiles").at(j).at(i) == 1), 0));
        }
    }

    Entity *player;
    bool first = false;
    if (!entities.empty())
        player = entities[0];
    else
    {
        first = true;
        player = new Player(10, 10, -1, Vec2f(4, 4), Vec2f(0, 1));
    }
    entities.clear();

    entities.push_back(player);

    if (saveKey == -1)
        for (int i = 0; i < (int)json.at(ID).at("Entities").size(); i++)
        {
            if (json.at(ID).at("Entities").at(i).at("type") == "Chest")
                entities.push_back(new Chest(
                    json.at(ID).at("Entities").at(i).at("id"),
                    json.at(ID).at("Entities").at(i).at("texture"),
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y")),
                    json.at(ID).at("Entities").at(i).at("visible")));
            else if (json.at(ID).at("Entities").at(i).at("type") == "Enemy")
            {
                entities.push_back(new Enemy(
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y")),
                    json.at(ID).at("Entities").at(i).at("health"), 0.0f));
            }
            else if (json.at(ID).at("Entities").at(i).at("type") == "Arrow")
            {
                entities.push_back(new Arrow(
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y")),
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("vx"),
                        json.at(ID).at("Entities").at(i).at("vy"))));
            }
            else if (json.at(ID).at("Entities").at(i).at("type") == "Fire")
            {
                entities.push_back(new Fire(
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y")),
                    json.at(ID).at("Entities").at(i).at("timer")));
            }
            else if (json.at(ID).at("Entities").at(i).at("type") == "Bomb")
            {
                entities.push_back(new Bomb(
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y"))));
            }
            else if (json.at(ID).at("Entities").at(i).at("type") == "Collectible")
            {
                entities.push_back(new Collectible(
                    Vec2f(
                        json.at(ID).at("Entities").at(i).at("x"),
                        json.at(ID).at("Entities").at(i).at("y")),
                    json.at(ID).at("Entities").at(i).at("value"),
                    json.at(ID).at("Entities").at(i).at("id")));
            }
        }
    else
    {
        if (!jSave.at(saveKey).at("clear"))
            for (int i = 0; i < (int)json.at(ID).at("Entities").size(); i++)
            {
                if (json.at(ID).at("Entities").at(i).at("type") == "Enemy")
                {
                    entities.push_back(new Enemy(
                        Vec2f(
                            json.at(ID).at("Entities").at(i).at("x"),
                            json.at(ID).at("Entities").at(i).at("y")),
                        json.at(ID).at("Entities").at(i).at("health"), 0.0f));
                }
            }

        for (int i = 0; i < (int)jSave.at(saveKey).at("Entities").size(); i++)
        {
            if (jSave.at(saveKey).at("Entities").at(i).at("type") == "Bomb")
            {
                entities.push_back(new Bomb(
                    Vec2f(
                        jSave.at(saveKey).at("Entities").at(i).at("x"),
                        jSave.at(saveKey).at("Entities").at(i).at("y"))));
            }
            else if (jSave.at(saveKey).at("Entities").at(i).at("type") == "Chest")
            {
                entities.push_back(new Chest(
                    jSave.at(saveKey).at("Entities").at(i).at("id"),
                    jSave.at(saveKey).at("Entities").at(i).at("texture"),
                    Vec2f(
                        jSave.at(saveKey).at("Entities").at(i).at("x"),
                        jSave.at(saveKey).at("Entities").at(i).at("y")),
                    jSave.at(saveKey).at("Entities").at(i).at("visible")));
            }
            else if (jSave.at(saveKey).at("Entities").at(i).at("type") == "Collectible")
            {
                entities.push_back(new Collectible(
                    Vec2f(
                        jSave.at(saveKey).at("Entities").at(i).at("x"),
                        jSave.at(saveKey).at("Entities").at(i).at("y")),
                    jSave.at(saveKey).at("Entities").at(i).at("value"),
                    jSave.at(saveKey).at("Entities").at(i).at("id")));
            }
        }
    }

    doors.clear();
    int startIndex;
    for (int i = 0; i < (int)json.at(ID).at("Doors").size(); i++)
    {
        if (json.at(ID).at("Doors").at(i).at("id") == mapID.x)
            startIndex = i;
        doors.push_back(Door(
            json.at(ID).at("Doors").at(i).at("id"),
            json.at(ID).at("Doors").at(i).at("destination"),
            true,
            Vec2f(
                json.at(ID).at("Doors").at(i).at("x"),
                json.at(ID).at("Doors").at(i).at("y"))));
    }
    if (!first)
        entities[0]->setPos(Vec2f(json.at(ID).at("Doors").at(startIndex).at("x"), json.at(ID).at("Doors").at(startIndex).at("y")) + (entities[0]->getPlayerDir()));
}
// void regressionTest()
// {
// Map map(1, 10, 10);
// assert(map.getID() == 1);
// assert(map.getWidth() == 10);
// assert(map.getHeight() == 10);
// std::cout << "Map height: " << height << std::endl;
// assert(map.getTile(0, 0).isWalkable());
// assert(map.getTile(0, 0).getTextureID() == 0);
// assert(map.getTile(0, 0).getPos().x == 0);
// assert(map.getTile(0, 0).getPos().y == 0);
// assert(map.getTile(5, 5).isWalkable());
// assert(map.getTile(5, 5).getTextureID() == 0);
// assert(map.getTile(5, 5).getPos().x == 5);
// assert(map.getTile(5, 5).getPos().y == 5);
// assert(map.getTile(9, 9).isWalkable());
// assert(map.getTile(9, 9).getTextureID() == 0);
// assert(map.getTile(9, 9).getPos().x == 9);
// assert(map.getTile(9, 9).getPos().y == 9);
// map.setTile(5, 5, Tile(Vec2f(5, 5), false, 1));
// assert(!map.getTile(5, 5).isWalkable());
// assert(map.getTile(5, 5).getTextureID() == 1);
// assert(map.getTile(5, 5).getPos().x == 5);
// assert(map.getTile(5, 5).getPos().y == 5);
// map.addEntity(new Enemy(Vec2f(5, 5), 8, 1.0f));
// assert(map.getEntities().size() == 1);
// assert(map.getEntities()[0]->getPos().x == 5);
// assert(map.getEntities()[0]->getPos().y == 5);
// assert(map.getEntities()[0]->getHealth() == 8);
// assert(map.getEntities()[0]->getMaxHealth() == 8);
// }
