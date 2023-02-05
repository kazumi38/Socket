#include "TCPEchoServer.h"

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
