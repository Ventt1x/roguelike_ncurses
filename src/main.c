#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "room.h"
#include "player.h"
#include "bullet.h"
#include "render.h"
#include "enemy.h"


int main(){
    char room[L_MIN][W_MIN];
    Player_t player;
    Bullet_t *bullet=NULL;
    Enemy_t *enemy=NULL;

    initscr();
    timeout(TICKRATE);  
    noecho();
    //nodelay(stdscr, TRUE);  // getch() gibt ERR zurück statt zu warten idee von C-Claude
    keypad(stdscr, TRUE);

    room_init(room);
    player_init(&player);
    enemy=enemy_init();
    int fire_cooldown=0;
    int tick=0;

    while(1){
        tick++;
        if(player.fire_cooldown>0)player.fire_cooldown--;
        clear();
        all_render(room, &player, &bullet, &enemy);
        if(tick%1==0) {
            bullet_update(&bullet, room, &player, &enemy);
        }
        if(tick%10==0) enemy=enemy_update(enemy, &player, room);
        refresh();
        int input = ERR;
        int last_input = ERR;
        while((input = getch()) != ERR){
            last_input = input;
        }       
        if((last_input==KEY_UP || last_input==KEY_DOWN || last_input==KEY_LEFT || last_input==KEY_RIGHT)&&player.fire_cooldown==0){ 
            player_attack(&player, last_input, room, &bullet);
            player.fire_cooldown=player.MAX_fire_cooldown;
        }else{
            player_move(&player, last_input, room);
        }
    }

    refresh();
    getch();    
    endwin(); 

    return 0;
}