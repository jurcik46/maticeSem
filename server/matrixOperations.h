#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
#ifdef __cplusplus
extern "C"
{
#endif

    struct Fraction **transposeMatrix(const struct Matrix *matrixStructSource, const struct Fraction **matrixSource, struct Matrix **matrixStructDestination, struct Fraction **matrixDestination);
    struct Fraction **additionMatrix(const struct Matrix *matrixStructA, const struct Fraction **matrixA, const struct Matrix *matrixStructB, const struct Fraction **matrixB);
    int64_t nsd(int64_t a, int64_t b);
    int64_t nsn(int64_t a, int64_t b);
    void fixFraction(struct Fraction *pFractionNumber);

#ifdef __cplusplus
}
#endif

#endif /* MATRIXOPERATIONS_H */
