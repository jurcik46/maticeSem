
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

    // double mat[N][N] = {{1, 0.5, 3},
    //                     {2, 1, -3},
    //                     {5, 0.2, -0.66666666666666}

    // };
    // display(mat, 3, 3);
    // printf("Determinant of the matrix is : %g",
    //        determinantOfMatrix(mat, N));
    // return (EXIT_SUCCESS);

    // memset(test, 0, sizeof(struct Matrix));
    // struct Fraction o[3][3];
    // o[0][0].numerator = 10, o[0][0].denominator = 10;
    // o[0][1].numerator = 1, o[0][1].denominator = 2;
    // o[0][2].numerator = 3, o[0][2].denominator = 1;
    // o[1][0].numerator = 2, o[1][0].denominator = 1;
    // o[1][1].numerator = 1, o[1][1].denominator = 1;
    // o[1][2].numerator = -3, o[1][2].denominator = 1;
    // o[2][0].numerator = 5, o[2][0].denominator = 1;
    // o[2][1].numerator = 1, o[2][1].denominator = 5;
    // o[2][2].numerator = -2, o[2][2].denominator = 3;

    // struct Fraction k = determinantMatrix(3, 3, o);
    // printf("%ld/%ld\n", k.numerator, k.denominator);
    // return (EXIT_SUCCESS);

    if (!createServer(5002))
        return (EXIT_FAILURE);
    printf("A Client connected  successfully\n");
    // read(getSocket(), test, sizeof(struct Matrix));
    // printf("%ld", sizeof(struct Matrix));

    // char *buf = malloc((sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    // read(getSocket(), buf, (sizeof(struct Fraction) + sizeof(char) * test->rows * test->columns));
    // strncpy(buff, test->matrixPayload, test->payloadLength);
    char buff[1500];
    memset(buff, '\0', 1500);
    struct Matrix *test = initMatrixStruct(0, 0);
    read(getSocket(), buff, 1500);
    test = (struct Matrix *)buff;
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", test->label, test->rows, test->columns, test->payloadLength, test->matrixPayload);

    struct Fraction **testMatrix = allocateMatrix(test->rows, test->columns);

    convertStringToMatrix(test->matrixPayload, test->rows, test->columns, testMatrix);
    // read(getSocket(), buff, sizeof(buff));
    // printf("%s\n", buff);
    printMatrix(test->rows, test->columns, testMatrix);
    printf("\n");

    struct Fraction aaa = determinantMatrix(test->rows, test->rows, testMatrix);
    printf("%ld/%ld\n", aaa.numerator, aaa.denominator);

    closeServer();
    printf("Connection was closed\n");
    return (EXIT_SUCCESS);
    struct Matrix *pom = initMatrixStruct(test->rows, test->columns);
    // struct Fraction **pomMatrix = transposeMatrix(test, testMatrix, &pom, pomMatrix);
    struct Fraction **pomMatrix = additionMatrixs(test, testMatrix, test, testMatrix, pomMatrix);
    if (pomMatrix)
    {
        printMatrix(pom->rows, pom->columns, pomMatrix);
        printf("\n");
        strcpy(pom->matrixPayload, convertMatrixToString(pom->rows, pom->columns, pomMatrix));
        pom->payloadLength = strlen(pom->matrixPayload);
        write(getSocket(), pom, sizeof(struct Matrix) + strlen(pom->matrixPayload));
        printf("Sending Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", pom->label, pom->rows, pom->columns, pom->payloadLength, pom->matrixPayload);
    }

    // deAllocateMatrix(pom->rows, pom->columns, pom->matrix);
    // free(pom);
    // read(getSocket(), test, sizeof(struct Matrix) + (test->rows * test->columns * sizeof(struct Fraction)));
    // struct Fraction a = (struct Fraction)test->matrix[0][0];
    // printf("%ld  %ld \n", test->matrix[0][0].numerator, test->matrix[0][0].denominator);
    closeServer();
    printf("Connection was closed\n");
    return (EXIT_SUCCESS);
}