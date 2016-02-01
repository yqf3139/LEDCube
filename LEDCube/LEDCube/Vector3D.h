//
//  Vector3.h
//  FallingFlowers
//
//  Created by Jessie Gao on 1/19/16.
//  Copyright © 2016 jessie. All rights reserved.
//

#ifndef Vector3D_h
#define Vector3D_h

#include <iostream>
using namespace std;

class Vector3D
{
public:
    double x, y, z;
    
public:
    Vector3D();
    Vector3D(double, double, double);
    void normalize();
    double length();
    void display(string);
    
    static Vector3D cross(Vector3D, Vector3D);
    static double dot(Vector3D, Vector3D);
    static double angle(Vector3D, Vector3D);
    static double cosAngle(Vector3D, Vector3D);
    Vector3D operator -(const Vector3D &);
    Vector3D operator +(const Vector3D &);
};

#endif /* Vector3_h */
