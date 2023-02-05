#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHOMAX 255

void DieWithError(char *errorMessage);

int main(int argc, char *argv[]){
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;

    unsigned short echoServPort;
    unsigned int cliAddrLen;

    char echoBuffer[ECHOMAX+1];
    int recvMsgSize;

    if(argc != 2){
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);
    printf("echo Server Port : %d\n", echoServPort);

    if((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP))<0){
        DieWithError("socket() failed");
    }

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    printf("echo server address : %s %d\n", inet_ntoa(echoServAddr.sin_addr), echoServAddr.sin_addr.s_addr);

    if(bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0){
        DieWithError("bind() failed");
    }

    for(;;){
        memset(&echoBuffer, 0, sizeof(echoBuffer));
        cliAddrLen = sizeof(echoClntAddr);

        if((recvMsgSize = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr*)&echoClntAddr, &cliAddrLen)) < 0){            
            printf("recv message size : %d\n", recvMsgSize);
            DieWithError("recvfrom() failed");
        }

        printf("Handling client %s > %s(%d)\n", inet_ntoa(echoClntAddr.sin_addr), echoBuffer, recvMsgSize);

        if(sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *)&echoClntAddr, sizeof(echoClntAddr)) != recvMsgSize){
            printf("Don't send messages");
            DieWithError("sendto() sent a different number of bytes than expected");
        }
    }

}

void DieWithError(char* errorMessage){
    perror(errorMessage);
    exit(1);
}