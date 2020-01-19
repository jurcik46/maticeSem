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

struct Fraction **additionMatrix(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB)
{
    if (matrixStructA->rows == matrixStructB->rows && matrixStructA->columns == matrixStructB->columns)
    {
        struct Fraction **result = allocateMatrix(matrixStructA->rows, matrixStructA->columns);
        for (int i = 0; i < matrixStructA->rows; i++)
        {
            for (int j = 0; j < matrixStructA->columns; j++)
            {

                // result. = a->matica[i][j] + b->matica[i][j];
                result[i][j].denominator = nsn(matrixA[i][j].denominator, matrixB[i][j].denominator);
                result[i][j].numerator = result[i][j].denominator / matrixA[i][j].denominator * matrixA[i][j].numerator + result[i][j].denominator / matrixB[i][j].denominator * matrixB[i][j].numerator;
                fixFraction(&result[i][j]);
            }
        }
        return result;
    }
    perror("We need matrices with the same number of elements to sum the matrices.\n");
    return NULL;
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
