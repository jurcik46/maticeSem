#ifndef CONNECTION_H
#define CONNECTION_H
#ifdef __cplusplus
extern "C"
{
#endif

#define BUFFER_SIZE 1500

    typedef enum
    {
        Sum,
        Difference,
        Transpose,
        Determinant,
        Inverse,
        End,
        Failed,
        Succes,
    } OPTIONS;
    struct ClientOptions
    {
        OPTIONS option;
    } __attribute__((packed));

    char buffer[BUFFER_SIZE];
    _Bool createServer(int port);
    void closeServer();
    char *readFromSocket();
    void sendToClientSuccesOrFailed(OPTIONS result);

#ifdef __cplusplus
}
#endif

#endif /* CONNECTION_H */
