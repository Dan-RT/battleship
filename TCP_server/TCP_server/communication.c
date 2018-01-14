//
//  communication.c
//  TCP_server
//
//  Created by Daniel Regnard on 09/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#include "communication.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#include <unistd.h>

int connection(int* newSocket) {
    
    int welcomeSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;
    
    
    /*---- Create the socket. The three arguments are: ----*/
    /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    /*---- Configure settings of the server address struct ----*/
    /* Address family = Internet */
    serverAddr.sin_family = AF_INET;
    
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(1981);
    
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    
    /*---- Bind the address struct to the socket ----*/
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    
    /*---- Listen on the socket, with 5 max connection requests queued ----*/
    if(listen(welcomeSocket,5)==0)
        printf("Listening\n");
    else
        printf("Error\n");
    
    /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof serverStorage;
    *newSocket = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);

    
    return 0;
}


int send_message(int newSocket, char* data) {
    char message[1024] = {'\0'};
    
    /*---- Send message to the socket of the incoming connection ----*/
    strcpy(message, data);
    //send(newSocket, message, strlen(message)+1, 0);
    write(newSocket, message, 1024);
    
    return 0;
}

int receive_message(int clientSocket, char* output) {
    
    char buffer[1024] = {'\0'};
    
    /*---- Read the message from the server into the buffer ----*/
    /*while (buffer[0] == '\0') {
        recv(clientSocket, buffer, 1024, 0);
    }*/
    read(clientSocket, buffer, 1024);
    strcpy(output, buffer);
    
    return 1;
}

void request(char* input, char* ouptut, int* socket) {
    char message[1024] = {'\0'};
    
    strcpy(message, "#request#");
    strcat (message, input);
    
    send_message(*socket, message);
    receive_message(*socket, ouptut);
}

void simple_display(char* input, int* socket) {
    
    char message[1024] = {'\0'};
    
    strcpy(message, "#display#");
    strcat (message, input);
    
    send_message(*socket, message);
}
















