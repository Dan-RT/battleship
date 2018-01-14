//
//  main.c
//  TCP_client
//
//  Created by Daniel Regnard on 08/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//


/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "connection.h"

/*
void *send_(void *args)
{
    //printf("\nNous sommes dans le thread send.\n");
    
    int* new_socket = args;
    
    int i = 0;
    for (i = 0; i < 5; i++) {
        //printf("send\n");
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
    //printf("\nNous sommes dans le thread receive.\n");
    
    int* new_socket = args;
    
    int i = 0;
    for (i = 0; i < 5; i++) {
        //printf("receive\n");
    }
    
    while (1) {
        //printf("\nWaiting for a message...\n");
        receive_message(*new_socket);
    }
    
    pthread_exit(NULL);
}
*/

int main(void)
{
    pthread_t send, receive;
    
    //printf("Avant la création des threads.\n");
    
    int socket;
    int* new_socket = &socket;
    char* input = malloc(100*sizeof(char));
    char* message = malloc(1024*sizeof(char));
    
    connection(new_socket);
    
    while (1) {
        receive_message(*new_socket, message);
        
        if (define_message(message) == 1) {
            //si c'est une request
            read_string("", input, 100);
            send_message(*new_socket, input);
        } else if (define_message(message) == 3) {
            //End of the game
            break;
        }
    }
    
    free(input);
    free(message);
    
    /*
    int *args = &socket;
    
    if (pthread_create(&send, NULL, send_, args)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    
    if (pthread_create(&receive, NULL, receive_, args)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    
    
    if (pthread_join(send, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
     
    if (pthread_join(receive, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    */
    printf("Après la création des threads.\n");
    
    return EXIT_SUCCESS;
}




/*

int main(){
    
    int socket;
    int* clientSocket = &socket;
    
    connection(clientSocket);
    
    printf("Waiting for a message...\n");
    while (1) {
        receive_message(socket);
    }
    
    
    return 0;
}
 */
 
 


