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
int play();

int main(int argc, const char * argv[]) {
    
    //play();
    
    char main_board[10][10];
    
    
    
    //char mark_board[10][10];
    
    initialiaze_tab(main_board);
    display_tab(main_board);
    
    //fill_main_board(main_board);
    
    main_board[0][0] = 'C';
    main_board[0][1] = 'C';
    main_board[0][2] = 'C';
    main_board[0][3] = 'C';
    
    display_tab(main_board);
    
    
    
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
            check = validation(board, input, coor, *give_boat_name(ships[i].code));
        } while (check == 0);
        check = 0;
        
        display_tab(board);
    }
    
    return 0;
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
















