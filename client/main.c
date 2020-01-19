
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

void waitForEnter()
{
    printf("\nPress Enter to continue....");
    while (!getchar())
    {
    }
    getchar();
}

char getUserInput()
{
    char selectedOptions = getchar();
    getchar();
    return selectedOptions;
}

int main(int argc, char **argv)
{
    if (!createConnetion("127.0.0.1", 5002))
        return (EXIT_FAILURE);
    struct Matrix *test = initMatrixStruct(0, 0);

    test->label = 'A';
    struct Fraction **testMatrix = loadMatrixFromFile(test, testMatrix);
    if (testMatrix != NULL)
    {
        printMatrix(test->rows, test->columns, testMatrix);
        // deAllocateMatrix(test->rows, test->columns, &test->matrix);
        // free(test);
        // return (EXIT_SUCCESS);
    }
    strcpy(test->matrixPayload, convertMatrixToString(test->rows, test->columns, testMatrix));
    // return (EXIT_FAILURE);
    // convertMatrix(test->rows, test->columns, test);
    // printMatrix(test->rows, test->columns, test->matrix);

    // printf("%d", sizeof(struct Fraction));
    // write(getSocket(), test, sizeof(test) + (sizeof(struct Fraction) * test->rows * test->columns));
    // int a = (sizeof(struct Fraction) * test->rows * test->columns);
    // printf("%s", sendMatrix(test->rows, test->columns, test->matrix));
    // printf("%s \n", test->matrixPayload);
    // printf("aaaa %d %d  %d", sizeof(struct Matrix), strlen(test->matr9ixPayload), sizeof(test->matrix));
    test->payloadLength = strlen(test->matrixPayload);
    write(getSocket(), test, sizeof(struct Matrix) + strlen(test->matrixPayload));

    // a->matrix = allocateMatrix(4, 6);

    // memset(a, 0, sizeof(struct Matrix));

    // memcpy(a, buff, sizeof(struct Matrix));
    // char *ab = malloc(sizeof(a->payloadLength));
    // memcpy(a, buff, sizeof(struct Matrix) + a -);
    // read(getSocket(), a, sizeof(struct Matrix));
    // strncpy(buff, a->matrixPayload, a->payloadLength);
    char buff[1500];
    memset(buff, '\0', 1500);
    struct Matrix *a = initMatrixStruct(0, 0);
    read(getSocket(), buff, 1500);
    a = (struct Matrix *)buff;
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", a->label, a->rows, a->columns, a->payloadLength, a->matrixPayload);
    struct Fraction **aMatrix = allocateMatrix(a->rows, a->columns);

    convertStringToMatrix(a->matrixPayload, a->rows, a->columns, aMatrix);
    printMatrix(a->rows, a->columns, aMatrix);
    // write(getSocket(), , (sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    return (EXIT_SUCCESS);
    _Bool end = false;
    char selectedOptions;
    while (!end)
    {
        printMenuOptions();
        switch (getUserInput())
        {
        case '1':
            printf("%c", selectedOptions);
            break;
        case '2':
            break;
        case '3':
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

    closeConnection();
    printf("Connection was closed\n");
    return 0;
}