#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "enemy.h"
#include "player.h"
#include "loot.h"
#include "bullet.h"
#include "room.h"



void drunk_peasant_attack(Enemy_t *enemy, Player_t *player, Bullet_t **bullet){
    if(enemy->hit_cooldown > 0){
        return;
    }
    else if(abs(enemy->x - player->x) + abs(enemy->y - player->y) == 1){
        player->hp-=enemy->damage;
        if(player->hp<=0){
            player_dead(player);
        }
        enemy->hit_cooldown = enemy->MAX_hit_cooldown;
        player->hit_timer=40;
        return;
    }
    return;
}

void drunk_peasant_move(Enemy_t *curr, Player_t *player, char room[][W_MIN]){
    int r=rand()%4;
    int r3 = rand()%2;
    curr->move_tick=curr->MAX_move_tick;
    if(r==0){ //staggering
        int r2 = rand()%3;
        if(r2==0 && room[curr->y+1][curr->x]!='#') curr->y++;
        else if(r2==1 && room[curr->y-1][curr->x]!='#') curr->y--;
        else if(r2==2 && room[curr->y][curr->x+1]!='#') curr->x++;
        else if(room[curr->y][curr->x-1]!='#')curr->x--;
    }   
    else if(curr->y == player->y){ //normal moving towards player
        if (((curr->x)-player->x)<0){
            curr->x++;
        } else if(((curr->x)-player->x)>0){
            curr->x--;
        }
    } else if(curr->x == player->x){
        if (((curr->y)-player->y)<0){
            curr->y++;
        } else if(((curr->y)-player->y)>0){
            curr->y--;
        }
    }  else if(r3==0){
        if (((curr->y)-player->y)<0){
            curr->y++;
        } else if(((curr->y)-player->y)>0){
            curr->y--;
        }
    } else{
        if (((curr->x)-player->x)<0){
            curr->x++;
        } else if(((curr->x)-player->x)>0){
            curr->x--;
        }
    }
}

Enemy_t *drunk_peasant_spawn(Enemy_t *head){
    Enemy_t *new=malloc(sizeof(*new));
    new->hp=80;
    new->x=W_MIN/2;
    new->y=L_MIN/2;
    new->damage=10;
    new->type=0;
    new->sign='8';
    new->move_tick=0;
    new->MAX_move_tick=10;
    new->hit_cooldown=0;
    new->MAX_hit_cooldown=40;
    new->do_move=drunk_peasant_move;
    new->attack=drunk_peasant_attack;

    new->next=head;
    return new;
}
