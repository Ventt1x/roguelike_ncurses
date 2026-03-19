#ifndef RENDER_H
#define RENDER_H

#include "config.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "loot.h"



void all_render(char room[][W_MIN],Player_t *player, Bullet_t **bullet, Enemy_t **enemy, Loot_t **loot);



#endif