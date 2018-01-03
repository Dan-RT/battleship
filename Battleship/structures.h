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
    char* name;
    int winner;
    int ip_address;
};


#endif /* structures_h */
