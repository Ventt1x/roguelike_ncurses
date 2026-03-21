#ifndef ENEMY_H
#define ENEMY_H

typedef struct player Player_t;

typedef struct loot Loot_t;

typedef struct bullet Bullet_t;

typedef enum {
    ENEMY_DRUNK_PEASANT,
    ARCHER
} EnemyType;

typedef struct enemy{
    struct enemy *next;
    int hp;
    int x;
    int y;
    int damage;
    char sign;
    int move_tick;
    int MAX_move_tick;
    int hit_cooldown;
    int MAX_hit_cooldown;
    EnemyType type;
    void (*attack) (struct enemy*, struct player*, Bullet_t **);
    void (*do_move) (struct enemy*, Player_t *, char[][W_MIN]);
    //void (*spawn) (struct enemy*);
} Enemy_t;

Enemy_t *enemy_update(Enemy_t *head, Player_t *player, char room[][W_MIN], int tick, Loot_t **loot_head, Bullet_t **bullets);
Enemy_t *enemy_dead(Enemy_t *dead, Enemy_t *prev, Enemy_t **head, Loot_t **loot_head);


#endif