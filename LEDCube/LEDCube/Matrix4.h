#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector3D.h"

class Matrix4
{
  public:
    double m[4][4];   // matrix elements; first index is for rows, second for columns (row-major)
    
  public:
    Matrix4();     
    Matrix4& operator=(const Matrix4&);
    double* getPointer(); 
    void identity(); 
    void transpose();
    void makeRotateX(double);
    void makeRotateY(double);
    void makeRotateZ(double);
    void makeTranslate(double, double, double);
    void makeRotate(Vector3D, double);
    void makeScale(double, double, double);
    void display(string);
    
    Matrix4 operator*(const Matrix4&);
    Vector3D operator*(const Vector3D&);
};

#endif