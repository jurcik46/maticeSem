
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include "connection.h"
#include "matrix.h"
#include "matrixOperations.h"

int main(int argc, char **argv)
{
    char buff[1500];
    memset(buff, '\0', 1500);
    struct Matrix *test = initMatrixStruct(0, 0);
    memset(test, 0, sizeof(struct Matrix));

    if (!createServer(5002))
        return (EXIT_FAILURE);
    printf("A Client connected  successfully\n");
    // read(getSocket(), test, sizeof(struct Matrix));
    // printf("%ld", sizeof(struct Matrix));
    read(getSocket(), test, sizeof(struct Matrix) + 1500);
    // char *buf = malloc((sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    // read(getSocket(), buf, (sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    strncpy(buff, test->matrixPayload, test->payloadLength);
    struct Fraction **testMatrix = allocateMatrix(test->rows, test->columns);
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", test->label, test->rows, test->columns, test->payloadLength, buff);

    convertStringToMatrix(buff, test->rows, test->columns, testMatrix);
    // read(getSocket(), buff, sizeof(buff));
    // printf("%s\n", buff);
    printMatrix(test->rows, test->columns, testMatrix);
    printf("\n");

    struct Matrix *pom = initMatrixStruct(0, 0);
    struct Fraction **pomMatrix = transposeMatrix(test, testMatrix, &pom, pomMatrix);
    printMatrix(pom->rows, pom->columns, pomMatrix);
    printf("\n");

    strcpy(pom->matrixPayload, convertMatrixToString(pom->rows, pom->columns, pomMatrix));
    pom->payloadLength = strlen(pom->matrixPayload);
    write(getSocket(), pom, sizeof(struct Matrix) + strlen(pom->matrixPayload));
    printf("Sending Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", pom->label, pom->rows, pom->columns, pom->payloadLength, pom->matrixPayload);

    // deAllocateMatrix(pom->rows, pom->columns, pom->matrix);
    // free(pom);
    // read(getSocket(), test, sizeof(struct Matrix) + (test->rows * test->columns * sizeof(struct Fraction)));
    // struct Fraction a = (struct Fraction)test->matrix[0][0];
    // printf("%ld  %ld \n", test->matrix[0][0].numerator, test->matrix[0][0].denominator);
    closeServer();
    printf("Connection was closed\n");
    return (EXIT_SUCCESS);
}