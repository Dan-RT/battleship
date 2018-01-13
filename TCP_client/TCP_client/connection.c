//
//  connection.c
//  TCP_client
//
//  Created by Daniel Regnard on 08/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#include "connection.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

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
    serverAddr.sin_port = htons(7891);
    
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
        printf("Connection successed.\n");

    } else {
        printf("Connection failed.\n");
    }
    
    return 0;
}

int receive_message(int clientSocket) {
    
    char buffer[1024] = {'\0'};
    
    /*---- Read the message from the server into the buffer ----*/
    while (buffer[0] == '\0') {
        recv(clientSocket, buffer, 1024, 0);
    }
    
    /*---- Print the received message ----*/
    printf("%s",buffer);
    
    return 1;
}

int send_message(int newSocket, char* data) {
    
    char buffer[1024];
    
    /*---- Send message to the socket of the incoming connection ----*/
    strcpy(buffer, data);
    send(newSocket,buffer,1024,0);
    
    return 0;
}





