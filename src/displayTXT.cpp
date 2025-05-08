#include <iostream>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32
#include "winTxt.h"
#include "Utils.h"
#include "Map.h"

void txtAff(WinTXT &win, const Map &map)
{
    const int width = map.getWidth();
    const int height = map.getHeight();

    win.clear();
    
    // print the map
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            win.color(i, j, COLOR_DEFAULT, 0);
            if (map.getTile(i, j).isWalkable())
            {
                win.print(i, j, ' ');
            }
            else
            {
                win.print(i, j, '#');
            }
        }
    }

    // print the entities
    for (int i = 0; i < (int)map.getEntities().size(); i++)
    {
        if (map.getEntities()[i]->isVisible())
        {
            int x = round(map.getEntities()[i]->getPos().x);
            int y = round(map.getEntities()[i]->getPos().y);
            switch (map.getEntities()[i]->type())
            {
            case ARROW_ID:
                win.color(x, y, COLOR_BLACK, 1);
                win.print(x, y, '>');
                break;
            case FIRE_ID:
                win.color(x, y, COLOR_RED, 0);
                win.print(x, y, 'F');
                break;
            case BOMB_ID:
                win.color(x, y, COLOR_BLUE, 0);
                win.print(x, y, 'B');
                break;
            case ENEMY_ID:
                win.color(x, y, COLOR_RED, 0);
                win.print(x, y, '☻');
                break;
            case CHEST_ID:
                win.color(x, y, COLOR_BROWN, 1);
                win.print(x, y, 'C');
                break;
            case PLAYER_ID:
                win.color(x, y, COLOR_GREEN, 0);
                win.print(x, y, '☺');
                break;
            }
        }
    }

    for (int i = 0; i < (int)map.getDoors().size(); i++)
    {
        int x = round(map.getDoors()[i].getPos().x);
        int y = round(map.getDoors()[i].getPos().y);
        win.print(x, y, 'Π');
    }

    int a[5][21] = {
        {'╔', '═', '1', '═', '╦', '═', '2', '═', '╦', '═', '3', '═', '╦', '═', '4', '═', '╦', '═', '5', '═', '╗'},
        {'║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║'},
        {'║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║'},
        {'║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║', ' ', ' ', ' ', '║'},
        {'╚', '═', '═', '═', '╩', '═', '═', '═', '╩', '═', '═', '═', '╩', '═', '═', '═', '╩', '═', '═', '═', '╝'}};

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 21; j++)
        {
            win.color(width + j + 2, i + 2, COLOR_DEFAULT, 0);
            win.print(width + j + 2, i + 2, a[i][j]);
        }
    if(map.GameOver)
    {
        char g[10] = "GAME OVER";
        for(int i = 0 ; i < 9; i++)
        {
            win.print(i, map.getHeight()/2, g[i]);
            win.color(i, map.getHeight()/2, COLOR_DEFAULT, 0);
        }
    }

    win.draw();
}

void displayHealth(const Map &map)
{
    Vec2f health = map.getPlayerHealth();
    if (health.x != -1)
    {
        std::string color;
        float ratio = health.x / health.y;
        if (ratio < 0)
            ratio = 0;
        if (ratio > 1)
            ratio = 1;
        if (ratio > 0.5)
            color = "\033[32m";
        else if (ratio > 0.25)
            color = "\033[33m";
        else
            color = "\033[31m";

        std::cout << "Health: [" << color;
        for (int i = 0; i < 20; i++)
        {
            if (i < ratio * 20)
            {
                std::cout << "█";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << "\033[0m]" << std::endl;
    }
}

void txtBoucle(Map &map)
{
    WinTXT win(map.getWidth() + 23, map.getHeight() + 2);

    bool playing = true;
    int c;
    do
    {
        txtAff(win, map);
        displayHealth(map);

#ifdef _WIN32
        Sleep(100);
#else
        usleep(1000);
#endif // WIN32

        c = win.getCh();
        Vec2f dir;
        switch (c)
        {
        case 'x':
            playing = false;
            break;
        case 'z':
            dir = Vec2f(0, -1);
            break;
        case 's':
            dir = Vec2f(0, 1);
            break;
        case 'd':
            dir = Vec2f(1, 0);
            break;
        case 'q':
            dir = Vec2f(-1, 0);
            break;
        /*case 'a' :
            map.entities*/
        }

        if(!map.GameOver)
        {
            map.update(dir, 0.001);
        }        

    } while (playing);
}