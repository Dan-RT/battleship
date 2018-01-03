//
//  tab_functions.h
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#ifndef tab_functions_h
#define tab_functions_h

#include <stdio.h>
#include "structures.h"


void initialiaze_tab(char tab[10][10]);
void display_tab(char tab[10][10], char* ouptut, int separation);
int fill_tab(char tab[10][10], coordinates boat, char boat_type);
void initialiaze_tab_ship (ship ships[10]);
void display_tab_ship(ship ships[10]);
char* give_boat_name(char code);
int give_boat_size(char code);

int empty_location_validation (char tab[10][10], coordinates boat);
int logical_location_validation (char tab[10][10], coordinates boat, int boat_size, int depth, int check_type);

#endif /* tab_functions_h */





