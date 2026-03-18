#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "enemy.h"
#include "player.h"

Enemy_t *enemy_init(){
    Enemy_t *new=malloc(sizeof(*new));
    new->hp=80;
    new->x=W_MIN/2;
    new->y=L_MIN/2;
    new->damage=10;
    new->type=0;
    new->sign='8';
    new->move_tick=2;
    new->next=NULL;
    return new;
}
void enemy_attack(Enemy_t *enemy){
    /*attack and damage*/return;
}

Enemy_t *enemy_dead(Enemy_t *dead, Enemy_t *prev, Enemy_t **head){
    printf("Enemy at (%d,%d) died\n", dead->x, dead->y); //debugging
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

Enemy_t *enemy_update(Enemy_t *head, Player_t *player, char room[][W_MIN], int tick){
    if(head==NULL) return NULL;
    Enemy_t *curr=head;
    Enemy_t *prev=NULL;

    while(curr!=NULL){
        if(curr->hp<=0){
            curr=enemy_dead(curr, prev, &head);
            continue;
        } else if (tick%10==0) {
            if(curr->x+1==player->x || curr->x-1==player->x || curr->y+1==player->y || curr->y-1==player->y){
                enemy_attack(curr);
            }
            int r=rand()%4;
            curr->move_tick++;
            if(r==0){
                int r = rand()%4;
                if(r==0 && room[curr->y+1][curr->x]!='#') curr->y++;
                else if(r==1 && room[curr->y-1][curr->x]!='#') curr->y--;
                else if(r==2 && room[curr->y][curr->x+1]!='#') curr->x++;
                else if(room[curr->y][curr->x-1]!='#')curr->x--;

            } else if(curr->y == player->y){
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
            }  else if(curr->move_tick%2==0){
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

        }   prev=curr;
            curr=curr->next; 
    }
    return head;

}


