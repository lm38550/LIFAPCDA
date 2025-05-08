#include "DisplaySDL.h"
#include "Player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <Collectible.h>
#include <iostream>

int getRefreshRate(SDL_Window *window)
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

Vec2f recenter(Vec2f pos, const Map &map)
{
    return Vec2f(pos.x + (TILE_SIZE / 2.0f), pos.y + (TILE_SIZE / 2.0f));
}

void drawMap(Map &map, SDL_Renderer *renderer)
{
    SDL_Surface *map_image = IMG_Load("assets/img/sol.png");
    if (map_image == NULL)
    {
        std::cout << "Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_Texture *texture;
    texture = SDL_CreateTextureFromSurface(renderer, map_image);
    // draw the map
    for (int i = 0; i < map.getWidth(); i++)
    {
        for (int j = 0; j < map.getHeight(); j++)
        {
            SDL_Rect src, dest;
            dest.x = (i * TILE_SIZE) - TILE_SIZE / 2;
            dest.y = (j * TILE_SIZE) - TILE_SIZE / 2;
            dest.w = TILE_SIZE;
            dest.h = TILE_SIZE;
            src.w = FRAME_SIZE;
            src.h = FRAME_SIZE;
            if (map.getTile(i, j).isWalkable())
            {
                src.x = 3 * FRAME_SIZE;
                src.y = 4 * FRAME_SIZE;
            }
            else
            {
                src.x = 3 * FRAME_SIZE;
                src.y = 1 * FRAME_SIZE;
            }
            Vec2f pos = recenter(Vec2f(dest.x, dest.y), map);
            dest.x = pos.x;
            dest.y = pos.y;
            SDL_RenderCopy(renderer, texture, &src, &dest);
        }
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(map_image);

    // draw doors brown
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);
    for (int i = 0; i < (int)map.getDoors().size(); i++)
    {
        if (map.getDoors()[i].isLocked())
        {
            SDL_Rect dest;
            dest.x = (map.getDoors()[i].getPos().x * TILE_SIZE) - TILE_SIZE / 2;
            dest.y = (map.getDoors()[i].getPos().y * TILE_SIZE) - TILE_SIZE / 2;
            dest.w = TILE_SIZE;
            dest.h = TILE_SIZE;
            Vec2f pos = recenter(Vec2f(dest.x, dest.y), map);
            dest.x = pos.x;
            dest.y = pos.y;
            SDL_RenderFillRect(renderer, &dest);
        }
    }
}

void DrawHUD(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *fontMini, int health, int maxHealth, Map &map)
{
    // draw life bar
    SDL_Color color = {255, 0, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, ("Health: " + std::to_string(health) + "/" + std::to_string(maxHealth)).c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    SDL_Rect rect2;
    rect2.x = 0;
    rect2.y = rect.h;
    rect2.w = 210;
    rect2.h = 30;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect2);
    float ratio = (float)health / (float)maxHealth;
    rect.x = 5;
    rect.y = rect.h + 5;
    rect.w = 200 * ratio;
    rect.h = 20;
    if (ratio > 0.5)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    else if (ratio > 0.25)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    rect.x = rect.w + 5;
    rect.w = 200 - rect.w;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // draw money
    surface = TTF_RenderText_Solid(font, ("Abricot: " + std::to_string(map.getInventory().getAbricot())).c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x = SDL_WINDOW_WIDTH - (surface->w + 2);
    rect.y = 0;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    // draw inventory
    rect.x = (SDL_WINDOW_WIDTH / 2) - 51;
    rect.y = SDL_WINDOW_HEIGHT - 34;
    rect.w = 3 * 34;
    rect.h = 34;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &rect);
    int equiped = map.getEntities()[0]->getEquipped();
    if (equiped != -1)
    {
        rect.x += equiped * 34;
        rect.w = 34;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
    rect.y = SDL_WINDOW_HEIGHT - 33;
    rect.w = 32;
    rect.h = 32;
    for (int i = 0; i < 3; i++)
    {
        int n = -1;
        rect.x = (SDL_WINDOW_WIDTH / 2) - 50 + i * 34;
        if (map.getInventory().getItem(i) == nullptr)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
            SDL_RenderFillRect(renderer, &rect);
        }
        else
        {
            SDL_Surface *objet_image = IMG_Load("assets/img/arrow.png");
            SDL_Texture *texture_obj;
            SDL_Rect src;
            n = map.getInventory().getItem(i)->getQuantity();
            texture_obj = SDL_CreateTextureFromSurface(renderer, objet_image);
            switch (map.getInventory().getItem(i)->id())
            {
            case BOMBBAG_ID:
                src.x = 0;
                src.y = 1 * FRAME_SIZE;
                src.w = FRAME_SIZE;
                src.h = FRAME_SIZE;
                break;
            case BOW_ID:
                src.x = 2 * FRAME_SIZE;
                src.y = 0;
                src.w = FRAME_SIZE;
                src.h = FRAME_SIZE;
                break;
            case LANTERN_ID:
                src.x = 2 * FRAME_SIZE;
                src.y = 2 * FRAME_SIZE;
                src.w = FRAME_SIZE;
                src.h = FRAME_SIZE;
                break;
            }
            SDL_RenderCopy(renderer, texture_obj, &src, &rect);
            SDL_DestroyTexture(texture_obj);
            SDL_FreeSurface(objet_image);
        }
        if (n != -1)
        {
            SDL_Color black = {0, 0, 0, 255};
            SDL_Rect rect3;
            surface = TTF_RenderText_Solid(fontMini, std::to_string(n).c_str(), black);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            rect3.x = rect.x + 32 - (surface->w);
            rect3.y = rect.y + 32 - (surface->h);
            rect3.w = surface->w;
            rect3.h = surface->h;
            SDL_RenderCopy(renderer, texture, NULL, &rect3);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
}

void DrawGameOver(SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color color = {255, 0, 0};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "Game Over !", color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = SDL_WINDOW_WIDTH / 2 - text_surface->w / 2;
    text_rect.y = SDL_WINDOW_HEIGHT / 2 - text_surface->h / 2;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void DrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

void DrawSword(SDL_Renderer *renderer, Map &map, float x, float y, Vec2f PlayerDir)
{
    SDL_Surface *item_image = IMG_Load("assets/img/arrow.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, item_image);
    SDL_Rect src, dest;
    SDL_Point point;
    src.x = 3 * FRAME_SIZE;
    src.y = 3 * FRAME_SIZE;
    src.w = FRAME_SIZE;
    src.h = FRAME_SIZE;
    dest.w = 4 + TILE_SIZE * 0.6;
    dest.h = 4 + TILE_SIZE * 0.6;
    point.x = dest.w / 2;
    point.y = dest.h / 2;
    if (PlayerDir == Vec2f(1, 0))
    {
        dest.x = (TILE_SIZE * 0.6) + x - (TILE_SIZE * 0.6 / 2);
        dest.y = 42 + y - (TILE_SIZE * 0.6);
        SDL_RenderCopyEx(renderer, texture, &src, &dest, 270, &point, SDL_FLIP_NONE);
    }
    if (PlayerDir == Vec2f(-1, 0))
    {
        dest.w = TILE_SIZE * 0.6;
        dest.x = 1 + x - 3.2 * (TILE_SIZE * 0.6 / 2);
        dest.y = 19 + y - (TILE_SIZE * 0.6 / 2);
        SDL_RenderCopyEx(renderer, texture, &src, &dest, 90, &point, SDL_FLIP_HORIZONTAL);
    }
    if (PlayerDir == Vec2f(0, 1))
    {
        dest.x = -2 + x - (TILE_SIZE * 0.6 / 2);
        dest.y = (TILE_SIZE * 0.6) + y - (TILE_SIZE * 0.6 / 2);
        SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, &point, SDL_FLIP_NONE);
    }
    if (PlayerDir == Vec2f(0, -1))
    {
        dest.x = -19 + x - (TILE_SIZE * 0.6 / 2);
        dest.y = -(TILE_SIZE * 0.6) + y - (TILE_SIZE * 0.6 / 2);
        SDL_RenderCopyEx(renderer, texture, &src, &dest, 180, &point, SDL_FLIP_HORIZONTAL);
    }
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(item_image);
}

void DrawAttack(SDL_Renderer *renderer, Map &map, bool isUsingSword, bool isUsingItem)
{
    SDL_Surface *player_image = IMG_Load("assets/img/char.png");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, player_image);
    SDL_Rect src, dest;
    Vec2f pos = recenter(map.getPlayer()->getPos() * TILE_SIZE, map);
    Vec2f playerDir = map.getPlayer()->getPlayerDir();
    if (playerDir == Vec2f(1, 0))
        src.x = 1 * FRAME_SIZE;
    if (playerDir == Vec2f(-1, 0))
        src.x = 2 * FRAME_SIZE;
    if (playerDir == Vec2f(0, 1))
        src.x = 0 * FRAME_SIZE;
    if (playerDir == Vec2f(0, -1))
        src.x = 3 * FRAME_SIZE;
    src.y = 0 * FRAME_SIZE;
    src.w = FRAME_SIZE;
    src.h = FRAME_SIZE;
    dest.x = pos.x - (TILE_SIZE * 0.6 / 2);
    dest.y = pos.y - (TILE_SIZE * 0.6 / 2);
    dest.w = TILE_SIZE * 0.6;
    dest.h = TILE_SIZE * 0.6;

    if (isUsingItem && map.getEntities()[0]->getEquipped() != -1)
    {
        Item *item = map.getInventory().getItem(map.getEntities()[0]->getEquipped());
        if (item->id() == LANTERN_ID)
            src.y = 5 * FRAME_SIZE;
        if (item->id() == BOW_ID)
            src.y = 6 * FRAME_SIZE;
    }
    if (isUsingSword)
    {
        src.y = 4 * FRAME_SIZE;
        DrawSword(renderer, map, pos.x, pos.y, playerDir);
    }
    SDL_RenderCopy(renderer, texture, &src, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(player_image);
}

void DrawPlayer(SDL_Renderer *renderer, int x, int y, float dt, Map &map)
{
    int frameSelection;
    SDL_Surface *player_image = IMG_Load("assets/img/char.png");
    SDL_Texture *texture;
    SDL_Rect src, dest;
    Vec2f playerDir = map.getPlayer()->getPlayerDir();
    texture = SDL_CreateTextureFromSurface(renderer, player_image);
    if (playerDir == Vec2f(1, 0))
        frameSelection = 1;
    if (playerDir == Vec2f(-1, 0))
        frameSelection = 2;
    if (playerDir == Vec2f(0, 1))
        frameSelection = 0;
    if (playerDir == Vec2f(0, -1))
        frameSelection = 3;
    map.getPlayer()->setFrameTimer(map.getPlayer()->getFrameTimer() + dt);
    float timer = map.getPlayer()->getFrameTimer();
    if (map.getPlayer()->getIsWalking())
    {
        if (timer > 0.4f || timer < 0.0f)
        {
            map.getPlayer()->setFrameTimer(0.0f);
        }
        if (timer < 0.1)
        {
            src.y = 0 * FRAME_SIZE;
        }
        else if (timer < 0.2)
        {
            src.y = 2 * FRAME_SIZE;
        }
        else if (timer < 0.3)
        {
            src.y = 1 * FRAME_SIZE;
        }
        else
        {
            src.y = 3 * FRAME_SIZE;
        }
    }
    else
    {
        if (timer > 0.6f || timer < 0.0f)
        {
            map.getPlayer()->setFrameTimer(0.0f);
        }
        if (timer < 0.3)
        {
            src.y = 0 * FRAME_SIZE;
        }
        else
        {
            src.y = 1 * FRAME_SIZE;
        }
    }
    src.x = frameSelection * FRAME_SIZE;
    src.w = FRAME_SIZE;
    src.h = FRAME_SIZE;
    dest.x = x - (TILE_SIZE * 0.6 / 2);
    dest.y = y - (TILE_SIZE * 0.6 / 2);
    dest.w = TILE_SIZE * 0.6;
    dest.h = TILE_SIZE * 0.6;
    SDL_RenderCopy(renderer, texture, &src, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(player_image);
}

void DrawEnemy(SDL_Renderer *renderer, int x, int y, Entity *entity, float dt, Map &map)
{
    SDL_Surface *enemy_image = IMG_Load("assets/img/slime.png");
    SDL_Texture *texture;
    SDL_Rect src, dest;
    texture = SDL_CreateTextureFromSurface(renderer, enemy_image);
    src.w = FRAME_SIZE;
    src.h = FRAME_SIZE;
    dest.x = x - (TILE_SIZE * 0.8 / 2);
    dest.y = y - (TILE_SIZE * 0.8 / 2);
    dest.w = TILE_SIZE * 0.8;
    dest.h = TILE_SIZE * 0.8;
    entity->setFrameTimer(entity->getFrameTimer() + dt);
    float timer = entity->getFrameTimer();
    if (timer > 0.8f || timer < 0.0f)
    {
        entity->setFrameTimer(0.0f);
    }
    if (timer < 0.1)
    {
        src.x = 0 * FRAME_SIZE;
        src.y = 0 * FRAME_SIZE;
    }
    else if (timer < 0.2)
    {
        src.x = 1 * FRAME_SIZE;
        src.y = 0 * FRAME_SIZE;
    }
    else if (timer < 0.3)
    {
        src.x = 2 * FRAME_SIZE;
        src.y = 0 * FRAME_SIZE;
    }
    else if (timer < 0.4)
    {
        src.x = 3 * FRAME_SIZE;
        src.y = 0 * FRAME_SIZE;
    }
    else if (timer < 0.5)
    {
        src.x = 0 * FRAME_SIZE;
        src.y = 1 * FRAME_SIZE;
    }
    else if (timer < 0.6)
    {
        src.x = 1 * FRAME_SIZE;
        src.y = 1 * FRAME_SIZE;
    }
    else if (timer < 0.7)
    {
        src.x = 2 * FRAME_SIZE;
        src.y = 1 * FRAME_SIZE;
    }
    else
    {
        src.x = 3 * FRAME_SIZE;
        src.y = 1 * FRAME_SIZE;
    }

    SDL_RenderCopy(renderer, texture, &src, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(enemy_image);
}

void DrawEntity(SDL_Renderer *renderer, int x, int y, Entity *entity, Map &map)
{
    SDL_Surface *entity_image = IMG_Load("assets/img/arrow.png");
    SDL_Texture *texture;
    SDL_Rect src, dest;
    SDL_Point point;
    Vec2f PlayerDir = map.getPlayer()->getPlayerDir();
    float timer = 0;
    texture = SDL_CreateTextureFromSurface(renderer, entity_image);
    if ((entity->type() == FIRE_ID) || (entity->type() == BOMB_ID))
        timer = entity->getTimer();
    src.w = FRAME_SIZE;
    src.h = FRAME_SIZE;
    dest.x = x - (TILE_SIZE * 0.8 / 2);
    dest.y = y - (TILE_SIZE * 0.8 / 2);
    dest.w = TILE_SIZE * 0.8;
    dest.h = TILE_SIZE * 0.8;
    switch (entity->type())
    {
    case CHEST_ID:
        if (entity->getContainID() == -1)
        {
            src.x = 1 * FRAME_SIZE;
        }
        else
        {
            src.x = 0;
        }
        src.y = 3 * FRAME_SIZE;
        break;
    case BOMB_ID:
        if (entity->isExploding())
        {
            src.x = 3 * FRAME_SIZE;
            src.y = 1 * FRAME_SIZE;
            dest.x = x - (TILE_SIZE * 4 / 2);
            dest.y = y - (TILE_SIZE * 4.5 / 2);
            dest.w = TILE_SIZE * 4;
            dest.h = TILE_SIZE * 4;
        }
        else
        {
            int image_bomb;
            if (timer > 1.5f)
            {
                image_bomb = 0;
            }
            else if (timer > 0.75f)
            {
                image_bomb = 1;
            }
            else
            {
                image_bomb = 2;
            }
            src.x = image_bomb * FRAME_SIZE;
            src.y = 1 * FRAME_SIZE;
        }
        break;
    case FIRE_ID:
        int image_fire;
        if (timer > 1.5f)
        {
            image_fire = 0;
        }
        else if (timer > 0.75f)
        {
            image_fire = 1;
        }
        else
        {
            image_fire = 2;
        }
        src.x = image_fire * FRAME_SIZE;
        src.y = 4 * FRAME_SIZE;
        break;
    case ARROW_ID:
        src.x = 0;
        src.y = 0;
        point.x = dest.h / 2;
        point.y = dest.w / 2;
        if (PlayerDir == Vec2f(1, 0))
            SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, &point, SDL_FLIP_NONE);
        if (PlayerDir == Vec2f(-1, 0))
            SDL_RenderCopyEx(renderer, texture, &src, &dest, 180, &point, SDL_FLIP_NONE);
        if (PlayerDir == Vec2f(0, 1))
            SDL_RenderCopyEx(renderer, texture, &src, &dest, 90, &point, SDL_FLIP_NONE);
        if (PlayerDir == Vec2f(0, -1))
            SDL_RenderCopyEx(renderer, texture, &src, &dest, 270, &point, SDL_FLIP_NONE);
        break;
    case COLLECTIBLE_ID:
        if (((Collectible *)entity)->getId() == COLLECTIBLE_HEALTH)
        {
            src.x = 2 * FRAME_SIZE;
            src.y = 3 * FRAME_SIZE;
        }
        else if (((Collectible *)entity)->getId() == COLLECTIBLE_ABRICOT)
        {
            src.x = 3 * FRAME_SIZE;
            src.y = 0 * FRAME_SIZE;
        }
        else if (((Collectible *)entity)->getId() == COLLECTIBLE_BOMB)
        {
            src.x = 3 * FRAME_SIZE;
            src.y = 4 * FRAME_SIZE;
        }
        else if (((Collectible *)entity)->getId() == COLLECTIBLE_ARROW)
        {
            src.x = 0 * FRAME_SIZE;
            src.y = 2 * FRAME_SIZE;
        }
        else if (((Collectible *)entity)->getId() == COLLECTIBLE_OIL)
        {
            src.x = 1 * FRAME_SIZE;
            src.y = 2 * FRAME_SIZE;
        }
        else if (((Collectible *)entity)->getId() == COLLECTIBLE_CROWN)
        {
            src.x = 3 * FRAME_SIZE;
            src.y = 2 * FRAME_SIZE;
        }
        break;

    default:
        break;
    }
    if (entity->type() != ARROW_ID)
        SDL_RenderCopy(renderer, texture, &src, &dest);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(entity_image);
}

void drawEntities(Map &map, float deltaTime, bool isUsingItem, bool isUsingSword, SDL_Renderer *renderer)
{
    // draw the entities
    if (map.getPlayer() != nullptr)
    {
        for (int i = 0; i < (int)map.getEntities().size(); i++)
        {
            Vec2f pos = recenter(map.getEntities()[i]->getPos() * TILE_SIZE, map);
            switch (map.getEntities()[i]->type())
            {
            case ARROW_ID:
                DrawEntity(renderer, pos.x, pos.y, map.getEntities()[i], map);
                break;
            case FIRE_ID:
                DrawEntity(renderer, pos.x, pos.y, map.getEntities()[i], map);
                break;
            case BOMB_ID:
                DrawEntity(renderer, pos.x, pos.y, map.getEntities()[i], map);
                break;
            case ENEMY_ID:
                DrawEnemy(renderer, pos.x, pos.y, map.getEntities()[i], deltaTime, map);
                break;
            case CHEST_ID:
                DrawEntity(renderer, pos.x, pos.y, map.getEntities()[i], map);
                break;
            case PLAYER_ID:
                if (isUsingItem || isUsingSword)
                {
                    DrawAttack(renderer, map, isUsingSword, isUsingItem);
                }
                else
                {
                    DrawPlayer(renderer, pos.x, pos.y, deltaTime, map);
                }
                break;
            case COLLECTIBLE_ID:
                DrawEntity(renderer, pos.x, pos.y, map.getEntities()[i], map);
                break;
            }
        }
    }
}

void DrawWin(SDL_Renderer *renderer, TTF_Font *font)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color color = {255, 255, 255};
    SDL_Surface *text_surface = TTF_RenderText_Solid(font, "You Win !", color);
    SDL_Texture *text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    SDL_Rect text_rect;
    text_rect.x = SDL_WINDOW_WIDTH / 2 - text_surface->w / 2;
    text_rect.y = SDL_WINDOW_HEIGHT / 2 - text_surface->h / 2;
    text_rect.w = text_surface->w;
    text_rect.h = text_surface->h;
    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}

void SDLBoucle(Map &map)
{
    SDL_assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    SDL_Window *window = SDL_CreateWindow(SDL_WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, 0);
    SDL_assert(TTF_Init() == 0);
    SDL_assert(window != NULL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_assert(renderer != NULL);
    bool quit = false;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    TTF_Font *bricksTrialBold = TTF_OpenFont("assets/ttf/tt_bricks/TT-Bricks-Trial-Bold.ttf", 24);
    TTF_Font *bricksTrialBoldMini = TTF_OpenFont("assets/ttf/tt_bricks/TT-Bricks-Trial-Bold.ttf", 12);
    bool isUsingItem = false;
    bool isUsingSword = false;

    while (!quit)
    {
        float startTicks = SDL_GetTicks();
        float deltaTime = 1.0f / 60.0f;
        float timeStepMs = 1000.0f / 60.0f;
        SDL_Event event;
        Vec2f dir;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || state[SDL_SCANCODE_ESCAPE])
            {
                quit = true;
            }
            if (map.getPlayer() != nullptr)
            {
                if (state[SDL_SCANCODE_W])
                {
                    dir = Vec2f(0, -1);
                    map.getPlayer()->setIsWalking(true);
                }
                else if (state[SDL_SCANCODE_S])
                {
                    dir = Vec2f(0, 1);
                    map.getPlayer()->setIsWalking(true);
                }
                else if (state[SDL_SCANCODE_A])
                {
                    dir = Vec2f(-1, 0);
                    map.getPlayer()->setIsWalking(true);
                }
                else if (state[SDL_SCANCODE_D])
                {
                    dir = Vec2f(1, 0);
                    map.getPlayer()->setIsWalking(true);
                }
                else
                {
                    dir = Vec2f(0, 0);
                    map.getPlayer()->setIsWalking(false);
                }
                if (state[SDL_SCANCODE_1])
                {
                    map.getEntities()[0]->setEquipped(0);
                }
                else if (state[SDL_SCANCODE_2])
                {
                    map.getEntities()[0]->setEquipped(1);
                }
                else if (state[SDL_SCANCODE_3])
                {
                    map.getEntities()[0]->setEquipped(2);
                }
                if (state[SDL_SCANCODE_Q])
                {
                    if (isUsingItem)
                        break;
                    isUsingItem = true;
                    Item *item = map.getInventory().getItem(map.getEntities()[0]->getEquipped());
                    if (item != nullptr)
                    {
                        item->use(map);
                    }
                }
                else
                {
                    isUsingItem = false;
                }
                if (state[SDL_SCANCODE_E])
                {
                    map.getPlayer()->Interacting(map);
                }
                if (state[SDL_SCANCODE_F])
                {
                    if (isUsingSword)
                        break;
                    map.getPlayer()->attack(map.getEntities());
                    isUsingSword = true;
                }
                else
                {
                    isUsingSword = false;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        if (map.getEntities()[0]->type() == PLAYER_ID)
        {
            if (!map.win)
            {
                map.update(dir, deltaTime);

                // draw the map
                drawMap(map, renderer);
                drawEntities(map, deltaTime, isUsingItem, isUsingSword, renderer);
                if (map.getEntities()[0]->type() == PLAYER_ID)
                {
                    DrawHUD(renderer, bricksTrialBold, bricksTrialBoldMini, map.getEntities()[0]->getHealth(), map.getEntities()[0]->getMaxHealth(), map);
                }
            }
            else
            {
                DrawWin(renderer, bricksTrialBold);
            }
        }
        else
        {
            DrawGameOver(renderer, bricksTrialBold);
        }

        SDL_RenderPresent(renderer);
        float endTicks = SDL_GetTicks();
        float deltaTicks = endTicks - startTicks;
        if (deltaTicks < timeStepMs)
        {
            SDL_Delay(timeStepMs - deltaTicks);
        }
    }

    // destroy the window
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_CloseFont(bricksTrialBold);
    TTF_Quit();
    SDL_Quit();
}