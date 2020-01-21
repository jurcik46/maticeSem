
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
#include "matrixOperations.h"

void printRawMatrixStruct(struct Matrix *matrixStruc)
{
    printf("Recieved Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", matrixStruc->label, matrixStruc->rows, matrixStruc->columns, matrixStruc->payloadLength, matrixStruc->matrixPayload);
}
int main(int argc, char **argv)
{

    if (!createServer(5002))
        return (EXIT_FAILURE);
    printf("A Client connected  successfully\n");

    _Bool end = false;

    while (!end)
    {
        struct ClientOptions *cOptions = (struct ClientOptions *)readFromSocket();
        struct Matrix *firstMatrixStruct;
        struct Fraction **firstMatrix;
        struct Matrix *secondMatrixStruct;
        struct Fraction **secondMatrix;
        struct Fraction **resultMatrix;
        switch (cOptions->option)
        {
        case Sum:
            firstMatrixStruct = initMatrixStruct(0, 0);
            firstMatrixStruct = (struct Matrix *)readFromSocket();
            printRawMatrixStruct(firstMatrixStruct);
            // sendToClientSuccesOrFailed(Succes);
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

            printf("\n---------Result of sum  Matrix %c and Matrix %c ---------\n", firstMatrixStruct->label, secondMatrixStruct->label);
            //TODO check same row a c lengt
            resultMatrix = additionMatrixs(firstMatrixStruct, firstMatrix, secondMatrixStruct, secondMatrix, resultMatrix);
            printMatrix(firstMatrixStruct->rows, firstMatrixStruct->columns, resultMatrix);
            // sendToClientSuccesOrFailed(Succes);
            printf("SUM\n");
            break;
        case Difference:
            printf("ddd\n");
            break;
        case Transpose:
            printf("ttt\n");
            break;
        case Determinant:
            break;
        case Inverse:
            break;
        case End:
            end = true;
            break;
        default:
            printf("The selected option does not exist\n");
        }
    }

    // struct Matrix *test = initMatrixStruct(0, 0);

    // test = (struct Matrix *)buff;

    // struct Fraction **testMatrix = allocateMatrix(test->rows, test->columns);

    // convertStringToMatrix(test->matrixPayload, test->rows, test->columns, testMatrix);
    // // read(getSocket(), buff, sizeof(buff));
    // // printf("%s\n", buff);
    // printMatrix(test->rows, test->columns, testMatrix);
    // printf("\n");

    // // struct Fraction aaa = determinantMatrix(test->rows, test->rows, testMatrix);
    // // printf("%ld/%ld\n", aaa.numerator, aaa.denominator);

    // // closeServer();
    // // printf("Connection was closed\n");
    // // return (EXIT_SUCCESS);
    // struct Matrix *pom = initMatrixStruct(test->rows, test->columns);
    // // struct Fraction **pomMatrix = transposeMatrix(test, testMatrix, &pom, pomMatrix);
    // // struct Fraction **pomMatrix;
    // struct Fraction **pomMatrix = inverseMatrix(test->rows, testMatrix, pomMatrix);
    // // _Bool re = inverseMatrix(pom->rows, testMatrix, pomMatrix);
    // // printMatrix(pom->rows, pom->columns, pomMatrix);

    // if (pomMatrix)
    // {
    //     printMatrix(pom->rows, pom->columns, pomMatrix);
    //     printf("\n");
    //     strcpy(pom->matrixPayload, convertMatrixToString(pom->rows, pom->columns, pomMatrix));
    //     pom->payloadLength = strlen(pom->matrixPayload);
    //     write(getSocket(), pom, sizeof(struct Matrix) + strlen(pom->matrixPayload));
    //     printf("Sending Label: %c Rows: %d  Columns: %d Payload length: %d  Data: %s \n", pom->label, pom->rows, pom->columns, pom->payloadLength, pom->matrixPayload);
    // }

    // deAllocateMatrix(pom->rows, pom->columns, pom->matrix);
    // free(pom);
    // read(getSocket(), test, sizeof(struct Matrix) + (test->rows * test->columns * sizeof(struct Fraction)));
    // struct Fraction a = (struct Fraction)test->matrix[0][0];
    // printf("%ld  %ld \n", test->matrix[0][0].numerator, test->matrix[0][0].denominator);
    closeServer();
    printf("Connection was closed\n");
    return (EXIT_SUCCESS);
}