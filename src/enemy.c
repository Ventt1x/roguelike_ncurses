#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "enemy.h"
#include "player.h"
#include "loot.h"
#include "bullet.h"

Enemy_t *enemy_dead(Enemy_t *dead, Enemy_t *prev, Enemy_t **head, Loot_t **loot_head){
    *loot_head=loot_drop(*loot_head, dead->x, dead->y);
    //printf("Enemy at (%d,%d) died\n", dead->x, dead->y); //debugging
    if(dead==NULL) return NULL;
    Enemy_t *next = dead->next;
    if(prev==NULL){
        *head = next;
    } else {
        prev->next = next;
    }
    free(dead);
    return next;
}

Enemy_t *enemy_update(Enemy_t *head, Player_t *player, char room[][W_MIN], int tick, Loot_t **loot_head){
    if(head==NULL) return NULL;
    Enemy_t *curr=head;
    Enemy_t *prev=NULL;

    while(curr!=NULL){
        if(curr->hit_cooldown > 0){
            curr->hit_cooldown--;
        }
        curr->move_tick--;
         if(curr->hp<=0){
            curr=enemy_dead(curr, prev, &head, loot_head);
            continue;
        } else{
            if(curr->move_tick<=0) curr->do_move(curr, player, room);
            if(curr->hit_cooldown<=0) curr->attack(curr, player, NULL);
        }
        curr=curr->next;
    }
    return head;
}