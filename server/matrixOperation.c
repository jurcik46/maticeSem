#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"
#include "matrixOperations.h"

_Bool denominatorZero;
struct Fraction **transposeMatrix(const struct Matrix *matrixStructSource, const struct Fraction **matrixSource, struct Matrix **matrixStructDestination, struct Fraction **matrixDestination)
{
    *matrixStructDestination = initMatrixStruct(matrixStructSource->columns, matrixStructSource->rows);
    matrixDestination = allocateMatrix(matrixStructSource->columns, matrixStructSource->rows);
    for (int i = 0; i < matrixStructSource->columns; i++)
    {
        for (int j = 0; j < matrixStructSource->rows; j++)
        {
            matrixDestination[i][j] = matrixSource[j][i];
        }
    }
    return matrixDestination;
}

struct Fraction **additionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result)
{
    if (matrixStructA->rows == matrixStructB->rows && matrixStructA->columns == matrixStructB->columns)
    {
        result = allocateMatrix(matrixStructA->rows, matrixStructA->columns);

        for (int i = 0; i < matrixStructA->rows; i++)
        {
            for (int j = 0; j < matrixStructA->columns; j++)
            {

                // result. = a->matica[i][j] + b->matica[i][j];
                if (matrixA[i][j].denominator == 0 || matrixB[i][j].denominator == 0)
                {
                    return NULL;
                }
                result[i][j] = additionFraction(matrixA[i][j], matrixB[i][j]);

                // result[i][j].denominator = nsn(matrixA[i][j].denominator, matrixB[i][j].denominator);
                // result[i][j].numerator = result[i][j].denominator / matrixA[i][j].denominator * matrixA[i][j].numerator + result[i][j].denominator / matrixB[i][j].denominator * matrixB[i][j].numerator;
                // fixFraction(&result[i][j]);
            }
        }
        return result;
    }
    perror("We need matrices with the same number of elements to sum the matrices.\n");
    return NULL;
}

struct Fraction **substractionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result)
{
    if (matrixStructA->rows == matrixStructB->rows && matrixStructA->columns == matrixStructB->columns)
    {
        result = allocateMatrix(matrixStructA->rows, matrixStructA->columns);

        for (int i = 0; i < matrixStructA->rows; i++)
        {
            for (int j = 0; j < matrixStructA->columns; j++)
            {

                // result. = a->matica[i][j] + b->matica[i][j];
                if (matrixA[i][j].denominator == 0 || matrixB[i][j].denominator == 0)
                {
                    return NULL;
                }
                result[i][j].denominator = nsn(matrixA[i][j].denominator, matrixB[i][j].denominator);
                result[i][j].numerator = result[i][j].denominator / matrixA[i][j].denominator * matrixA[i][j].numerator - result[i][j].denominator / matrixB[i][j].denominator * matrixB[i][j].numerator;
                fixFraction(&result[i][j]);
            }
        }
        return result;
    }
    perror("We need matrices with the same number of elements to substraction the matrices.\n");
    return NULL;
}

