#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "room.h"
#include "player.h"
#include "bullet.h"
#include "render.h"
#include "enemy.h"
#include "loot.h"
#include "enemies/drunk_peasant.h"
#include "enemies/archer.h"


int main(){
    char room[L_MIN][W_MIN];
    Player_t player;
    Bullet_t *bullet=NULL;
    Enemy_t *enemy=NULL;
    Loot_t *loot=NULL;

    initscr();
    timeout(TICKRATE);  
    noecho();
    //nodelay(stdscr, TRUE);  // getch() gibt ERR zurück statt zu warten idee von C-Claude
    keypad(stdscr, TRUE);

    room_init(room);
    player_init(&player);
    //enemy=drunk_peasant_spawn(enemy);
    enemy=archer_spawn(enemy);
    int tick=0;

    while(1){
        tick++;
        if(player.fire_cooldown>0)player.fire_cooldown--;
        if(player.hit_timer>0) player.hit_timer--;
        erase();

        enemy=enemy_update(enemy, &player, room, tick, &loot, &bullet);
        bullet_update(&bullet, room, &player, &enemy, tick);
        all_render(room, &player, &bullet, &enemy, &loot);

        refresh();
        int input = ERR;
        int last_input = ERR;
        while((input = getch()) != ERR){
            last_input = input;
        }       
        if((last_input==KEY_UP || last_input==KEY_DOWN || last_input==KEY_LEFT || last_input==KEY_RIGHT)&&player.fire_cooldown==0){ 
            player.do_attack(&player, last_input, room, &bullet);
            player.fire_cooldown=player.MAX_fire_cooldown;
        }else{
            player_move(&player, last_input, room);
            loot=loot_collect(loot, player.x, player.y, &player);
        }
    }

    refresh();
    getch();    
    endwin(); 

    return 0;
}