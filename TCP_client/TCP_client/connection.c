//
//  connection.c
//  TCP_client
//
//  Created by Daniel Regnard on 08/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "connection.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <unistd.h>

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

int connection(int* clientSocket) {
    
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    int connected = 1;
    
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    *clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1981);
    
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    /*---- Connect the socket to the server using the address struct ----*/
    addr_size = sizeof serverAddr;
    
    do {
        connected = connect(*clientSocket, (struct sockaddr *) &serverAddr, addr_size);
    } while (connected == 1);
    
    if (connected == 0) {
        printf("Connection successed with an opponent.\n\n");

    } else {
        printf("Connection failed.\n");
        exit(0);
    }
    
    return 0;
}

int receive_message(int clientSocket, char* output) {
    
    char buffer[1024] = {'\0'};
    
    /*---- Read the message from the server into the buffer ----*/
    /*while (buffer[0] == '\0') {
        recv(clientSocket, buffer, 1024, 0);
    }*/
    read(clientSocket, buffer, 1024);
    //printf("Received : %s\n",buffer);
    strcpy(output, buffer);
    
    return 1;
}

int send_message(int newSocket, char* data) {
    
    char buffer[1024];
    
    /*---- Send message to the socket of the incoming connection ----*/
    strcpy(buffer, data);
    //send(newSocket,buffer,strlen(buffer)+1,0);
    write(newSocket, buffer, 1024);
    
    return 0;
}

int define_message (char* data) {
    //cette fonction check si c'est une request ou un simple display, et enlève de data le code #
    
    const char s[2] = "#";
    char* token = malloc(1024*sizeof(char));
    int returned_value = 0;
    char data_copy[1024];
    strcpy(data_copy, data);
    
    /* get the first token */
    token = strtok(data_copy, s);
    
    if (token != NULL) {
        //checking what is token equals to
        if (strcmp(token,"request") == 0) {
            returned_value = 1;
        } else if (strcmp(token,"display") == 0) {
            returned_value = 2;
        } else if (strcmp(token,"end") == 0) {
            returned_value = 3;
        } else {
            printf( "Code unknown : |%s|\n", token );
            return 0;
        }
        
        /* walk through other tokens */
        //while(token != NULL) {
        //printf( "%s\n", token );
        token = strtok(NULL, s);
        strcpy(data, token);    //it's supposed to have only one token left
        //}
        
        if (token != NULL) {
            //free(token);
        }
        //free(data_copy);
    }
    
    
    return returned_value;
}





