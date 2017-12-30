//
//  inputs.h
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#ifndef inputs_h
#define inputs_h

#include <stdio.h>
#include "structures.h"

int safe_input(const char* output, int max);
int validate_input_pattern(char input_location [3]);
int convert_ascii_to_table_index (char input);
int read_string (char* output, char* data, int size);
void empty_buffer ();
int validate_location (char tab[10][10], coordinates boat, char boat_type);
int validation (char tab[10][10], char input_location [3], coordinates* coor, char boat_type);

#endif /* inputs_h */