void cofatorMatrix(int rcFix, int rc, struct Fraction matrix[rcFix][rcFix], struct Fraction tempMatrix[rcFix][rcFix], int p, int q)
{
    int i = 0, j = 0;

    for (int row = 0; row < rc; row++)
    {
        for (int col = 0; col < rc; col++)
        {
            //  Copying into temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                tempMatrix[i][j++] = matrix[row][col];
                // printf("I %d J: %d  ROW: %d COL: %d  tempMatrix: %ld/%ld oldMatrix: %ld/%ld\n", i, j, row, col, tempMatrix[i][j - 1].numerator, tempMatrix[i][j - 1].denominator, matrix[row][col].numerator, matrix[row][col].denominator);

                // tempMatrix[i][j++].numerator = matrix[row][col].numerator;
                // tempMatrix[i][j++].denominator = matrix[row][col].denominator;

                // Row is filled, so increase row index and
                // reset col index
                if (j == rc - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

struct Fraction determinantMatrix(uint32_t rcFix, uint32_t rc, struct Fraction matrix[rcFix][rcFix])
{
    // printMatrix(rc, rc, matrix);
    printf("----------------------------------RC %d------------------------\n", rc);
    printMatrixA(rc, matrix);
    printf("----------------------------------RC %d------------------------\n", rc);
    if (rc == 1)
    {
        return (matrix[0][0]);
    }
    struct Fraction sign, det;
    det.numerator = 0, det.denominator = 1;
    sign.numerator = 1, sign.denominator = 1;
    struct Fraction tempMatrix[rcFix][rcFix];

    // for (int i = 0; i < rc; i++)
    // {
    //     for (int j = 0; j < rc; j++)
    //     {
    //         tempMatrix[i][j].numerator = 0;
    //         tempMatrix[i][j].denominator = 1;
    //     }
    // }
    // if (matrixStruct->rows != matrixStruct->columns)
    // { // TODO check this in main
    //     perror("The matrix must be square to calculate the determinant!");
    //     return det;
    // }
    for (int f = 0; f < rc; f++)
    {
        cofatorMatrix(rcFix, rc, matrix, tempMatrix, 0, f);
        // printf("---------------------------------- %d------------------------\n", rc);
        // printMatrixA(rc, tempMatrix);
        // printf("---------------------------------- %d------------------------\n", rc);

        // printf("----------------------------------TEMP RC %d------------------------\n", rc);
        // printMatrixA(rc, tempMatrix);
        // printf("----------------------------------TEMP RC %d------------------------\n", rc);
        struct Fraction firstPart = multiplicationFraction(sign, matrix[0][f]);
        struct Fraction secndPart = multiplicationFraction(firstPart, determinantMatrix(rcFix, rc - 1, tempMatrix));
        det = additionFraction(det, secndPart);
        sign.numerator = -sign.numerator;
        // sign.denominator = -sign.denominator;
    }

    // fixFraction(&det);
    return (det);
}

void printMatrixA(uint32_t rc, struct Fraction matrix[rc][rc])
{
    for (int i = 0; i < rc; i++)
    {
        for (int j = 0; j < rc; j++)
        {
            // if (matrix[i][j].numerator != 0)
            // {
            //     printf(" %lld/%lld ", matrix[i][j].numerator, matrix[i][j].denominator);
            //     continue;
            // }
            printf(" %ld/%ld ", matrix[i][j].numerator, matrix[i][j].denominator);

            // printf(" 0/0 ");
        }
        printf("\n");
    }
}

struct Fraction multiplicationFraction(struct Fraction a, struct Fraction b)
{
    struct Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    fixFraction(&result);
    return result;
}
struct Fraction additionFraction(struct Fraction a, struct Fraction b)
{
    struct Fraction result;
    result.denominator = nsn(a.denominator, b.denominator);
    result.numerator = result.denominator / a.denominator * a.numerator + result.denominator / b.denominator * b.numerator;
    fixFraction(&result);
    return result;
}
int64_t nsd(int64_t a, int64_t b)
{
    if (a < 0)
        a = -a;
    if (b < 0)
        b = -b;
    while (a != b)
    {
        if (a < b)
            b %= a;
        else
            a %= b;
        if (a == 1 || b == 1)
            return 1;
        if (a == 0)
            return b;
        else if (b == 0)
            return a;
    }
    return a;
}

int64_t nsn(int64_t a, int64_t b)
{
    return a * b / nsd(a, b);
}

void fixFraction(struct Fraction *pFractionNumber)
{
    denominatorZero = false;

    if (pFractionNumber->numerator == 0)
        return;
    long long pomNsd = nsd(pFractionNumber->numerator, pFractionNumber->denominator);
    pFractionNumber->numerator /= pomNsd;
    pFractionNumber->denominator /= pomNsd;
    if (pFractionNumber->numerator < 0 && pFractionNumber->denominator < 0)
    {
        pFractionNumber->numerator = -pFractionNumber->numerator;
        pFractionNumber->denominator = -pFractionNumber->denominator;
    }
    if (pFractionNumber->denominator < 0)
    {
        pFractionNumber->numerator = -pFractionNumber->numerator;
        pFractionNumber->denominator = -pFractionNumber->denominator;
    }
    if (pFractionNumber->denominator == 0)
        denominatorZero = true;
}
