#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "enemy.h"
#include "player.h"
#include "loot.h"
#include "bullet.h"
#include "room.h"



void archer_attack(Enemy_t *enemy, Player_t *player, Bullet_t **head){
    if(enemy->hit_cooldown > 0){
        return;
    }
    else if(enemy->x == player->x || enemy->y == player->y){
        int dx = 0, dy = 0;
        if(enemy->x==player->x){
            if(enemy->y<player->y){
                dy=1;
            } else dy=-1;
        } else {
            if(enemy->x<player->x){
                dx=1;
            } else dx=-1;
        }
        bullet_spawn(head, enemy->x, enemy->y, dx, dy, enemy->damage, 'o', 1);
        enemy->hit_cooldown = enemy->MAX_hit_cooldown;
        return;
    } 
}

void archer_move(Enemy_t *curr, Player_t *player, char room[][W_MIN]){
    curr->move_tick=curr->MAX_move_tick;

    if(abs(curr->x - player->x)+ abs (curr->y-player->y)<6){//possible to corner him atm
        if(curr->y==player->y){
            if(curr->x < player->x){  
                if(room[curr->y][curr->x-1]!='#') curr->x--;
            } else {
                if(room[curr->y][curr->x+1]!='#') curr->x++;
            }
        }
        else if(curr->x==player->x) {
            if(curr->y < player->y ){
                if(room[curr->y-1][curr->x]!= '#') curr->y--;
            } else if(room[curr->y+1][curr->x]!='#') curr->y++;

        }
        else{
            int r=rand()%3;
            if(r==0){
                if(room[curr->y+1][curr->x]!= '#') curr->y++;
                else if(room[curr->y-1] [curr->x] !='#') curr->y--;               
            }
            else{
               if(room[curr->y][curr->x+1]!='#') curr->x++;
                else if (room[curr->y][curr->x+1]!='#') curr->x--; 
            }
        }
    } else if(curr->x == player->x || curr->y == player->y) { //if same lane already, do nothing
        return;
    } else if (abs(curr->x - player->x)+ abs (curr->y-player->y)>7) {  //try to get on the same x or y axis for clean shot
        if(abs(curr->x-player->x)<abs(curr->y-player->y)){
            if((curr->x-player->x)<0){
                curr->x++;
            } else curr->x--;
        } else{
            if((curr->y-player->y)<0){
                curr->y++;
            } else curr->y--;
        }
        
    }   
    else return;    



}


Enemy_t *archer_spawn(Enemy_t *head){
    Enemy_t *new=malloc(sizeof(*new));
    new->hp=80;
    new->x=W_MIN/2;
    new->y=1;
    new->damage=10;
    new->type=1;
    new->sign='B';
    new->move_tick=0;
    new->MAX_move_tick=10;
    new->hit_cooldown=0;
    new->MAX_hit_cooldown=60;
    new->do_move=archer_move;
    new->attack=archer_attack;

    new->next=head;
    return new;
}
