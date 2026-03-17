#ifndef RENDER_H
#define RENDER_H

#include "config.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"



void all_render(char room[][W_MIN],Player_t *player, Bullet_t **bullet, Enemy_t **enemy);



#endif