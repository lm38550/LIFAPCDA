#pragma once

// Entity
#define ARROW_ID 1
#define FIRE_ID 2
#define BOMB_ID 3
#define ENEMY_ID 4
#define CHEST_ID 5
#define PLAYER_ID 6
#define COLLECTIBLE_ID 7
#define ENTITY_RADIUS 0.3f

// Item
#define BOMBBAG_ID 1
#define BOW_ID 2
#define LANTERN_ID 3

// Bomb
#define BOMB_DAMAGE 8
#define BOMB_TIME 3.0f
#define BOMB_EXPLOSION_RADIUS 1.5f
#define BOMB_EXPLOSION_TIME 0.5f

// Arrow
#define ARROW_DAMAGE 2
#define ARROW_SPEED 5

// Fire
#define FIRE_DAMAGE 1
#define FIRE_TIME 3.0f

// Enemy
#define ENEMY_HEALTH 5
#define ENEMY_DAMAGE 1
#define ENEMY_SIZE 0.6
#define ENEMY_INVINCIBILITY_TIME 0.5f
#define ENEMY_DROP_CHANCE 50

// Chest
#define CHEST_5_ABRICOT 0
#define CHEST_BOMBBAG 1
#define CHEST_BOW 2
#define CHEST_LANTERN 3

// Player
#define PLAYER_HEALTH 10
#define PLAYER_INVINCIBILITY_TIME 1.0f
#define PLAYER_SIZE 0.6

// Sword
#define SWORD_SIZE 0.6
#define SWORD_DAMAGE 3

// Collectible
#define COLLECTIBLE_HEALTH 0
#define COLLECTIBLE_ABRICOT 1
#define COLLECTIBLE_BOMB 2
#define COLLECTIBLE_ARROW 3
#define COLLECTIBLE_OIL 4
#define COLLECTIBLE_CROWN 5

// TXTcolors
#define COLOR_BLACK 30
#define COLOR_RED 31
#define COLOR_GREEN 32
#define COLOR_BROWN 33
#define COLOR_BLUE 34
#define COLOR_PURPLE 35
#define COLOR_CYAN 36
#define COLOR_WHITE 37
#define COLOR_DEFAULT 0

// SDL
#define SDL_WINDOW_WIDTH 800
#define SDL_WINDOW_HEIGHT 800
#define SDL_WINDOW_TITLE "SDL2 Displaying Image"
#define TILE_SIZE SDL_WINDOW_WIDTH / map.getWidth()
#define FRAME_SIZE 32;