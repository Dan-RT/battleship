//
//  communication.h
//  TCP_server
//
//  Created by Daniel Regnard on 09/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#ifndef communication_h
#define communication_h

#include <stdio.h>

int connection(int* newSocket);
int send_message(int newSocket, char* data);
int receive_message(int clientSocket, char* output);
void request(char* input, char* ouptut, int* socket);


#endif /* communication_h */
