    #ifndef BULLET_H
    #define BULLET_H

    #include <stdlib.h>
    #include <stdio.h>

    #include "config.h"
  

    typedef struct player Player_t;
    typedef struct enemy Enemy_t;
    
    typedef struct bullet{
        struct bullet *next;
        int x;
        int y;
        int dx;
        int dy;
        char sign;

    } Bullet_t;

    void bullet_collision(Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Bullet_t **head);
    void bullet_update(Bullet_t **head, char room[][W_MIN], Player_t *player, Enemy_t **enemy);
    void bullet_shoot(Bullet_t **head, Player_t *player, int dir);
    void bullet_hit(Bullet_t **head, Bullet_t **dead, Bullet_t **prev, Bullet_t *next, Player_t *player, Enemy_t **enemy);
#endif