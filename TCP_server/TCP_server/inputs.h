//
//  inputs.h
//  TCP_server
//
//  Created by Daniel Regnard on 13/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#ifndef inputs_h
#define inputs_h

#include <stdio.h>
#include "structures.h"

int read_string (char* output, char* data, int size);
void empty_buffer ();
void get_names(char* name_1, char* name_2, int* socket);
int safe_input(const char* output, int max);
int validate_input_pattern(char input_location [3]);
int convert_ascii_to_table_index (char input);
int validate_fill_location (char tab[10][10], coordinates boat, char boat_type);
int validation_fill (char tab[10][10], char input_location [3], coordinates* coor, char boat_type);
int validation_shoot(char tab[10][10], char input_location [3], coordinates* coor);
int shoot_location (char board[10][10], char mark_board[10][10], int* lives);
int shoot_location_request (char board[10][10], char mark_board[10][10], int* lives, char* to_be_send, int* socket);



#endif /* inputs_h */
