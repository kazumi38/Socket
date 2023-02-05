#include <stdio.h>      
#include <sys/socket.h> 
#include <arpa/inet.h>  
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>     

#define RCVBUFSIZE 32
#define MAXPENDING 5

void DieWithError(char *errorMessage);
void HandleTCPClient(int clntSocket);
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConnection(int servSock);
