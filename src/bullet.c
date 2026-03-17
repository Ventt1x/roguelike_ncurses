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

void bullet_hit(Bullet_t **head, Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Player_t *player, Enemy_t **enemy){
    (*enemy)->hp-=player->damage;
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



void bullet_update(Bullet_t **head, char room[][W_MIN], Player_t *player, Enemy_t **enemy_head){
    if(*head==NULL) return;

    Bullet_t *curr=*head;
    Bullet_t *prev=NULL;
    Bullet_t *temp;

    while(curr!=NULL){
        int gone=0;
        curr->x+=curr->dx;
        curr->y+=curr->dy;
        temp=curr;
        curr=curr->next;
        if(temp->x<=0 || temp->x>= W_MIN-1|| temp->y<= 0 || temp->y>=L_MIN-1){
            bullet_collision(&temp, &prev, curr, head);
            gone=1;
        } else if(gone==0){
            Enemy_t *enemy_curr=*enemy_head;
            while(enemy_curr!=NULL){
                if(temp->y==enemy_curr->y && temp->x==enemy_curr->x){
                    bullet_hit(head, &temp, &prev, curr ,player, &enemy_curr);
                    gone=1;
                    break;
                }
                enemy_curr=enemy_curr->next;
            }
        }
        if(!gone) prev=temp;

    }
}

void bullet_shoot(Bullet_t **head, Player_t *player, int dir){
    Bullet_t *new=malloc(sizeof(*new));
    new->x=player->x;
    new->y=player->y;
    switch(dir){
        case KEY_UP:{
            new->dy=(-1)*B_VELO;
            new->dx=0;
            break;
        }
        case KEY_DOWN:{
            new->dy=B_VELO;
            new->dx=0;
            break;
        }
        case KEY_LEFT:{
            new->dy=0;
            new->dx=(-1)*B_VELO;
            break;
        }
        case KEY_RIGHT:{
            new->dy=0;
            new->dx=B_VELO;
            break;
        }
    }
    new->sign='*';
    new->next=*head;
    *head=new;    
}    
