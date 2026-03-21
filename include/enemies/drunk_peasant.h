#ifndef DRUNK_PEASANT_H
#define DRUNK_PEASANT_H

#include "config.h"

typedef struct player Player_t;
typedef struct loot Loot_t;
typedef struct bullet Bullet_t;
typedef struct enemy Enemy_t;

Enemy_t *drunk_peasant_spawn(Enemy_t *head);
void drunk_peasant_attack(Enemy_t *enemy, Player_t *player);
void drunk_peasant_move(Enemy_t *curr, Player_t *player, char room[][W_MIN]);




#endif