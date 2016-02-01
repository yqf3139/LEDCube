#include <math.h>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Matrix4.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4& Matrix4::operator=(const Matrix4& m2)
{
  if (this != &m2)
  {
    for (int i=0; i<4; ++i)
    {
      for (int j=0; j<4; ++j)
      {
        m[i][j] = m2.m[i][j];
      }
    }
  }
  return *this;
}

// return pointer to matrix elements
double* Matrix4::getPointer()
{
  return &m[0][0];
}

// set matrix to identity matrix
void Matrix4::identity()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      if (i==j) 
        m[i][j] = 1.0; 
      else 
        m[i][j] = 0.0;
    }
  }
}

// transpose the matrix (mirror at diagonal)
void Matrix4::transpose()
{
  Matrix4 temp;
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      temp.m[j][i] = m[i][j];
    }
  }
  *this = temp;  // copy temporary values to this matrix
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateX(double angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    identity();
    m[1][1] = cos(angle);
    m[1][2] = -sin(angle);
    m[2][1] = sin(angle);
    m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateY(double angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    identity();
    m[0][0] = cos(angle);
    m[0][2] = sin(angle);
    m[2][0] = -sin(angle);
    m[2][2] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeRotateZ(double angle)
{
    angle = angle / 180.0 * M_PI;  // convert from degrees to radians
    identity();
    m[0][0] = cos(angle);
    m[0][1] = -sin(angle);
    m[1][0] = sin(angle);
    m[1][1] = cos(angle);
}

// Creates a rotation matrix which rotates about the y axis.
// angle is expected in degrees
void Matrix4::makeTranslate(double x, double y, double z)
{
    identity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
}

Matrix4 Matrix4::operator*(const Matrix4 &m2)
{
    Matrix4 newM;
    
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            for (int k = 0; k < 4; ++k)
            {
                newM.m[i][j] += m[i][k] * m2.m[k][j];
            }
        }
    }
//    newM.display();
    
    return newM;
}
Vector3D Matrix4::operator*(const Vector3D &v2)
{
    Vector3D newV;
    
    newV.x = m[0][0] * v2.x + m[0][1] * v2.y + m[0][2] * v2.z;
    newV.y = m[1][0] * v2.x + m[1][1] * v2.y + m[1][2] * v2.z;
    newV.z = m[2][0] * v2.x + m[2][1] * v2.y + m[2][2] * v2.z;
    
    return newV;
}

void Matrix4::makeScale(double sx, double sy, double sz)
{
    identity();
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    
//    cout<<sx<<' '<<sy<<' '<<sz<<endl;
//    display();
}

void Matrix4::makeRotate(Vector3D axis, double cosA)
{
    identity();
    
    Vector3D unitVector = axis;
    unitVector.normalize();
    
    if (unitVector.x == 0 && unitVector.y == 0 && unitVector.z == 0)
    {
        return;
    }
    
    double sinA = sqrt(1 - cosA*cosA);
    
    m[0][0] = 1 + (1 - cosA) * (unitVector.x * unitVector.x - 1);
    m[0][1] = -unitVector.z * sinA + (1 - cosA) * unitVector.x * unitVector.y;
    m[0][2] = unitVector.y * sinA + (1 - cosA) * unitVector.x * unitVector.z;
    m[1][0] = unitVector.z * sinA + (1 - cosA) * unitVector.y * unitVector.x;
    m[1][1] = 1 + (1 - cosA) * (unitVector.y * unitVector.y - 1);
    m[1][2] = -unitVector.x * sinA + (1 - cosA) * unitVector.y * unitVector.z;
    m[2][0] = -unitVector.y * sinA + (1 - cosA) * unitVector.z * unitVector.x;
    m[2][1] = unitVector.x * sinA + (1 - cosA) * unitVector.z * unitVector.y;
    m[2][2] = 1 + (1 - cosA) * (unitVector.z * unitVector.z - 1);
    
//    display("makeRotate:");
//    unitVector.display("axis");
//    cout<<"cosA"<<cosA<<endl<<"xxxxxx"<<endl;
}

void Matrix4::display(string msg)
{
    cout<<msg<<endl;
    
    cout.setf(ios::fixed);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout<<setprecision(2)<<setw(7)<<m[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}