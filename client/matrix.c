
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            printf(" %lld/%lld ", pMatrix[i][j].numerator, pMatrix[i][j].denominator);
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
            sprintf(pomBuffer, "%lld/%lld;", pMatrix[i][j].numerator, pMatrix[i][j].denominator);
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
            sscanf(ptr, "%lld/%lld", &pMatrixDestination[i][j].numerator, &pMatrixDestination[i][j].denominator);
            ptr = strtok(NULL, ";");
        }
    }
}

struct Fraction **loadMatrixFromFile(struct Matrix *pMatrixStruct, struct Fraction **pMatrix)
{
    FILE *file = fopen(MATRIX_FILE, "r");
    if (file == NULL)
    {
        perror("Filed to open matrix file.");
        return NULL;
    }
    char selectedMatrixLabel;
    while ((int)pMatrixStruct->label != (int)selectedMatrixLabel)
    {
        if (fscanf(file, "%c %lu %lu", &selectedMatrixLabel, &pMatrixStruct->rows, &pMatrixStruct->columns) == EOF)
            return false;
    }
    pMatrix = allocateMatrix(pMatrixStruct->rows, pMatrixStruct->columns);

    for (int i = 0; i < pMatrixStruct->rows; i++)
    {
        for (int j = 0; j < pMatrixStruct->columns; j++)
        {
            long numerator, denominator;
            char fractionBar;
            fscanf(file, "%lld%c%lld", &numerator, &fractionBar, &denominator);
            pMatrix[i][j].numerator = numerator;
            pMatrix[i][j].denominator = denominator;
            printf("%lld/%lld", pMatrix[i][j].numerator, pMatrix[i][j].denominator);
        }
    }
    if (fclose(file) == EOF)
    {
        perror("Filed to open matrix file.");
    }
    return pMatrix;
    // return true;
}