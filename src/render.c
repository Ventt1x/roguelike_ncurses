
#include "config.h"
#include "room.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"


void all_render(char (*room)[W_MIN], Player_t *player, Bullet_t **bullet, Enemy_t **enemy){
    for(int i=0; i<L_MIN; i++){
        for (int j = 0; j < W_MIN; j++)
        {
            int found=0;
            if(player->x==j && player->y==i){
                if((player->hit_timer/5)%2==0){
                    printw(" %c", player->sign);
                    found=1;
                } else{
                    printw("  ");
                    found=1;
                } 

            }if (found==0) {
                Enemy_t *curr=*enemy;
                while(curr!=NULL){ 
                    if(curr->x==j && curr->y==i){
                        printw(" %c", curr->sign);
                        found=1;
                        break;
                    }
                    curr=curr->next;
                }   
            }if(found==0){
                Bullet_t *curr=*bullet;
                while(curr!=NULL){ 
                    if(curr->x==j && curr->y==i){
                        printw(" %c", curr->sign);
                        found=1;
                        break;
                    }
                    curr=curr->next;
            } 
            } if(!found){
                if(i==0 || i==L_MIN-1){
                    printw(" %c", room[i][j]); 
                } else  {printw(" %c", room[i][j]);}

            }
        }
        printw("\n");
    }
    int hp_blocks =(player->hp*20)/HP_START;
    printw(" HP: [");
    for(int i=0; i<20; i++){
        if(i<hp_blocks){
            printw("#");
        } else {
            printw("-");
        }
    } 
    printw("] %d/%d", player->hp, HP_START);
    printw("\n");
}