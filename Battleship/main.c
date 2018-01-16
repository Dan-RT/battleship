//
//  main.c
//  Battleship
//
//  Created by Daniel Regnard on 27/12/2017.
//  Copyright © 2017 Daniel Regnard. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "tab_functions.h"
#include "structures.h"
#include "inputs.h"


int fill_main_board (char board[10][10]);
int shoot_location (char board[10][10], char mark_board[10][10], int* lives);
void display_boards(char board[10][10], char mark_board[10][10], char* name);
int play (player* player1, player* player2);
void get_names(char* name_1, char* name_2);

int main(int argc, const char * argv[]) {
    
    player* player1 = malloc(sizeof(player));
    player* player2 = malloc(sizeof(player));
    
    player1->name = malloc(10*sizeof(char));
    player2->name = malloc(10*sizeof(char));
    
    initialiaze_tab(player1->main_board);
    initialiaze_tab(player1->mark_board);
    initialiaze_tab(player2->main_board);
    initialiaze_tab(player2->mark_board);
    
    fill_main_board(player1->main_board);
    fill_main_board(player2->main_board);
    
    /*
    player1->main_board[0][0] = 'C';
    player1->main_board[0][1] = 'C';
    player1->main_board[0][2] = 'C';
    player1->main_board[0][3] = 'C';
    player1->main_board[0][4] = 'C';
    
    player2->main_board[0][0] = 'C';
    player2->main_board[0][1] = 'C';
    player2->main_board[0][2] = 'C';
    player2->main_board[0][3] = 'C';
    player2->main_board[0][4] = 'C';
    */
     
    printf("\nFilling board has been disabled on the code. A carrier was set by default\n");
    get_names(player1->name, player2->name);
    play(player1, player2);
    
    return 0;
}



int play (player* player1, player* player2) {
    
    int alternance = 0;
    player1->lives = 30;
    player2->lives = 30;
    
    
    while (alternance < 10) {
        if (alternance % 2 == 0) {
            display_boards(player1->main_board, player1->mark_board, player1->name);
            printf("\nNumber of lives : %d\n", player1->lives);
            shoot_location(player2->main_board, player1->mark_board, &player2->lives);
        } else {
            display_boards(player2->main_board, player2->mark_board, player2->name);
            printf("\nNumber of lives : %d\n", player2->lives);
            shoot_location(player1->main_board, player2->mark_board, &player1->lives);
        }
        alternance++;
    }
    
    return 0;
}


int fill_main_board (char board[10][10]) {
    
    ship ships[10];
    char output[50];
    char input[3];
    int i = 0, check = 0;
    coordinates* coor = malloc(sizeof(coordinates));
    
    initialiaze_tab_ship(ships);
    display_tab_ship(ships);
    
    for (i = 0; i < 10; i++) {
        //on boucle sur chaque bateau
        do {
            //on demande les coordonnées du bateau
            snprintf(output, sizeof(output),
                     "\n\nEnter coordinate for a %s : \n",
                     give_boat_name(ships[i].code));
            read_string(output, input, 3);
            check = validation_fill(board, input, coor, *give_boat_name(ships[i].code));
            //on vérifie si toutes les conditions sont remplies pour poser le bateau
        } while (check == 0);
        check = 0;
    }
    
    return 0;
}


void get_names(char* name_1, char* name_2) {
    read_string("\nEnter name Player 1 : ", name_1, 10);
    read_string("\nEnter name Player 2 : ", name_2, 10);
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
        printf("Poum\n\n");
        lives = lives - 1;
    } else {
        fill_tab(mark_board, *coor, 'X');
        printf("Dans l'eau\n\n");
    }
    
    return 0;
}


void display_boards(char board[10][10], char mark_board[10][10], char* name) {
    display_tab(board, "Main Board :", 1, name);
    display_tab(mark_board, "Mark Board :", 0, name);
}




















