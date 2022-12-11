#pragma once

void UnitMatrix(double (&mtxResult)[6]);
void CopyMatrix(const double (&mtx)[6], double (&mtxResult)[6]);
void MultiplyMatrix(const double (&mtxA)[6], const double (&mtxB)[6], double (&mtxResult)[6]);
void CopyBox(const double (&box)[4], double (&boxResult)[4]);
void TransformBox(const double (&box)[4],const double (&mtx)[6], double (&boxResult)[4]);
void CopyVector(const double (&vector)[2], double (&vectorResult)[2]);
void TransformVector(const double (&vector)[2],const double (&mtx)[6], double (&vectorResult)[2]);
