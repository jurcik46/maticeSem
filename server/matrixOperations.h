#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
#ifdef __cplusplus
extern "C"
{
#endif
    struct Fraction multiplicationFraction(struct Fraction a, struct Fraction b);
    struct Fraction additionFraction(struct Fraction a, struct Fraction b);
    struct Fraction divideFraction(struct Fraction a, struct Fraction b);
    struct Fraction **transposeMatrix(const struct Matrix *matrixStructSource, const struct Fraction **matrixSource, struct Matrix **matrixStructDestination, struct Fraction **matrixDestination);
    struct Fraction **additionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result);
    struct Fraction **substractionMatrixs(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB, struct Fraction **result);
    void cofatorMatrix(int rcFix, int rc, struct Fraction **matrix, struct Fraction **tempMatrix, int p, int q);
    struct Fraction determinantMatrix(uint32_t rcFix, uint32_t rc, struct Fraction **matrix);
    void subadjoint(uint32_t rc, struct Fraction **matrixSource, struct Fraction **matrixDestination);
    struct Fraction **inverseMatrix(uint32_t rc, const struct Fraction **matrixSource, struct Fraction **matrixDestination);
    int64_t nsd(int64_t a, int64_t b);
    int64_t nsn(int64_t a, int64_t b);
    void fixFraction(struct Fraction *pFractionNumber);

#ifdef __cplusplus
}
#endif

#endif /* MATRIXOPERATIONS_H */
