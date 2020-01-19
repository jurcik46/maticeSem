#ifndef MATRIX_H
#define MATRIX_H
#ifdef __cplusplus
extern "C"
{
#endif

#define MATRIX_FILE "matrix.txt"

    typedef struct Fraction
    {
        int64_t numerator;
        int64_t denominator;
    } __attribute__((packed));

    struct Matrix
    {
        char label;
        uint32_t rows;
        uint32_t columns;
        uint32_t payloadLength;
        char matrixPayload[0];

    } __attribute__((packed));
    struct Fraction **allocateMatrix(int rows, int columns);
    struct Matrix *initMatrixStruct(int rows, int columns);
    void deAllocateMatrix(int rows, int columns, struct Fraction ***pMatrix);
    void printMatrix(int rows, int columns, struct Fraction **pMatrix);
    char *convertMatrixToString(int rows, int columns, struct Fraction **pMatrix);
    void convertStringToMatrix(char *matrixString, int rows, int columns, struct Fraction **pMatrixDestination);
    struct Fraction **loadMatrixFromFile(struct Matrix *pMatrixStruct, struct Fraction **pMatrix);

#ifdef __cplusplus
}
#endif

#endif /* MATRIX_H */
