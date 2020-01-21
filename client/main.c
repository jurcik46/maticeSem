
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>

#define _DEBUG
#include "connection.h"
#include "matrix.h"
#include "CMemLeak.h"

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do
    {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void waitForEnter()
{
    printf("\nPress Enter to continue....");
    while (!getchar())
    {
    }
}

char getUserInput()
{
    char selectedOptions = getchar();
    getchar();
    return selectedOptions;
}
void printMenuOptions()
{
    system("clear");
    printf("\n--------- Select an option from the menu. ---------");
    printf("\n'1'->\tSum of matrices A + B");
    printf("\n'2'->\tDifference of matrices A - B");
    printf("\n'3'->\tTranspose matrix");
    printf("\n'4'->\tDeterminant of matrix");
    printf("\n'5'->\tInverse matrix");
    printf("\n'0'->\tExit       \n");
}

void printRawMatrixStruct(struct Matrix *matrixStruc)
{
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", matrixStruc->label, matrixStruc->rows, matrixStruc->columns, matrixStruc->payloadLength, matrixStruc->matrixPayload);
}

void matrixInverseMenu(struct ClientOptions *clientOption)
{
    system("clear");
    printf("\n--------- Select the  matrix from the file. ---------\n");
    struct Matrix *firstMatrixStruct = initMatrixStruct(0, 0);

    firstMatrixStruct->label = getUserInput();
    struct Fraction **firstMatrix = loadMatrixFromFile(firstMatrixStruct, firstMatrix);
    if (firstMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %c \n", firstMatrixStruct->label);
        free(firstMatrixStruct);
        waitForEnter();
        return;
    }

    // system("clear");
    printf("\n---------  Matrix %c ---------\n", firstMatrixStruct->label);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    if (firstMatrixStruct->rows != firstMatrixStruct->columns)
    {
        fprintf(stderr, " The matrix must be square to calculate the determinant!  \n");
        waitForEnter();
        return;
    }
    sendToServerOption(clientOption);
    msleep(200);
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + firstMatrixStruct->payloadLength);

    struct Matrix *resultMatrixStruct = (struct Matrix *)readFromSocket();
    struct Fraction **resultMatrix;
    printRawMatrixStruct(resultMatrixStruct);
    if (resultMatrixStruct->rows == 0 && resultMatrixStruct->columns == 0)
    {

        fprintf(stderr, " Singular matrix, can't find its inverse!  \n");
        waitForEnter();
        return;
    }

    resultMatrix = allocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns);
    convertStringToMatrix(resultMatrixStruct->matrixPayload, resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    printf("\n--------- Inverse  Matrix %c ---------\n", firstMatrixStruct->label);
    printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    // free(firstMatrixStruct);
    // deAllocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    // free(firstMatrixStruct);
    // deAllocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    waitForEnter();
}
void matrixDeterminantMenu(struct ClientOptions *clientOption)
{
    system("clear");
    printf("\n--------- Select the  matrix from the file. ---------\n");
    struct Matrix *firstMatrixStruct = initMatrixStruct(0, 0);

    firstMatrixStruct->label = getUserInput();
    struct Fraction **firstMatrix = loadMatrixFromFile(firstMatrixStruct, firstMatrix);
    if (firstMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %c \n", firstMatrixStruct->label);
        free(firstMatrixStruct);
        waitForEnter();
        return;
    }
    printf("\n---------  Matrix %c ---------\n", firstMatrixStruct->label);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    if (firstMatrixStruct->rows != firstMatrixStruct->columns)
    {
        fprintf(stderr, " The matrix must be square to calculate the determinant! \n");
        waitForEnter();
        return;
    }
    sendToServerOption(clientOption);
    msleep(200);
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + firstMatrixStruct->payloadLength);
    struct Fraction *determinant = (struct Matrix *)readFromSocket();
    printf("\n---------Determinant of Matrix %c  is %ld/%ld---------\n", firstMatrixStruct->label, determinant->numerator, determinant->denominator);
    waitForEnter();
    free(determinant);

    // system("clear");
}
void matrixTransposeMenu(struct ClientOptions *clientOption)
{
    system("clear");
    printf("\n--------- Select the  matrix from the file. ---------\n");
    struct Matrix *firstMatrixStruct = initMatrixStruct(0, 0);

    firstMatrixStruct->label = getUserInput();
    struct Fraction **firstMatrix = loadMatrixFromFile(firstMatrixStruct, firstMatrix);
    if (firstMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %c \n", firstMatrixStruct->label);
        free(firstMatrixStruct);
        waitForEnter();
        return;
    }
    sendToServerOption(clientOption);
    msleep(200);
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + firstMatrixStruct->payloadLength);
    // system("clear");
    printf("\n---------  Matrix %c ---------\n", firstMatrixStruct->label);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);

    struct Matrix *resultMatrixStruct = (struct Matrix *)readFromSocket();
    struct Fraction **resultMatrix;
    printRawMatrixStruct(resultMatrixStruct);
    resultMatrix = allocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns);

    convertStringToMatrix(resultMatrixStruct->matrixPayload, resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    printf("\n---------Transpose  Matrix %c ---------\n", firstMatrixStruct->label);
    printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    // free(firstMatrixStruct);
    // deAllocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    // free(firstMatrixStruct);
    // deAllocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    waitForEnter();
}
void matrixDiffMenu(struct ClientOptions *clientOption)
{
    system("clear");
    printf("\n--------- Select the first matrix from the file. ---------\n");

    struct Matrix *firstMatrixStruct = initMatrixStruct(0, 0);

    firstMatrixStruct->label = getUserInput();
    struct Fraction **firstMatrix = loadMatrixFromFile(firstMatrixStruct, firstMatrix);
    if (firstMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %c \n", firstMatrixStruct->label);
        free(firstMatrixStruct);
        waitForEnter();
        return;
    }
    // system("clear");
    printf("\n--------- First Matrix %c ---------\n", firstMatrixStruct->label);

    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printf("\n--------- Select the second matrix from the file. ---------\n");

    struct Matrix *secondMatrixStruct = initMatrixStruct(0, 0);

    secondMatrixStruct->label = getUserInput();
    struct Fraction **secondMatrix = loadMatrixFromFile(secondMatrixStruct, secondMatrix);
    if (secondMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %C \n", secondMatrixStruct->label);
        free(secondMatrixStruct);
        waitForEnter();
        return;
    }
    printf("\n--------- Second Matrix %c ---------\n", secondMatrixStruct->label);
    printMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    if (firstMatrixStruct->rows != secondMatrixStruct->rows || firstMatrixStruct->columns != secondMatrixStruct->columns)
    {
        fprintf(stderr, " We need matrices with the same number of elements to divide the matrices  \n");
        waitForEnter();
        return;
    }
    sendToServerOption(clientOption);
    msleep(200);
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + firstMatrixStruct->payloadLength);
    struct ClientOptions *result = (struct ClientOptions *)readFromSocket();
    if (result->option == Succes)
    {
        strcpy(secondMatrixStruct->matrixPayload, convertMatrixToString(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix));
        secondMatrixStruct->payloadLength = strlen(secondMatrixStruct->matrixPayload);
        sendToServer(secondMatrixStruct, sizeof(struct Matrix) + secondMatrixStruct->payloadLength);
        // system("clear");
        struct Matrix *resultMatrixStruct = (struct Matrix *)readFromSocket();
        struct Fraction **resultMatrix;
        printRawMatrixStruct(resultMatrixStruct);
        resultMatrix = allocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns);

        convertStringToMatrix(resultMatrixStruct->matrixPayload, resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
        printf("\n---------Result of Difference  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);
        printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    }
    free(result);
    waitForEnter();
}
void matrixSumMenu(struct ClientOptions *clientOption)
{
    system("clear");
    printf("\n--------- Select the first matrix from the file. ---------\n");

    struct Matrix *firstMatrixStruct = initMatrixStruct(0, 0);

    firstMatrixStruct->label = getUserInput();
    struct Fraction **firstMatrix = loadMatrixFromFile(firstMatrixStruct, firstMatrix);
    if (firstMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %c \n", firstMatrixStruct->label);
        free(firstMatrixStruct);
        waitForEnter();
        return;
    }
    // system("clear");
    printf("\n--------- First Matrix %c ---------\n", firstMatrixStruct->label);

    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printf("\n--------- Select the second matrix from the file. ---------\n");

    struct Matrix *secondMatrixStruct = initMatrixStruct(0, 0);

    secondMatrixStruct->label = getUserInput();
    struct Fraction **secondMatrix = loadMatrixFromFile(secondMatrixStruct, secondMatrix);

    if (secondMatrix == NULL)
    {
        fprintf(stderr, "Failed to load matrix from file. Matrix: %C \n", secondMatrixStruct->label);
        free(secondMatrixStruct);
        waitForEnter();
        return;
    }

    printf("\n--------- Second Matrix %c ---------\n", secondMatrixStruct->label);
    printMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    if (firstMatrixStruct->rows != secondMatrixStruct->rows || firstMatrixStruct->columns != secondMatrixStruct->columns)
    {
        fprintf(stderr, " We need matrices with the same number of elements to sum the matrices  \n");
        waitForEnter();
        return;
    }
    sendToServerOption(clientOption);
    msleep(200);
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + firstMatrixStruct->payloadLength);
    struct ClientOptions *result = (struct ClientOptions *)readFromSocket();
    if (result->option == Succes)
    {
        strcpy(secondMatrixStruct->matrixPayload, convertMatrixToString(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix));
        secondMatrixStruct->payloadLength = strlen(secondMatrixStruct->matrixPayload);
        sendToServer(secondMatrixStruct, sizeof(struct Matrix) + secondMatrixStruct->payloadLength);
        // system("clear");
        struct Matrix *resultMatrixStruct = (struct Matrix *)readFromSocket();
        struct Fraction **resultMatrix;
        printRawMatrixStruct(resultMatrixStruct);
        resultMatrix = allocateMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns);

        convertStringToMatrix(resultMatrixStruct->matrixPayload, resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
        printf("\n---------Result of sum  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);
        printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
        // deAllocateMatrix(5, 5, resultMatrix);
        free(resultMatrixStruct);
    }
    // free(result);
    // free(firstMatrixStruct);
    // free(secondMatrixStruct);
    waitForEnter();

    // strcpy(test->matrixPayload, convertMatrixToString(test->rows, test->columns, testMatrix));
    // test->payloadLength = strlen(test->matrixPayload);
    // write(getSocket(), test, sizeof(struct Matrix) + strlen(test->matrixPayload));
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "Klienta je nutne spustit s nasledujucimi argumentmi: adresa port.\n");
    }

    //ziskanie adresy a portu servera <netdb.h>
    struct hostent *server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Server neexistuje.\n");
    }

    int port = atoi(argv[2]);
    if (port <= 0)
    {
        fprintf(stderr, "Port musi byt cele cislo vacsie ako 0.\n");
    }
    if (!createConnetion(argv[1], port))
        return (EXIT_FAILURE);

    _Bool end = false;
    struct ClientOptions *cOption = calloc(1, sizeof(struct ClientOptions));
    while (!end)
    {
        printMenuOptions();
        switch (getUserInput())
        {
        case '1':
            cOption->option = Sum;
            matrixSumMenu(cOption);
            break;
        case '2':
            cOption->option = Difference;
            matrixDiffMenu(cOption);
            break;
        case '3':
            cOption->option = Transpose;
            matrixTransposeMenu(cOption);
            break;
        case '4':
            cOption->option = Determinant;
            matrixDeterminantMenu(cOption);
            break;
        case '5':
            cOption->option = Inverse;
            matrixInverseMenu(cOption);
            break;
        case '0':
            cOption->option = End;
            sendToServerOption(cOption);
            end = true;
            break;
        default:
            printf("The selected option does not exist\n");
            waitForEnter();
        }
    }
    free(cOption);
    closeConnection();
    printf("Connection was closed\n");
    return 0;
}