
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#define _DEBUG

#include "connection.h"
#include "matrix.h"
#include "matrixOperations.h"
#include "CMemLeak.h"

void printRawMatrixStruct(struct Matrix *matrixStruc)
{
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", matrixStruc->label, matrixStruc->rows, matrixStruc->columns, matrixStruc->payloadLength, matrixStruc->matrixPayload);
}

void matrixInverseMenu()
{
    system("clear");
    struct Matrix *firstMatrixStruct;
    struct Fraction **firstMatrix;
    struct Matrix *resultMatrixStruct;
    struct Fraction **resultMatrix;
    firstMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(firstMatrixStruct);
    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);
    firstMatrix = allocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns);
    convertStringToMatrix(firstMatrixStruct->matrixPayload, firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    resultMatrixStruct = initMatrixStruct(firstMatrixStruct->rows, firstMatrixStruct->columns);
    resultMatrixStruct->label = firstMatrixStruct->label;
    resultMatrix = inverseMatrix(firstMatrixStruct->rows, firstMatrix, resultMatrix);
    if (resultMatrix != NULL)
    {
        printf("\n--------- Inverse  Matrix %c  ---------\n", resultMatrixStruct->label);
        printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
        strcpy(resultMatrixStruct->matrixPayload, convertMatrixToString(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix));
        resultMatrixStruct->payloadLength = strlen(resultMatrixStruct->matrixPayload);
        sendToClient(resultMatrixStruct, sizeof(struct Matrix) + resultMatrixStruct->payloadLength);
    }
    else
    {
        resultMatrixStruct->rows = 0;
        resultMatrixStruct->columns = 0;
        strcpy(resultMatrixStruct->matrixPayload, convertMatrixToString(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix));
        resultMatrixStruct->payloadLength = strlen(resultMatrixStruct->matrixPayload);
        sendToClient(resultMatrixStruct, sizeof(struct Matrix) + resultMatrixStruct->payloadLength);
    }
}

void matrixDeterminantMenu()
{
    system("clear");
    struct Matrix *firstMatrixStruct;
    struct Fraction **firstMatrix;
    firstMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(firstMatrixStruct);
    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);
    firstMatrix = allocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns);
    convertStringToMatrix(firstMatrixStruct->matrixPayload, firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);

    struct Fraction determinant = determinantMatrix(firstMatrixStruct->rows, firstMatrixStruct->rows, firstMatrix);
    printf("\n---------Determinant of Matrix %c  is %ld/%ld---------\n", firstMatrixStruct->label, determinant.numerator, determinant.denominator);
    sendToClient(&determinant, sizeof(struct Fraction));
}

