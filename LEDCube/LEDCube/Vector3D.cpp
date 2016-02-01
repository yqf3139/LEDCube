//
//  Vector3.cpp
//  FallingFlowers
//
//  Created by Jessie Gao on 1/19/16.
//  Copyright © 2016 jessie. All rights reserved.
//

#include "Vector3D.h"
#include <iostream>
#include <math.h>
using namespace std;

Vector3D::Vector3D ()
{
    x = y = z = 0;
}

Vector3D::Vector3D (double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3D::normalize()
{
    double len = length();
    if (len != 0)
    {
        x = x / len;
        y = y / len;
        z = z / len;
    }
    else
    {
        x = y = z = 0;
    }
}

double Vector3D::length()
{
    return sqrt(x*x + y*y + z*z);
}

Vector3D Vector3D::cross(Vector3D u, Vector3D v)
{
    Vector3D res;
    
    res.x = u.y * v.z - u.z * v.y;
    res.y = u.z * v.x - u.x * v.z;
    res.z = u.x * v.y - u.y * v.x;
    
    return res;
}

double Vector3D::dot(Vector3D u, Vector3D v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

double Vector3D::angle(Vector3D u, Vector3D v)
{
    return acos(cosAngle(u, v));
}

double Vector3D::cosAngle(Vector3D u, Vector3D v)
{
    if (u.length() != 0 && v.length() != 0)
    {
        return dot(u, v) / u.length() / v.length();
    }
    
    return 1;
}

Vector3D Vector3D::operator -(const Vector3D &v)
{
    Vector3D newV;
    
    newV.x = x - v.x;
    newV.y = y - v.y;
    newV.z = z - v.z;
    
    return newV;
}

Vector3D Vector3D::operator +(const Vector3D &v)
{
    Vector3D newV;
    
    newV.x = x + v.x;
    newV.y = y + v.y;
    newV.z = z + v.z;
    
    return newV;
}

void Vector3D::display(string msg)
{
    cout<<msg<<endl;
    cout<<x<<", "<<y<<", "<<z<<endl;
    cout<<endl;
}
