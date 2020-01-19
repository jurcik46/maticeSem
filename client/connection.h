#ifndef CONNECTION_H
#define CONNECTION_H
#ifdef __cplusplus
extern "C"
{
#endif

    _Bool createConnetion(char *serverIpAddress, int port);
    void closeConnection();
    int getSocket();
#ifdef __cplusplus
}
#endif

#endif /* CONNECTION_H */
