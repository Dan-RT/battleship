//
//  connection.h
//  TCP_client
//
//  Created by Daniel Regnard on 08/01/2018.
//  Copyright © 2018 Daniel Regnard. All rights reserved.
//

#ifndef connection_h
#define connection_h

#include <stdio.h>

int read_string (char* output, char* data, int size);
void empty_buffer ();
int receive_message(int clientSocket, char* output);
int send_message(int newSocket, char* data);
int connection(int* clientSocket);
int define_message (char* data);

#endif /* connection_h */
