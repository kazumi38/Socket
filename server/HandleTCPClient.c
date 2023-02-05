#include "TCPEchoServer.h"

void HandleTCPClient(int clntSocket)
{
	char echoBuffer[RCVBUFSIZE];
	int recvMsgSize;

	if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
		DieWithError("recv() failed");
	}

	while (recvMsgSize > 0){
		if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize){
			DieWithError("send() failed");
		}

		if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
			DieWithError("recv() failed");
		}
	}

	close(clntSocket);
}
