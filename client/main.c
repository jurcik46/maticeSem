
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#include "connection.h"
#include "matrix.h"

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

void metrixSumMenu()
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
    strcpy(firstMatrixStruct->matrixPayload, convertMatrixToString(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix));
    firstMatrixStruct->payloadLength = strlen(firstMatrixStruct->matrixPayload);
    sendToServer(firstMatrixStruct, sizeof(struct Matrix) + strlen(firstMatrixStruct->matrixPayload));
    system("clear");
    //TODO send to server
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
    strcpy(secondMatrixStruct->matrixPayload, convertMatrixToString(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix));
    secondMatrixStruct->payloadLength = strlen(secondMatrixStruct->matrixPayload);
    sendToServer(secondMatrixStruct, sizeof(struct Matrix) + strlen(secondMatrixStruct->matrixPayload));

    // struct ClientOptions *result = (struct ClientOptions *)readFromSocket();
    // if (result->option == Succes)
    // {
    // strcpy(secondMatrixStruct->matrixPayload, convertMatrixToString(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix));
    // secondMatrixStruct->payloadLength = strlen(secondMatrixStruct->matrixPayload);
    // sendToServer(secondMatrixStruct, sizeof(struct Matrix) + strlen(secondMatrixStruct->matrixPayload));
    system("clear");
    printf("\n--------- Matrix %c ---------\n", firstMatrixStruct->label);

    // printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, firstMatrix);

    printf("\n--------- Matrix %c ---------\n", secondMatrixStruct->label);
    // printMatrix(secondMatrixStruct->rows, secondMatrixStruct->columns, secondMatrix);

    printf("\n---------Result of sum  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);

    waitForEnter();
    // }

    // strcpy(test->matrixPayload, convertMatrixToString(test->rows, test->columns, testMatrix));
    // test->payloadLength = strlen(test->matrixPayload);
    // write(getSocket(), test, sizeof(struct Matrix) + strlen(test->matrixPayload));
}

int main(int argc, char **argv)
{
    if (!createConnetion("127.0.0.1", 5002))
        return (EXIT_FAILURE);

    // char buff[1500];
    // memset(buff, '\0', 1500);
    // struct Matrix *a = initMatrixStruct(0, 0);
    // read(getSocket(), buff, 1500);
    // a = (struct Matrix *)buff;
    // printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", a->label, a->rows, a->columns, a->payloadLength, a->matrixPayload);
    // struct Fraction **aMatrix = allocateMatrix(a->rows, a->columns);

    // convertStringToMatrix(a->matrixPayload, a->rows, a->columns, aMatrix);
    // printMatrix(a->rows, a->columns, aMatrix);
    // write(getSocket(), , (sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    _Bool end = false;
    struct ClientOptions *cOption = calloc(1, sizeof(struct ClientOptions));
    while (!end)
    {
        printMenuOptions();
        switch (getUserInput())
        {
        case '1':
            cOption->option = Sum;
            sendToServerOption(cOption);
            metrixSumMenu();
            break;
        case '2':
            cOption->option = Difference;
            sendToServerOption(cOption);
            break;
        case '3':
            cOption->option = Transpose;
            sendToServerOption(cOption);
            break;
        case '4':
            break;
        case '5':
            break;
        case '0':
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