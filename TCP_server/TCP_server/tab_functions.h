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
void display_tab(char tab[10][10], char* ouptut, int separation, char* name);
void display_tab_to_be_send(char tab[10][10], char* ouptut, int separation, char* name, char* to_be_send);

int fill_tab(char tab[10][10], coordinates boat, char boat_type);
void initialiaze_tab_ship (ship ships[10]);
void display_tab_ship(ship ships[10]);
void display_tab_ship_request(ship ships[10], char* data);
char* give_boat_name(char code);
int give_boat_size(char code);

int empty_location_validation (char tab[10][10], coordinates boat);
int logical_location_validation (char tab[10][10], coordinates boat, int boat_size, int depth, int check_type);

int fill_main_board (char board[10][10], int remote, int* socket);
void display_boards(char board[10][10], char mark_board[10][10], char* name);
void display_boards_to_be_send(char board[10][10], char mark_board[10][10], char* name, char* to_be_send);

#endif /* tab_functions_h */





