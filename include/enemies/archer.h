#ifndef ARCHER_H
#define ARCHER_H

#include "config.h"

typedef struct player Player_t;
typedef struct loot Loot_t;
typedef struct bullet Bullet_t;
typedef struct enemy Enemy_t;

Enemy_t *archer_spawn(Enemy_t *head);
void archer_attack(Enemy_t *enemy, Player_t *player, Bullet_t **bullet);
void archer_move(Enemy_t *curr, Player_t *player, char room[][W_MIN]);


#endif