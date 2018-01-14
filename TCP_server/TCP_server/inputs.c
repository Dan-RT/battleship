//
//  inputs.c
//  TCP_server
//
//  Created by Daniel Regnard on 13/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "structures.h"
#include "tab_functions.h"
#include <string.h>
#include "communication.h"

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

void empty_buffer ()
{
    int a = 0;
    while (a != '\n' && a != EOF) {
        a = getchar();
    }
}


void get_names(char* name_1, char* name_2, int* socket) {
    read_string("\nEnter your name : ", name_1, 10);
    request("\nEnter your name : ", name_2, socket);
}


int validation_fill (char tab[10][10], char input_location [3], coordinates* coor, char boat_type, int remote, int* socket) {

    char data[32];
    
    if (validate_input_pattern(input_location)) {
        
        coor->x = convert_ascii_to_table_index(input_location[0]);
        coor->y = input_location[1] - 48;
        
        if (remote) {
            sprintf(data, "\nCoordinates : %d, %d.\n", coor->x, coor->y);
            simple_display(data, socket);
        } else {
            printf("\nCoordinates : %d, %d.\n", coor->x, coor->y);
        }
        
        if (validate_fill_location(tab, *coor, boat_type, remote, socket)) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int safe_input(const char* output, int max) {
    
    int data = 0, check = 0;
    
    do {
        printf("%s", output);
        fflush(stdin);
        check = scanf("%d", &data);
    } while (data < 1 || data > max || check == 0);
    
    return data;
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


int validate_fill_location (char tab[10][10], coordinates boat, char boat_type, int remote, int* socket) {
    
    int i = 0, flag = 0, choice = 0;
    int orientation[4];
    char data[128];
    
    for (i = 0; i < 4; i++) {
        orientation[i] = 0;
    }
    
    if (empty_location_validation(tab, boat)) {
        for (i = 0; i < 4; i++) {
            if (logical_location_validation(tab, boat, give_boat_size(boat_type), 0, i+1) == 0) {
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
                        if (remote) {
                            sprintf(data, "1 - Vertical South-orientation avalaible.\n");
                            simple_display(data, socket);
                        } else {
                            printf("1 - Vertical South-orientation avalaible.\n");
                        }
                        
                        break;
                    case 1:
                        if (remote) {
                            sprintf(data, "2 - Vertical North-orientation avalaible.\n");
                            simple_display(data, socket);
                        } else {
                            printf("2 - Vertical North-orientation avalaible.\n");
                        }
                        
                        break;
                    case 2:
                        if (remote) {
                            sprintf(data, "3 - Horizontal East-orientation avalaible.\n");
                            simple_display(data, socket);
                        } else {
                            printf("3 - Horizontal East-orientation avalaible.\n");
                        }
                        
                        break;
                    case 3:
                        if (remote) {
                            sprintf(data, "4 - Horizontal West-orientation avalaible.\n");
                            simple_display(data, socket);
                        } else {
                            printf("4 - Horizontal West-orientation avalaible.\n");
                        }
                        break;
                }
            }
        }
        
        do {
            if (remote) {
                sprintf(data, "Choose a orientation for your ship : ");
                request(data, data, socket);
                //pas sécurisée
                choice = data[0];
            } else {
                choice = safe_input("Choose a orientation for your ship : ", 4);
            }
        } while (orientation[choice-1] == 0);
        
        for (i = 0; i < give_boat_size(boat_type); i++) {
            switch (choice) {
                case 1:
                    fill_tab(tab, boat, boat_type);
                    boat.x++;
                    break;
                case 2:
                    fill_tab(tab, boat, boat_type);
                    boat.x--;
                    break;
                case 3:
                    fill_tab(tab, boat, boat_type);
                    boat.y++;
                    break;
                case 4:
                    fill_tab(tab, boat, boat_type);
                    boat.y--;
                    break;
            }
        }
        return 1;
    }
    if (remote) {
        sprintf(data, "The boat can't be placed here.\n");
        simple_display(data, socket);
    } else {
        printf("The boat can't be placed here.\n");
    }
    return 0;
}


int validation_shoot (char tab[10][10], char input_location [3], coordinates* coor) {
    
    if (validate_input_pattern(input_location)) {
        
        coor->x = convert_ascii_to_table_index(input_location[0]);
        coor->y = input_location[1] - 48;
        return 1;
    } else {
        return 0;
    }
}

int validate_input_pattern(char input_location [3]) {
    
    if (input_location[0] < 65 || input_location[0] > 74) {
        if (input_location[0] < 97 || input_location[0] > 106) {
            //printf("Please respect the pattern \"A1\" (Char - Integer).\n");
            return 0;
        }
    }
    
    if (input_location[1] < 48 || input_location[1] > 58) {
        
        //printf("Please respect the pattern \"A1\" (Char - Integer).\n");
        return 0;
    }
    
    return 1;
}


int shoot_location (char board[10][10], char mark_board[10][10], int* lives) {
    
    char input[3];
    int check = 0;
    coordinates* coor = malloc(sizeof(coordinates));
    
    do {
        read_string("\nEnter coordinate to shoot : \n", input, 3);
        check = validation_shoot(board, input, coor);
    } while (check == 0);
    
    if (fill_tab(board, *coor, ' ')) {
        fill_tab(mark_board, *coor, 'x');
        printf("Hit\n\n");
        *lives = *lives - 1;
    } else {
        fill_tab(mark_board, *coor, 'X');
        printf("Dans l'eau\n\n");
    }
    
    return 0;
}

int shoot_location_request (char board[10][10], char mark_board[10][10], int* lives, char* to_be_send, int* socket) {
    
    //char input[3];
    char response[10];
    int check = 0;
    coordinates* coor = malloc(sizeof(coordinates));
    
    sprintf(to_be_send + strlen(to_be_send),"\nEnter coordinate to shoot : \n");
    request(to_be_send, response, socket);
    
    if (validation_shoot(board, response, coor) == 0) {
        do {
            request("\nPlease respect the pattern \"A1\" (Char - Integer) or choose a correct location.\nEnter coordinate to shoot : \n", response, socket);
            check = validation_shoot(board, response, coor);
        } while (check == 0);
    }
    
    if (fill_tab(board, *coor, ' ')) {
        fill_tab(mark_board, *coor, 'x');
        
        strcpy(to_be_send, "");     //erase string
        sprintf(to_be_send + strlen(to_be_send),"Hit\n\n");
        simple_display(to_be_send, socket);
        
        *lives = *lives - 1;
    } else {
        fill_tab(mark_board, *coor, 'X');
        
        strcpy(to_be_send, "");     //erase string
        sprintf(to_be_send + strlen(to_be_send),"Dans l'eau\n\n");
        simple_display(to_be_send, socket);
    }
    
    return 0;
}



