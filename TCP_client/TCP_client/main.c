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

int main(void)
{
    printf("Welcome!! Let's play Battleship.\n\n\n");
    
    int socket, type_message = -1;
    int* new_socket = &socket;
    char* input = malloc(100*sizeof(char));
    char* message = malloc(1024*sizeof(char));
    
    connection(new_socket);
    
    while (1) {
        receive_message(*new_socket, message);
        type_message = define_message(message);
        if (type_message == 1) {
            printf("%s", message);
            //si c'est une request
            read_string("", input, 100);
            send_message(*new_socket, input);
        } else if (type_message == 3) {
            //End of the game
            break;
        } else {
            printf("%s", message);
        }
        
    }
    
    free(input);
    free(message);
    
    
    return EXIT_SUCCESS;
}





