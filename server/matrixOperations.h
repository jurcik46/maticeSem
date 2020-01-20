#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
#ifdef __cplusplus
extern "C"
{
#endif
    struct Fraction multiplicationFraction(struct Fraction a, struct Fraction b);
    struct Fraction additionFraction(struct Fraction a, struct Fraction b);
    struct Fraction **transposeMatrix(const struct Matrix *matrixStructSource, const struct Fraction **matrixSource, struct Matrix **matrixStructDestination, struct Fraction **matrixDestination);
    struct Fraction **additionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result);
    struct Fraction **substractionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result);
    void cofatorMatrix(int rc, struct Fraction matrix[rc][rc], struct Fraction tempMatrix[rc][rc], int p, int q);
    struct Fraction determinantMatrix(uint32_t rc, struct Fraction matrix[rc][rc]);
    void printMatrixA(uint32_t rc, struct Fraction matrix[rc][rc]);
    int64_t nsd(int64_t a, int64_t b);
    int64_t nsn(int64_t a, int64_t b);
    void fixFraction(struct Fraction *pFractionNumber);

#ifdef __cplusplus
}
#endif

#endif /* MATRIXOPERATIONS_H */
