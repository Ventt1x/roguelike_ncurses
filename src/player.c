#include <ncurses.h>

#include "player.h"
#include "bullet.h"

void player_init(Player_t *player){
    player->x=W_MIN/2;
    player->y=L_MIN-2;
    player->hp=HP_START;
    player->damage=DMG_START;
    player->sign='@';
    player->fire_cooldown=0;
    player->MAX_fire_cooldown=40;
}

void player_attack(Player_t *player, int input, char room[][W_MIN], Bullet_t **bullet){
    //int dir=getch();
    bullet_shoot(bullet, player, input);
}


void player_move(Player_t *player, char input, char room[][W_MIN]){
    switch(input){
        case 'w': {
            if(room[player->y-1][player->x]!='#'){
                player->y-=1;
            }
            break;
        }
        case 'a': {
            if(room[player->y][player->x-1]!='#'){
                player->x-=1;
            }
            break;
        }
        case 's': {
            if(room[player->y+1][player->x]!='#'){
                player->y+=1;
            }
            break;
        }
        case 'd': {
            if(room[player->y][player->x+1]!='#'){
                player->x+=1;
            }
            break;
        }


    }

}

