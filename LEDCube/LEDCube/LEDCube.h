//
//  LEDCube.h
//  FallingFlowers
//
//  Created by Jessie Gao on 1/19/16.
//  Copyright © 2016 jessie. All rights reserved.
//

#ifndef LEDCube_h
#define LEDCube_h

#include "Matrix4.h"
#include "Window.h"

class LEDCube
{
protected:
    Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
    double cubeLength, cubeWidth, cubeDepth;
    unsigned int *colors;
    double pointSize;
    int length, width, depth;
    
public:
    LEDCube(int, int, int);   // Constructor
    Matrix4& getMatrix();
    void draw();
    void spin(double);
    void transform(Matrix4);
    void scalePointSize(double);
    void initColors();
    void setColors(unsigned int *);
    
private:
    void setTestColors();
    void setPointSize();
};

#endif /* LEDCube_h */
