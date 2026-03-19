#include "loot.h"
#include "player.h"

Loot_t *loot_drop(Loot_t *head, int x, int y){
    Loot_t *new=malloc(sizeof(*new));
    new->next=head;
    new->value=LOOT_VALUE;
    new->x=x;
    new->y=y;
    new->sign='!';

    return new;
}

Loot_t *loot_collect(Loot_t *head, int x, int y, Player_t *player){ 
    if(head==NULL) return NULL;
    if(head->x==x && head->y==y){
        player->hp+=head->value;
        Loot_t *temp=head->next;
        free(head);
        head=NULL;
        return loot_collect(temp, x, y, player);
    }
    Loot_t *curr=head;
    while(curr->next!=NULL && !(curr->next->x==x && curr->next->y==y)){
        curr=curr->next;
    }
    if(curr->next==NULL){
        return head;
    }
    player->hp+=curr->next->value;
    Loot_t *temp2=curr->next;
    curr->next=curr->next->next;
    free(temp2);
    temp2=NULL;
    return loot_collect(head, x, y, player);
}