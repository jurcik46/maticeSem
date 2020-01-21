#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <stdbool.h>
#include "connection.h"
#define QUEUE_LENGTH 10

int Socket;
_Bool createConnetion(char *serverIpAddress, int port)
{
    struct sockaddr_in Addr;
    if ((Socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Creating socket error");
        return false;
    }

    Addr.sin_family = AF_INET;
    Addr.sin_port = htons(port);
    if (inet_aton(serverIpAddress, &Addr.sin_addr) == 0)
    {
        perror("inet_aton: Error in IP conversion \n");
        close(Socket);
        return false;
    }

    if (connect(Socket, (struct sockaddr *)&Addr, sizeof(Addr)) == -1)
    {
        perror("Failed connect to the server");
        close(Socket);
        return false;
    }

    return true;
}

void sendToServer(const void *buff, size_t n)
{
    write(Socket, buff, n);
}

void sendToServerOption(struct ClientOptions *clientOption)
{
    write(Socket, clientOption, sizeof(struct ClientOptions));
}

char *readFromSocket()
{
    memset(buffer, '\0', 1500);
    read(Socket, buffer, 1500);
    return buffer;
}
void closeConnection()
{
    close(Socket);
}