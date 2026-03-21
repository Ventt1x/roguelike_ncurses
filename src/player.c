#include <ncurses.h>

#include "player.h"
#include "bullet.h"



void player_shoot(Player_t *player, int input, char room[][W_MIN], Bullet_t **head){
    int dx;
    int dy;
    char sign='*';
    switch(input){
        case KEY_UP:{
            dy=(-1)*B_VELO;
            dx=0;
            break;
        }
        case KEY_DOWN:{
            dy=B_VELO;
            dx=0;
            break;
        }
        case KEY_LEFT:{
            dy=0;
            dx=(-1)*B_VELO;
            break;
        }
        case KEY_RIGHT:{
            dy=0;
            dx=B_VELO;
            break;
        }
    }
    bullet_spawn(head, player->x, player->y, dx, dy, player->damage, sign, 0);
}


void player_move(Player_t *player, char input, char room[][W_MIN]){
    if(player->move_cooldown > 0){
        player->move_cooldown--;
        return;
    }

    int moved=0;
    switch(input){
        case 'w': {
            if(room[player->y-1][player->x]!='#'){
                player->y-=1;
                moved=1;
            }
            break;
        }
        case 'a': {
            if(room[player->y][player->x-1]!='#'){
                player->x-=1;
                moved=1;
            }
            break;
        }
        case 's': {
            if(room[player->y+1][player->x]!='#'){
                player->y+=1;
                moved=1;
            }
            break;
        }
        case 'd': {
            if(room[player->y][player->x+1]!='#'){
                player->x+=1;
                moved=1;
            }
            break;
        }


    }
    if(moved){
        player->move_cooldown = player->MAX_move_cooldown;
    }

}

void player_dead(Player_t *player){
    endwin();
    exit(0);
}


void player_init(Player_t *player){
    player->x=W_MIN/2;
    player->y=L_MIN-2;
    player->hp=HP_START;
    player->damage=DMG_START;
    player->sign='@';
    player->fire_cooldown=0;
    player->MAX_fire_cooldown=40;
    player->move_cooldown = 0;
    player->MAX_move_cooldown = 3; // tweak this
    player->hit_timer = 0;
    player->do_attack=player_shoot;
}