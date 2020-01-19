#include <stdint.h>

#include "matrix.h"
#include "matrixOperations.h"

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
