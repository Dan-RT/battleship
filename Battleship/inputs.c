//
//  inputs.c
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#include <stdio.h>
#include "inputs.h"
#include "structures.h"
#include "tab_functions.h"
#include <string.h>

int safe_input(const char* output, int max) {
    
    int data = 0, check = 0;
    
    do {
        printf("%s", output);
        fflush(stdin);
        check = scanf("%d", &data);
    } while (data < 1 || data > max || check == 0);
    
    return data;
}

void empty_buffer ()
{
    int a = 0;
    while (a != '\n' && a != EOF) {
        a = getchar();
    }
}

int convert_ascii_to_table_index (char input) {
    
    if (input >= 65 && input <= 74) {
        return (int)input - 65;
    } else if (input >= 97 && input <= 106) {
        return (int)input - 97;
    }
    
    printf("Error on convert_ascii_to_table_index function");
    return 0;
}

int read_string (char* output, char* data, int size)
{
    
    printf("%s", output);
    char* retour_ligne = NULL;
    
    if (fgets(data, size, stdin)) {
        retour_ligne = strchr(data, '\n');
        if (retour_ligne != NULL) {
            *retour_ligne = '\0';
        } else {
            empty_buffer();
        }
        return 1;
    }
    empty_buffer();
    return 0;
}

int validation (char tab[10][10], char input_location [3], coordinates* coor, char boat_type) {
    
    if (validate_input_pattern(input_location)) {
        
        coor->x = convert_ascii_to_table_index(input_location[0]);
        coor->y = input_location[1] - 48;
        
        printf("\nCoordinates : %d, %d.\n", coor->x, coor->y);
        
        if (validate_location(tab, *coor, boat_type)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}


int validate_input_pattern(char input_location [3]) {
    
    if (input_location[0] < 65 || input_location[0] > 74) {
        if (input_location[0] < 97 || input_location[0] > 106) {
            printf("Please respect the pattern \"A1\" (Char - Integer).\n");
            //printf("Incorrect char input : %s", input_location);
            return 0;
        }
    }
    
    if (input_location[1] < 48 || input_location[1] > 58) {
        
        printf("Please respect the pattern \"A1\" (Char - Integer).\n");
        //printf("Incorrect integer input : %s", input_location);
        return 0;
    }
    
    return 1;
}

int validate_location (char tab[10][10], coordinates boat, char boat_type) {
    
    int i = 0, flag = 0, choice = 0;
    int orientation[4];
    
    for (i = 0; i < 4; i++) {
        orientation[i] = 0;
    }
    
    if (empty_location_validation(tab, boat)) {
        for (i = 0; i < 4; i++) {
            if (logical_location_validation(tab, boat, boat_type, give_boat_size(boat_type), i+1) == 0) {
                //Comme on est sur du récursif ici on regarde si on est bien resté à 0 pour valider, et non pas 1 comme avant
                orientation[i] = 1;
                flag = 1;
            }
        }
    } else {
        return 0;
    }
    
    if (flag) {
        for (i = 0; i < 4; i++) {
            if (orientation[i] == 1) {
                switch (i) {
                    case 0:
                        printf("1 - Horizontal East-orientation avalaible.\n");
                        break;
                    case 1:
                        printf("2 - Horizontal West-orientation avalaible.\n");
                        break;
                    case 2:
                        printf("3 - Vertical North-orientation avalaible.\n");
                        break;
                    case 3:
                        printf("4 - Vertical South-orientation avalaible.\n");
                        break;
                }
            }
        }
        
        do {
            choice = safe_input("Choose a orientation for your ship : ", 4);
        } while (orientation[choice-1] == 0);
        
        for (i = 0; i < give_boat_size(boat_type); i++) {
            switch (choice) {
                case 1:
                    boat.x++;
                    fill_tab(tab, boat, boat_type);
                    break;
                case 2:
                    boat.x--;
                    fill_tab(tab, boat, boat_type);
                    break;
                case 3:
                    boat.y++;
                    fill_tab(tab, boat, boat_type);
                    break;
                case 4:
                    boat.y--;
                    fill_tab(tab, boat, boat_type);
                    break;
            }
        }
        return 1;
    }
    printf("The boat can't be placed here.\n");
    return 0;
}












