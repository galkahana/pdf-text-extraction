

void multiplyMatrix(const double (&inMatrixA)[6], const double (&inMatrixB)[6], double (&outResult)[6]) {
    outResult[0] = inMatrixA[0]*inMatrixB[0] + inMatrixA[1]*inMatrixB[2];
    outResult[1] = inMatrixA[0]*inMatrixB[1] + inMatrixA[1]*inMatrixB[3];
    outResult[2] = inMatrixA[2]*inMatrixB[0] + inMatrixA[3]*inMatrixB[2];
    outResult[3] = inMatrixA[2]*inMatrixB[1] + inMatrixA[3]*inMatrixB[3];
    outResult[4] = inMatrixA[4]*inMatrixB[0] + inMatrixA[5]*inMatrixB[2] + inMatrixB[4];
    outResult[5] = inMatrixA[4]*inMatrixB[1] + inMatrixA[5]*inMatrixB[3] + inMatrixB[5];
}