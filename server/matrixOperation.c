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
            }
        }
        return result;
    }
    fprintf(stderr, "We need matrices with the same number of elements to sum the matrices.\n");
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
    fprintf(stderr, "We need matrices with the same number of elements to substraction the matrices.\n");
    return NULL;
}

void cofatorMatrix(int rcFix, int rc, struct Fraction **matrix, struct Fraction **tempMatrix, int p, int q)
{
    int i = 0, j = 0;

    for (int row = 0; row < rc; row++)
    {
        for (int col = 0; col < rc; col++)
        {
            if (row != p && col != q)
            {
                tempMatrix[i][j++] = matrix[row][col];
                if (j == rc - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

struct Fraction determinantMatrix(uint32_t rcFix, uint32_t rc, struct Fraction **matrix)
{
    if (rc == 1)
    {
        return (matrix[0][0]);
    }
    struct Fraction sign, det;
    det.numerator = 0, det.denominator = 1;
    sign.numerator = 1, sign.denominator = 1;
    struct Fraction **tempMatrix = allocateMatrix(rcFix, rcFix);
    // if (matrixStruct->rows != matrixStruct->columns)
    // { // TODO check this in main
    //     perror("The matrix must be square to calculate the determinant!");
    //     return det;
    // }
    for (int f = 0; f < rc; f++)
    {
        cofatorMatrix(rcFix, rc, matrix, tempMatrix, 0, f);
        det = additionFraction(det, multiplicationFraction(multiplicationFraction(sign, matrix[0][f]), determinantMatrix(rcFix, rc - 1, tempMatrix)));
        sign.numerator = -sign.numerator;
    }
    return (det);
}
void adjoint(uint32_t rc, struct Fraction **matrixSource, struct Fraction **matrixDestination)
{
    if (rc == 1)
    {
        matrixDestination[0][0].numerator = 1;
        matrixDestination[0][0].denominator = 1;
        return;
    }

    struct Fraction sign;
    sign.numerator = 1, sign.denominator = 1;
    struct Fraction **tempMatrix = allocateMatrix(rc, rc);
    // temp is used to store cofactors of A[][]

    for (int i = 0; i < rc; i++)
    {
        for (int j = 0; j < rc; j++)
        {
            // Get cofactor of A[i][j]
            cofatorMatrix(rc, rc, matrixSource, tempMatrix, i, j);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign.numerator = ((i + j) % 2 == 0) ? 1 : -1;

            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            matrixDestination[j][i] = multiplicationFraction(sign, determinantMatrix(rc, rc - 1, tempMatrix));
        }
    }
}

struct Fraction **inverseMatrix(uint32_t rc, const struct Fraction **matrixSource, struct Fraction **matrixDestination)
{
    // { // TODO check this in main
    //     perror("The matrix must be square to calculate the determinant!");
    struct Fraction determinantSourceMatrix = determinantMatrix(rc, rc, matrixSource);
    if (determinantSourceMatrix.numerator == 0)
    {
        fprintf(stderr, " Singular matrix, can't find its inverse!  \n");
        return NULL;
    }

    matrixDestination = allocateMatrix(rc, rc);
    // Find adjoint
    struct Fraction **adj = allocateMatrix(rc, rc);
    adjoint(rc, matrixSource, adj);
    // printMatrix(rc, rc, adj);
    // printf("\n");

    for (int i = 0; i < rc; i++)
        for (int j = 0; j < rc; j++)
            matrixDestination[i][j] = divideFraction(adj[i][j], determinantSourceMatrix);
    printMatrix(rc, rc, adj);

    return matrixDestination;
}

struct Fraction multiplicationFraction(struct Fraction a, struct Fraction b)
{
    struct Fraction result;
    result.numerator = a.numerator * b.numerator;
    result.denominator = a.denominator * b.denominator;
    fixFraction(&result);
    return result;
}

struct Fraction divideFraction(struct Fraction a, struct Fraction b)
{
    struct Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
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
