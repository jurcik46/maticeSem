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

struct Fraction determinantMatrix(struct Matrix *matrixStruct, struct Fraction **matrix)
{
    struct Fraction s, det, pomE;
    det.numerator = 0, det.denominator = 1;
    s.numerator = 1, s.denominator = 1;
    pomE.numerator = -1, pomE.denominator = -1;

    struct Matrix *pomMatrixStruct = initMatrixStruct(matrixStruct->rows, matrixStruct->columns);
    struct Fraction **pomMatrix = allocateMatrix(matrixStruct->rows, matrixStruct->columns);

    int i, j, m, n, c;
    if (matrixStruct->rows != matrixStruct->columns)
    {
        perror("The matrix must be square to calculate the determinant!");
        return det;
    }
    if (matrixStruct->rows == 1)
    {
        return (matrix[0][0]);
    }
    for (c = 0; c < matrixStruct->rows; c++)
    {
        m = 0;
        n = 0;
        for (i = 0; i < matrixStruct->rows; i++)
        {
            for (j = 0; j < matrixStruct->rows; j++)
            {
                pomMatrix[i][j].numerator = 0, pomMatrix[i][j].denominator = 1;
                if (i != 0 && j != c)
                {
                    pomMatrix[m][n] = matrix[i][j];
                    if (n < (matrixStruct->rows - 2))
                        n++;
                    else
                    {
                        n = 0;
                        if (matrixStruct->rows == matrixStruct->columns)
                            m++;
                    }
                }
            }
        }
        pomMatrixStruct->rows--;
        pomMatrixStruct->columns--;

        det = additionFraction(det, multiplicationFraction(s, multiplicationFraction(matrix[0][c], determinantMatrix(pomMatrixStruct, pomMatrix))));
        s = multiplicationFraction(pomE, s);
        pomMatrixStruct->rows++;
        pomMatrixStruct->columns++;
    }
    // deAllocateMatrix(matrixStruct->rows, matrixStruct->columns, pomMatrix);
    // free(pomMatrixStruct);
    fixFraction(&det);
    return (det);
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
