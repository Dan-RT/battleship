//
//  structures.h
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#ifndef structures_h
#define structures_h

#include <stdio.h>



typedef struct coordinates coordinates ;
struct coordinates {
    int x;
    int y;
};


typedef struct ship ship ;
struct ship {
    char code;
    int size;
    int life;
};

typedef struct player player ;
struct player {
    char main_board[10][10];
    char mark_board[10][10];
    char* name;
    int lives;
    int winner;
    int ip_address;
    int* socket;
};


#endif /* structures_h */
