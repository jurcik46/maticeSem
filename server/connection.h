#ifndef CONNECTION_H
#define CONNECTION_H
#ifdef __cplusplus
extern "C"
{
#endif

    _Bool createServer(int port);
    void closeServer();
    int getSocket();

#ifdef __cplusplus
}
#endif

#endif /* CONNECTION_H */
