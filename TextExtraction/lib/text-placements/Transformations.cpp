
void copyMatrix(const double (&mtx)[6], double (&mtxResult)[6]) {
    mtxResult[0] = mtx[0];
    mtxResult[1] = mtx[1];
    mtxResult[2] = mtx[2];
    mtxResult[3] = mtx[3];
    mtxResult[4] = mtx[4];
    mtxResult[5] = mtx[5];
}

void multiplyMatrix(const double (&inMatrixA)[6], const double (&inMatrixB)[6], double (&outResult)[6]) {
    outResult[0] = inMatrixA[0]*inMatrixB[0] + inMatrixA[1]*inMatrixB[2];
    outResult[1] = inMatrixA[0]*inMatrixB[1] + inMatrixA[1]*inMatrixB[3];
    outResult[2] = inMatrixA[2]*inMatrixB[0] + inMatrixA[3]*inMatrixB[2];
    outResult[3] = inMatrixA[2]*inMatrixB[1] + inMatrixA[3]*inMatrixB[3];
    outResult[4] = inMatrixA[4]*inMatrixB[0] + inMatrixA[5]*inMatrixB[2] + inMatrixB[4];
    outResult[5] = inMatrixA[4]*inMatrixB[1] + inMatrixA[5]*inMatrixB[3] + inMatrixB[5];
}

void copyVector(const double (&vector)[2], double (&vectorResult)[2]) {
    vectorResult[0] = vector[0];
    vectorResult[1] = vector[1];
}


void transformVector(const double (&vector)[2],const double (&mtx)[6], double (&vectorResult)[2]) {
    vectorResult[0] = mtx[0]*vector[0] + mtx[2]*vector[1] + mtx[4];
    vectorResult[1] = mtx[1]*vector[0] + mtx[3]*vector[1] + mtx[5];
}


void copyBox(const double (&box)[4], double (&boxResult)[4]) {
    boxResult[0] = box[0];
    boxResult[1] = box[1];
    boxResult[2] = box[2];
    boxResult[3] = box[3];    
}

void transformBox(const double (&box)[4],const double (&mtx)[6], double (&boxResult)[4]) {
    double t[4][2];

    double a[2] = {box[0], box[1]};
    double b[2] = {box[0], box[3]};
    double c[2] = {box[2], box[3]};
    double d[2] = {box[2], box[1]};
    transformVector(a, mtx, t[0]);
    transformVector(b, mtx, t[1]);
    transformVector(c, mtx, t[2]);
    transformVector(d, mtx, t[3]);

    double minX,minY,maxX,maxY;
    
    minX = maxX = t[0][0];
    minY = maxY = t[0][1];
    
    for(int i=1;i<4;++i)
    {
        if(minX > t[i][0])
            minX = t[i][0];
        if(maxX < t[i][0])
            maxX = t[i][0];
        if(minY > t[i][1])
            minY = t[i][1];
        if(maxY < t[i][1])
            maxY = t[i][1];
    }

    double computedBox[4] = {minX, minY, maxX, maxY};
    copyBox(computedBox, boxResult);
}