#ifndef ENEMY_H
#define ENEMY_H

typedef struct player Player_t;

typedef enum {
    ENEMY_DRUNK_PEASANT
} EnemyType;

typedef struct enemy{
    struct enemy *next;
    int hp;
    int x;
    int y;
    int damage;
    char sign;
    int move_tick;
    EnemyType type;
} Enemy_t;

Enemy_t *enemy_init();
Enemy_t *enemy_update(Enemy_t *head, Player_t *player, char room[][W_MIN]);
Enemy_t *enemy_dead(Enemy_t *dead, Enemy_t *prev, Enemy_t **head);
void enemy_attack(Enemy_t *enemy);


#endif