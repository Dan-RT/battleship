//
//  tab_functions.c
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#include "tab_functions.h"
#include "structures.h"
#include <ctype.h>

void initialiaze_tab(char tab[10][10]) {
 
    int i = 0, j = 0;
    
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            tab[i][j] = '-';
        }
    }
}

void display_tab(char tab[10][10], char* ouptut, int separation, char* name) {
    
    int i = 0, j = 0;
    char letter = 'A';
    
    printf("\n\n");
    if (separation) {
        printf("----------------------------------------------------------------");
        printf("\n\n\n");
    }
    
    printf("%s\n", name);
    printf("%s", ouptut);
    printf("\n");
    
    printf("  |0|1|2|3|4|5|6|7|8|9|\n");
    
    for(i = 0; i < 10; i++) {
        
        printf("|%c", letter);
        letter++;
        for(j = 0; j < 10; j++) {
            printf("|%c", tab[i][j]);
        }
        printf("|\n");
    }
    
    printf("\n");
}

int fill_tab(char tab[10][10], coordinates boat, char boat_type) {

    int i = 0, j = 0;
    
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            if (i == boat.x && j == boat.y) {
                if (tab[i][j] == '-') {
                    if (boat_type != ' ') {
                        tab[i][j] = boat_type;
                    }
                    return 0;
                } else if (tab[i][j] != 'X' && tab[i][j] != 'x') {
                    tab[i][j] = tolower(tab[i][j]);
                    return 1;
                } else {
                    printf("fill_tab last else used");
                    return 0;
                }
            }
        }
    }
    return 0;
}


int empty_location_validation (char tab[10][10], coordinates boat) {
    
    int i = 0, j = 0;
    
    for(i = 0; i < 10; i++) {
        for(j = 0; j < 10; j++) {
            if (i == boat.x && j == boat.y) {
                if (tab[i][j] != '-') {
                    return 0;
                } else {
                    return 1;
                }
            }
        }
    }
    printf("Location not found.\n");
    return 0;
}


int logical_location_validation (char tab[10][10], coordinates boat, int boat_size, int depth, int check_type) {
    
    int i = 0, j = 0;
    
    if (depth != boat_size) {
        if (boat.x < 0 || boat.y < 0 || boat.x > 9 || boat.y > 9 ) {
            //Pour éviter qu'on autorise un bateau hors du tableau
            return 1;
        } else {
            for(i = 0; i < 10; i++) {
                for(j = 0; j < 10; j++) {
                    if (i == boat.x && j == boat.y) {
                        switch (check_type) {
                            case 1:
                                boat.x++;
                                depth++;
                                return 0 + logical_location_validation(tab, boat, boat_size, depth, check_type);
                                break;
                            case 2:
                                boat.x--;
                                depth++;
                                return 0 + logical_location_validation(tab, boat, boat_size, depth, check_type);
                                break;
                            case 3:
                                boat.y++;
                                depth++;
                                return 0 + logical_location_validation(tab, boat, boat_size, depth, check_type);
                                break;
                            case 4:
                                boat.y--;
                                depth++;
                                return 0 + logical_location_validation(tab, boat, boat_size, depth, check_type);
                                break;
                            default:
                                return 1;
                                break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}


void initialiaze_tab_ship (ship ships[10]) {
    
    int i = 0;
    
    ships[0].code = 'C';
    ships[0].size = 5;
    
    for (i = 1; i < 3; i++) {
        ships[i].code = 'B';
        ships[i].size = 4;
    }
    
    for (i = 3; i < 6; i++) {
        ships[i].code = 'S';
        ships[i].size = 3;
    }
    
    for (i = 6; i < 10; i++) {
        ships[i].code = 'D';
        ships[i].size = 2;
    }
}

void display_tab_ship(ship ships[10]) {
    int i = 0;
    
    for(i = 0; i < 10; i++) {
        printf("Name : %c, Size : %d\n", ships[i].code, ships[i].size);
    }
}

char* give_boat_name(char code) {
    
    switch (code) {
        case 'C':
            return "Carrier";
            break;
        case 'B':
            return "Battleship";
            break;
        case 'S':
            return "Submarine";
            break;
        case 'D':
            return "Destroyer";
            break;
        default:
            return "Error";
            break;
    }
}

int give_boat_size(char code) {
    
    switch (code) {
        case 'C':
            return 5;
            break;
        case 'B':
            return 4;
            break;
        case 'S':
            return 3;
            break;
        case 'D':
            return 2;
            break;
        default:
            printf("Invalid boat code.");
            return 0;
            break;
    }
}
















