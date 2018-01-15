//
//  main.c
//  TCP_server
//
//  Created by Daniel Regnard on 09/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

/****************** SERVER CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include "communication.h"
#include "structures.h"
#include "inputs.h"
#include "tab_functions.h"
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int shoot_location (char board[10][10], char mark_board[10][10], int* lives);
void display_boards(char board[10][10], char mark_board[10][10], char* name);
int play (player* player1, player* player2, int* socket);


/*
void *send_(void *args)
{
    printf("\nNous sommes dans le thread send.\n");
    
    int* new_socket = args;
    
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("send\n");
    }
    
    while (1) {
        char* output = "\nVotre message : ";
        char* input = malloc(1024*sizeof(char));
        read_string(output, input, 1024);
        send_message(*new_socket, input);
    }
    
    pthread_exit(NULL);
}

void *receive_(void *args)
{
    printf("\nNous sommes dans le thread receive.\n");
    
    int* new_socket = args;
    
    int i = 0;
    for (i = 0; i < 5; i++) {
        printf("receive\n");
    }
    
    while (1) {
        printf("\nWaiting for a message...\n");
        receive_message(*new_socket);
    }
    
    pthread_exit(NULL);
}

*/



void *host_(void *args)
{
    printf("\nNous sommes dans le thread host.\n");
    
    player* player1_ = args;
    
    initialiaze_tab(player1_->main_board);
    initialiaze_tab(player1_->mark_board);
    
    //fill_main_board(player1_->main_board, 0, NULL);
    
    pthread_exit(NULL);
}

void *client_(void *args)
{
    printf("\nNous sommes dans le thread client.\n");
    
    player* player2_ = args;
    
    initialiaze_tab(player2_->main_board);
    initialiaze_tab(player2_->mark_board);
    
    //fill_main_board(player2_->main_board, 1, player2_->socket);
    
    pthread_exit(NULL);
}


int main(void)
{
    pthread_t host, client;
    
    printf("Avant la création des threads.\n");
    
    int socket;
    int* new_socket = &socket;
    
    player* player1 = malloc(sizeof(player));
    player* player2 = malloc(sizeof(player));
    player2->socket = &socket;

    player1->name = malloc(10*sizeof(char));
    player2->name = malloc(10*sizeof(char));
    
    player *args_1 = player1;
    player *args_2 = player2;
    
    connection(new_socket);
    
    if (pthread_create(&host, NULL, host_, args_1)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    
    if (pthread_create(&client, NULL, client_, args_2)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    
    if (pthread_join(host, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    
    if (pthread_join(client, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    
    printf("\nPlayer1 name : %s\n", player1->name);
    printf("\nPlayer2 name : %s\n", player2->name);
    
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
    
    printf("\nFilling board has been disabled on the code. A carrier was set by default\n");
    
    play(player1, player2, new_socket);
     
    return EXIT_SUCCESS;
}


int play (player* player1, player* player2, int* socket) {
    
    int alternance = 0, end = 0;
    player1->lives = 5; //30;
    player2->lives = 5; //30;
    char to_be_send[1024] = "";
    
    while (end == 0) {
        if (alternance % 2 == 0) {
            display_boards(player1->main_board, player1->mark_board, player1->name);
            printf("\nNumber of lives : %d\n", player1->lives);
            shoot_location(player2->main_board, player1->mark_board, &player2->lives);
        } else {
            printf("Waiting for player 2 to play...");
            
            strcpy(to_be_send, "");     //erase string
            display_boards_to_be_send(player2->main_board, player2->mark_board, player2->name, to_be_send);     //filling string
            simple_display(to_be_send, socket); //sending it
            
            strcpy(to_be_send, "");
            sprintf(to_be_send + strlen(to_be_send),"\nNumber of lives : %d\n", player2->lives);
            shoot_location_request(player1->main_board, player2->mark_board, &player1->lives, to_be_send, socket);      //request is made inside this function
        }
        if (player1->lives == 0 || player2->lives == 0) {
            end = 1;
        }
        alternance++;
    }
    
    if (player1->lives == 0) {
        strcpy(to_be_send, "");
        sprintf(to_be_send + strlen(to_be_send),"\nYou've won the Game! Congratulations!\n");
        printf("\nYou've lost the game.\n");
    } else {
        strcpy(to_be_send, "");
        sprintf(to_be_send + strlen(to_be_send),"\nYou've lost the game.\n");
        printf("\nYou've won the Game! Congratulations!\n");
    }
    strcpy(to_be_send, "");
    display_tab_to_be_send(player2->main_board, "Your Board :", 1, "", to_be_send);
    display_tab_to_be_send(player1->main_board, "Opponent's Board :", 1, player2->name, to_be_send);
    simple_display(to_be_send, socket);
    display_tab(player2->main_board, "Opponent's Board", 1, player2->name);
    display_tab(player1->main_board, "Your Board", 1, player2->name);
    
    return 0;
}










