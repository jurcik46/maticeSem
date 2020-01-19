#ifndef MATRIXOPERATIONS_H
#define MATRIXOPERATIONS_H
#ifdef __cplusplus
extern "C"
{
#endif

    struct Fraction **transposeMatrix(const struct Matrix *matrixStructSource, const struct Fraction **matrixSource, struct Matrix **matrixStructDestination, struct Fraction **matrixDestination);

#ifdef __cplusplus
}
#endif

#endif /* MATRIXOPERATIONS_H */
