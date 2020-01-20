
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <stdbool.h>
#include "matrix.h"

struct Fraction **allocateMatrix(int rows, int columns)
{
    struct Fraction **pomNewMatrix;
    pomNewMatrix = (struct Fraction **)malloc(rows * sizeof(struct Fraction *));
    for (int i = 0; i < rows; i++)
    {
        pomNewMatrix[i] = (struct Fraction *)calloc(columns, sizeof(struct Fraction));
    }
    return pomNewMatrix;
}

struct Matrix *initMatrixStruct(int rows, int columns)
{
    struct Matrix *pomNewMatrixStruct = malloc(sizeof(struct Matrix));
    pomNewMatrixStruct->rows = rows;
    pomNewMatrixStruct->columns = columns;
    // if (rows && columns)
    //     pomNewMatrixStruct->matrix = allocateMatrix(rows, columns);
    return pomNewMatrixStruct;
}

void deAllocateMatrix(int rows, int columns, struct Fraction ***pMatrix)
{
    for (int i = 0; i < rows; i++)
    {
        free((*pMatrix)[i]);
    }
    free((*pMatrix));
    *pMatrix = NULL;
}

void printMatrix(int rows, int columns, struct Fraction **pMatrix)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (pMatrix[i][j].numerator != 0)
            {
                printf(" %ld/%ld ", pMatrix[i][j].numerator, pMatrix[i][j].denominator);
                continue;
            }
            printf(" 0/0 ");
        }
        printf("\n");
    }
}

char *convertMatrixToString(int rows, int columns, struct Fraction **pMatrix)
{
    char *buffer = malloc(((sizeof(struct Fraction) + sizeof(char)) * rows * columns));
    char *pomBuffer = malloc((sizeof(struct Fraction)));
    strcpy(buffer, "");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sprintf(pomBuffer, "%ld/%ld;", pMatrix[i][j].numerator, pMatrix[i][j].denominator);
            strcat(buffer, pomBuffer);
        }
    }
    return buffer;
}

void convertStringToMatrix(char *matrixString, int rows, int columns, struct Fraction **pMatrixDestination)
{
    char *ptr = strtok(matrixString, ";");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            sscanf(ptr, "%ld/%ld", &pMatrixDestination[i][j].numerator, &pMatrixDestination[i][j].denominator);
            ptr = strtok(NULL, ";");
        }
    }
}