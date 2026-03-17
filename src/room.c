#include "room.h"


void room_init(char room[][W_MIN]){
    for(int i=0; i<L_MIN; i++){
        for (int j = 0; j < W_MIN; j++)
        {
            room[i][j]=' '; //.
            room[0][j]='#'; //-
            room[i][0]='#'; //|
            room[L_MIN-1][j]='#'; //-
            room[i][W_MIN-1]='#'; //>
        }
        
    }
}

