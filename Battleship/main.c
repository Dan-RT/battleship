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
int shoot_location (char board[10][10], char mark_board[10][10]);
void display_boards(char board[10][10], char mark_board[10][10]);
int play();

int main(int argc, const char * argv[]) {
    
    //play();
    
    char main_board[10][10];
    char mark_board[10][10];
    
    initialiaze_tab(main_board);
    initialiaze_tab(mark_board);
    
    //fill_main_board(main_board);
    
    main_board[0][0] = 'C';
    main_board[0][1] = 'C';
    main_board[0][2] = 'C';
    main_board[0][3] = 'C';
    main_board[0][4] = 'C';
    
    display_boards(main_board, mark_board);
    
    printf("\nFilling board has been disabled on the code. A carrier was set by default\n");
    
    while (1) {     //used for tests
        shoot_location(main_board, mark_board);
        
        display_boards(main_board, mark_board);
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
        do {
            //permet de créer dans input une un string avec des variables dedans
            snprintf(output, sizeof(output),
                     "\n\nEnter coordinate for a %s : \n",
                     give_boat_name(ships[i].code));
            read_string(output, input, 3);
            check = validation_fill(board, input, coor, *give_boat_name(ships[i].code));
        } while (check == 0);
        check = 0;
        
    }
    
    return 0;
}


int shoot_location (char board[10][10], char mark_board[10][10]) {
    
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
    } else {
        fill_tab(mark_board, *coor, 'X');
        printf("Dans l'eau\n\n");
    }
    
    return 0;
}


void display_boards(char board[10][10], char mark_board[10][10]) {
    display_tab(board, "Main Board :", 1);
    display_tab(mark_board, "Mark Board :", 0);
}




int play () {
    
    player player1, player2;
    int alternance = 0;
    
    while (1) {
        if (alternance % 2 == 0) {
            
        } else {
            
        }
        alternance++;
    }
    
    return 0;
}
















