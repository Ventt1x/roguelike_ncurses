#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"
#include "bullet.h"

typedef struct player{
    int x;
    int y;
    int hp;
    int damage;
    char sign;
    unsigned fire_cooldown;
    unsigned MAX_fire_cooldown;
    int move_cooldown;
    int MAX_move_cooldown;
    int hit_timer;

} Player_t;

void player_init(Player_t *player);
void player_attack(Player_t *player, int input, char room[][W_MIN],  Bullet_t **bullet);
void player_move(Player_t *player, char input, char room[][W_MIN]);
void player_dead(Player_t *player);

#endif