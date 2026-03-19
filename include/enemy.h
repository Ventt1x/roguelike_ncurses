#ifndef ENEMY_H
#define ENEMY_H

typedef struct player Player_t;

typedef struct loot Loot_t;

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
    int hit_cooldown;
    int MAX_hit_cooldown;
    EnemyType type;
} Enemy_t;

Enemy_t *enemy_init();
Enemy_t *enemy_update(Enemy_t *head, Player_t *player, char room[][W_MIN], int tick, Loot_t **loot_head);
Enemy_t *enemy_dead(Enemy_t *dead, Enemy_t *prev, Enemy_t **head, Loot_t **loot_head);
void enemy_attack(Enemy_t *enemy, Player_t *player);


#endif