void matrixTransposeMenu()
{
    system("clear");
    struct Matrix *firstMatrixStruct;
    struct Fraction **firstMatrix;
    struct Matrix *resultMatrixStruct;
    struct Fraction **resultMatrix;
    firstMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(firstMatrixStruct);
    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);
    firstMatrix = allocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns);
    convertStringToMatrix(firstMatrixStruct->matrixPayload, firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    resultMatrixStruct = initMatrixStruct(0, 0);
    resultMatrixStruct->label = firstMatrixStruct->label;
    resultMatrix = transposeMatrix(firstMatrixStruct, firstMatrix, &resultMatrixStruct, resultMatrix);
    printf("\n---------Transpose  Matrix %c  ---------\n", resultMatrixStruct->label);

    printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    strcpy(resultMatrixStruct->matrixPayload, convertMatrixToString(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix));
    resultMatrixStruct->payloadLength = strlen(resultMatrixStruct->matrixPayload);
    sendToClient(resultMatrixStruct, sizeof(struct Matrix) + resultMatrixStruct->payloadLength);
}
void matrixDiffMenu()
{
    system("clear");

    struct Matrix *firstMatrixStruct;
    struct Fraction **firstMatrix;
    struct Matrix *secondMatrixStruct;
    struct Fraction **secondMatrix;
    struct Matrix *resultMatrixStruct;
    struct Fraction **resultMatrix;
    // firstMatrixStruct = initMatrixStruct(0, 0);
    firstMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(firstMatrixStruct);
    sendToClientSuccesOrFailed(Succes);
    // secondMatrixStruct = initMatrixStruct(0, 0);
    secondMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(secondMatrixStruct);

    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);
    firstMatrix = allocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns);
    convertStringToMatrix(firstMatrixStruct->matrixPayload, firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printf("\n");
    printf("\n--------- Matrix %c ---------\n", secondMatrixStruct->label);
    secondMatrix = allocateMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns);
    convertStringToMatrix(secondMatrixStruct->matrixPayload, secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    printMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    printf("\n");

    printf("\n---------Result of Difference  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);
    resultMatrixStruct = initMatrixStruct(firstMatrixStruct->rows, firstMatrixStruct->columns);
    resultMatrixStruct->label = 'R';
    resultMatrix = substractionMatrixs(firstMatrixStruct, firstMatrix, secondMatrixStruct, secondMatrix, resultMatrix);
    printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    // sendToClientSuccesOrFailed(Succes);
    strcpy(resultMatrixStruct->matrixPayload, convertMatrixToString(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix));
    resultMatrixStruct->payloadLength = strlen(resultMatrixStruct->matrixPayload);
    sendToClient(resultMatrixStruct, sizeof(struct Matrix) + resultMatrixStruct->payloadLength);
}
void matrixSumMenu()
{
    system("clear");

    struct Matrix *firstMatrixStruct;
    struct Fraction **firstMatrix;
    struct Matrix *secondMatrixStruct;
    struct Fraction **secondMatrix;

    firstMatrixStruct = initMatrixStruct(0, 0);
    firstMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(firstMatrixStruct);
    sendToClientSuccesOrFailed(Succes);
    secondMatrixStruct = initMatrixStruct(0, 0);
    secondMatrixStruct = (struct Matrix *)readFromSocket();
    printRawMatrixStruct(secondMatrixStruct);

    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);
    firstMatrix = allocateMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns);
    convertStringToMatrix(firstMatrixStruct->matrixPayload, firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);
    printf("\n");
    printf("\n--------- Matrix %c ---------\n", secondMatrixStruct->label);
    secondMatrix = allocateMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns);
    convertStringToMatrix(secondMatrixStruct->matrixPayload, secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    printMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);
    printf("\n");
    struct Matrix *resultMatrixStruct;
    struct Fraction **resultMatrix;
    printf("\n---------Result of Sum  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);

    resultMatrixStruct = initMatrixStruct(firstMatrixStruct->rows, firstMatrixStruct->columns);
    resultMatrixStruct->label = 'R';
    resultMatrix = additionMatrixs(firstMatrixStruct, firstMatrix, secondMatrixStruct, secondMatrix, resultMatrix);
    printMatrix(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix);
    // sendToClientSuccesOrFailed(Succes);
    strcpy(resultMatrixStruct->matrixPayload, convertMatrixToString(resultMatrixStruct->rows, resultMatrixStruct->columns, resultMatrix));
    resultMatrixStruct->payloadLength = strlen(resultMatrixStruct->matrixPayload);
    sendToClient(resultMatrixStruct, sizeof(struct Matrix) + resultMatrixStruct->payloadLength);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Sever je nutne spustit s nasledujucimi argumentmi: port.\n");
    }
    int port = atoi(argv[1]);
    if (port <= 0)
    {
        fprintf(stderr, "Port musi byt cele cislo vacsie ako 0.\n");
    }

    if (!createServer(5002))
        return (EXIT_FAILURE);
    printf("A Client connected  successfully\n");

    _Bool end = false;

    while (!end)
    {
        struct ClientOptions *cOptions = (struct ClientOptions *)readFromSocket();

        switch (cOptions->option)
        {
        case Sum:
            matrixSumMenu();
            break;
        case Difference:
            matrixDiffMenu();
            break;
        case Transpose:
            matrixTransposeMenu();
            break;
        case Determinant:
            matrixDeterminantMenu();
            break;
        case Inverse:
            matrixInverseMenu();
            break;
        case End:
            end = true;
            break;
        default:
            printf("The selected option does not exist\n");
        }
    }

    closeServer();
    printf("Connection was closed\n");
    return (EXIT_SUCCESS);
}