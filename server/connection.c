#include <stdbool.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include "connection.h"

#define QUEUE_LENGTH 10
int Socket, ClientSocket;
_Bool createServer(int port)
{
    struct sockaddr_in Addr, ClientAddr;
    int SockOption = 1;
    socklen_t SockLen;

    if ((Socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return false;
    }

    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(port);
    Addr.sin_addr.s_addr = INADDR_ANY;

    if (setsockopt(Socket, SOL_SOCKET, SO_REUSEADDR, &SockOption, sizeof(SockOption)) == -1)
    {
        perror("setsockopt");
        close(Socket);
        return false;
    }

    if (bind(Socket, (struct sockaddr *)&Addr, sizeof(Addr)) == -1)
    {
        perror("bind");
        close(Socket);
        return false;
    }

    if (listen(Socket, QUEUE_LENGTH) == -1)
    {
        perror("listen");
        close(Socket);
        return false;
    }

    SockLen = sizeof(ClientAddr);
    if ((ClientSocket = accept(Socket, (struct sockaddr *)&ClientAddr, &SockLen)) == -1)
    {
        perror("accept");
        close(Socket);
        return false;
    }
    return true;
}

char *readFromSocket()
{
    char *buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));
    memset(buffer, '\0', BUFFER_SIZE);
    if (read(ClientSocket, buffer, BUFFER_SIZE) == -1)
    {
        perror("connection was forcibly closed by the remote host");
        closeServer();
        exit(EXIT_FAILURE);
    };
    return buffer;
}

void sendToClient(const void *buff, size_t n)
{
    if (write(ClientSocket, buff, n) == -1)
    {
        perror("connection was forcibly closed by the remote host");
        closeServer();
        exit(EXIT_FAILURE);
    };
}

void sendToClientSuccesOrFailed(OPTIONS result)
{
    struct ClientOptions *cOption = calloc(1, sizeof(struct ClientOptions));
    cOption->option = result;
    if (write(ClientSocket, cOption, sizeof(struct ClientOptions)) == -1)
    {
        perror("connection was forcibly closed by the remote host");
        closeServer();
        exit(EXIT_FAILURE);
    };
    free(cOption);
}

void closeServer()
{
    close(Socket);
    close(ClientSocket);
}