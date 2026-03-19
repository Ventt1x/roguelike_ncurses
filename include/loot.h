#ifndef LOOT_H
#define LOOT_H

typedef struct player Player_t;

typedef struct loot{
    struct loot* next;
    int value;
    int x;
    int y;
    char sign;
} Loot_t;

Loot_t * loot_collect(Loot_t *head, int x, int y, Player_t *player);
Loot_t * loot_drop(Loot_t *head, int x, int y);

#endif