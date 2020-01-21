
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

// Dimension of input square matrix
// #define N 3

// /* function for displaying the matrix */
// void display(double mat[N][N], int row, int col)
// {
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//             printf("  %g  ", mat[i][j]);
//         printf("\n");
//     }
// }

// // Function to get cofactor of mat[p][q] in temp[][]. n is current
// // dimension of mat[][]
// void getCofactor(double mat[N][N], double temp[N][N], int p, int q, int n)
// {
//     int i = 0, j = 0;

//     // Looping for each element of the matrix
//     for (int row = 0; row < n; row++)
//     {
//         for (int col = 0; col < n; col++)
//         {
//             // Copying into temporary matrix only those element
//             // which are not in given row and column
//             if (row != p && col != q)
//             {
//                 temp[i][j++] = mat[row][col];

//                 // Row is filled, so increase row index and
//                 // reset col index
//                 if (j == n - 1)
//                 {
//                     j = 0;
//                     i++;
//                 }
//             }
//         }
//     }
// }

// /* Recursive function for finding determinant of matrix.
// n is current dimension of mat[][]. */
// double determinantOfMatrix(double mat[N][N], int n)
// {
//     double D = 0; // Initialize result
//     printf("----------------------------------RC %d------------------------\n", n);

//     display(mat, n, n);
//     printf("----------------------------------RC %d------------------------\n", n);

//     // Base case : if matrix contains single element
//     if (n == 1)
//         return mat[0][0];

//     double temp[N][N]; // To store cofactors

//     int sign = 1; // To store sign multiplier

//     // Iterate for each element of first row
//     for (int f = 0; f < n; f++)
//     {
//         // Getting Cofactor of mat[0][f]
//         getCofactor(mat, temp, 0, f, n);
//         D += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);

//         // terms are to be added with alternate sign
//         sign = -sign;
//         printf("D %g, sign %g \n", D, sign);
//     }

//     return D;
// }
// void cofatorMatrix(int rcFix, int rc, struct Fraction matrix[rcFix][rcFix], struct Fraction tempMatrix[rcFix][rcFix], int p, int q)
// {
//     int i = 0, j = 0;

//     for (int row = 0; row < rc; row++)
//     {
//         for (int col = 0; col < rc; col++)
//         {
//             //  Copying into temporary matrix only those element
//             //  which are not in given row and column
//             if (row != p && col != q)
//             {
//                 tempMatrix[i][j++] = matrix[row][col];
//                 // printf("I %d J: %d  ROW: %d COL: %d  tempMatrix: %ld/%ld oldMatrix: %ld/%ld\n", i, j, row, col, tempMatrix[i][j - 1].numerator, tempMatrix[i][j - 1].denominator, matrix[row][col].numerator, matrix[row][col].denominator);

//                 // tempMatrix[i][j++].numerator = matrix[row][col].numerator;
//                 // tempMatrix[i][j++].denominator = matrix[row][col].denominator;

//                 // Row is filled, so increase row index and
//                 // reset col index
//                 if (j == rc - 1)
//                 {
//                     j = 0;
//                     i++;
//                 }
//             }
//         }
//     }
// }
// struct Fraction determinantMatrix(uint32_t rcFix, uint32_t rc, struct Fraction matrix[rcFix][rcFix])
// {
//     printf("----------------------------------RC %d------------------------\n", rc);
//     printMatrixA(3, matrix);
//     printf("----------------------------------RC %d------------------------\n", rc);

//     if (rc == 1)
//     {
//         return (matrix[0][0]);
//     }
//     struct Fraction sign, det;
//     det.numerator = 0, det.denominator = 1;
//     sign.numerator = 1, sign.denominator = 1;
//     struct Fraction tempMatrix[rcFix][rcFix];

//     // for (int i = 0; i < rc; i++)
//     // {
//     //     for (int j = 0; j < rc; j++)
//     //     {
//     //         tempMatrix[i][j].numerator = 0;
//     //         tempMatrix[i][j].denominator = 1;
//     //     }
//     // }
//     // if (matrixStruct->rows != matrixStruct->columns)
//     // { // TODO check this in main
//     //     perror("The matrix must be square to calculate the determinant!");
//     //     return det;
//     // }
//     for (int f = 0; f < rc; f++)
//     {
//         cofatorMatrix(rcFix, rc, matrix, tempMatrix, 0, f);
//         // printf("----------------------------------F=%d***** %d------------------------\n", f, rc);
//         // printMatrixA(rc, tempMatrix);
//         // printf("----------------------------------F=%d****** %d------------------------\n", f, rc);

//         // printf("----------------------------------TEMP RC %d------------------------\n", rc);
//         // printMatrixA(rc, tempMatrix);
//         // printf("----------------------------------TEMP RC %d------------------------\n", rc);
//         struct Fraction firstPart = multiplicationFraction(sign, matrix[0][f]);
//         struct Fraction secndPart = multiplicationFraction(firstPart, determinantMatrix(rcFix, rc - 1, tempMatrix));
//         det = additionFraction(det, secndPart);
//         sign.numerator = -sign.numerator;
//         // sign.denominator = -sign.denominator;
//         printf("D %ld/%ld, sign %ld/%ld \n", det.numerator, det.denominator, sign.numerator, sign.denominator);
//     }

//     return (det);
// }

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