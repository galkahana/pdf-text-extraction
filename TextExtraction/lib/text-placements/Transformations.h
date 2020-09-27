#pragma once

void copyMatrix(const double (&mtx)[6], double (&mtxResult)[6]);
void multiplyMatrix(const double (&mtxA)[6], const double (&mtxB)[6], double (&mtxResult)[6]);
void copyBox(const double (&box)[4], double (&boxResult)[4]);
void transformBox(const double (&box)[4],const double (&mtx)[6], double (&boxResult)[4]);
void copyVector(const double (&vector)[2], double (&vectorResult)[2]);
void transformVector(const double (&vector)[2],const double (&mtx)[6], double (&vectorResult)[2]);
