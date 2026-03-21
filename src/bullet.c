#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>    

#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "room.h"

void bullet_collision(Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Bullet_t **head){
    //if(*head==NULL) return; not possible
    if(*prev==NULL){
        *head=next;
        free(*dead);
        *dead=NULL;
        return;
    } 
    (*prev)->next=next;
    free(*dead);
    *dead=NULL;
    return;
}

void bullet_hit(Bullet_t **head, Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Player_t *player, Enemy_t *enemy){
    enemy->hp-=(*dead)->damage;
    if(*prev==NULL){
        *head=next;
        free(*dead);
        *dead=NULL;
        return;
    } 
    (*prev)->next=next;
    free(*dead);
    *dead=NULL;
    return;
}

void bullet_hit_player(Bullet_t **head, Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Player_t *player){
    player->hp-=(*dead)->damage;
    player->hit_timer=40;
    if(player->hp<=0){
        player_dead(player);
    }
    if(*prev==NULL){
        *head=next;
        free(*dead);
        *dead=NULL;
        return;
    } 
    (*prev)->next=next;
    free(*dead);
    *dead=NULL;
    return;
}


void bullet_update(Bullet_t **head, char room[][W_MIN], Player_t *player, Enemy_t **enemy_head, int tick){
    if(*head == NULL) return;

    Bullet_t *curr = *head;
    Bullet_t *prev = NULL;
    Bullet_t *temp;

    while(curr != NULL){
        int gone = 0;

        // determine tick rate based on owner
        int move_now = 0;
        if(curr->owner == PLAYER_OWNER){
            if(tick % 8 == 0){
                move_now = 1;
            }
        } else if(curr->owner == ENEMY_OWNER){
            if(tick % 12 == 0){
                move_now = 1;
            }
        }

        // movement
        if(move_now){
            curr->x += curr->dx;
            curr->y += curr->dy;
        }

        temp = curr;
        curr = curr->next;

        // wall collision (shared)
        if(temp->x <= 0 || temp->x >= W_MIN-1 || temp->y <= 0 || temp->y >= L_MIN-1){
            bullet_collision(&temp, &prev, curr, head);
            gone = 1;
        }

        // entity collision
        if(!gone){
            if(temp->owner == PLAYER_OWNER){
                Enemy_t *enemy_curr = *enemy_head;
                while(enemy_curr != NULL){
                    if(temp->x == enemy_curr->x && temp->y == enemy_curr->y){
                        bullet_hit(head, &temp, &prev, curr, player, enemy_curr);
                        gone = 1;
                        break;
                    }
                    enemy_curr = enemy_curr->next;
                }
            } 
            else if(temp->owner == ENEMY_OWNER){
                if(temp->x == player->x && temp->y == player->y){
                    bullet_hit_player(head, &temp, &prev, curr, player);
                    gone = 1;
                }
            }
        }

        if(!gone){
            prev = temp;
        }
    }
}

void bullet_spawn(Bullet_t **head, int x, int y, int dx ,int dy, int damage, char sign, BulletOwner owner){
    Bullet_t *new=malloc(sizeof(*new));
    new->x=x;
    new->y=y;
    new->dx=dx;
    new->dy=dy;
    new->sign=sign;
    new->next=*head;
    new->owner=owner;
    new->damage=damage;
    *head=new;
}    
