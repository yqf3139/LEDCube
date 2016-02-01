//
//  LEDCube.cpp
//  FallingFlowers
//
//  Created by Jessie Gao on 1/19/16.
//  Copyright © 2016 jessie. All rights reserved.
//
#include <iostream>

#include "LEDCube.h"
#include "Window.h"

#include "Matrix4.h"
#include <GLUT/GLUT.h>

LEDCube::LEDCube(int l, int w, int d)
{
    length = l;
    width = w;
    depth = d;
    
    model2world.identity();
    
    cubeLength = LED_LEN_INTERVAL * LED_LENGTH;
    cubeWidth = LED_WID_INTERVAL * LED_WIDTH;
    cubeDepth = LED_DEP_INTERVAL * LED_DEPTH;
    
    setPointSize();
    setTestColors();
}

void LEDCube::initColors()
{
    colors = nullptr;
}

void LEDCube::setPointSize()
{
    pointSize = LED_SIZE;
}

void LEDCube::scalePointSize(double scale)
{
    pointSize *= scale;
}

void LEDCube::setColors(unsigned int *c)
{
    if (colors != nullptr && colors != c)
    {
        delete colors;
    }
    
    colors = c;
}

Matrix4& LEDCube::getMatrix()
{
    return model2world;
}

void LEDCube::spin(double deg)   // deg is in degrees
{
//    std::cerr<<"spin\n";
    Matrix4 rotateMatrix;
    rotateMatrix.makeRotateY(deg);
    model2world = rotateMatrix * model2world;
}

void LEDCube::transform(Matrix4 matrix)
{
    model2world =  matrix * model2world;
}

void LEDCube::draw()
{
    if (colors == nullptr)
    {
        return;
    }
    
    glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

    // draw a sphere after translation
    // make sure to get back to the former matrix when finish drawing
    glPushMatrix();
    
    Matrix4 glMatrix = model2world;
    glMatrix.transpose();
    glLoadMatrixd(glMatrix.getPointer());
    
    glPointSize(pointSize);
    
    glColor3d(1, 1, 1); // white frame
    
    // draw while frame
    glBegin(GL_LINE_STRIP);
    
    glVertex3d(-cubeLength/2 - 5, -cubeWidth/2 - 5, -cubeDepth/2 - 5);
    glVertex3d(-cubeLength/2 - 5, cubeWidth/2 + 5, -cubeDepth/2 - 5);
    glVertex3d(cubeLength/2 + 5, cubeWidth/2 + 5, -cubeDepth/2 - 5);
    glVertex3d(cubeLength/2 + 5, -cubeWidth/2 - 5, -cubeDepth/2 - 5);
    glVertex3d(-cubeLength/2 - 5, -cubeWidth/2 - 5, -cubeDepth/2 - 5);
    glVertex3d(-cubeLength/2 - 5, -cubeWidth/2 - 5, cubeDepth/2 + 5);
    glVertex3d(cubeLength/2 + 5, -cubeWidth/2 - 5, cubeDepth/2 + 5);
    glVertex3d(cubeLength/2 + 5, cubeWidth/2 + 5, cubeDepth/2 + 5);
    glVertex3d(-cubeLength/2 - 5, cubeWidth/2 + 5, cubeDepth/2 + 5);
    glVertex3d(-cubeLength/2 - 5, -cubeWidth/2 - 5, cubeDepth/2 + 5);
    
    glEnd();
    
    glBegin(GL_LINES);
    
    glVertex3d(-cubeLength/2 - 5, cubeWidth/2 + 5, cubeDepth/2 + 5);
    glVertex3d(-cubeLength/2 - 5, cubeWidth/2 + 5, -cubeDepth/2 - 5);
    
    glVertex3d(cubeLength/2 + 5, cubeWidth/2 + 5, cubeDepth/2 + 5);
    glVertex3d(cubeLength/2 + 5, cubeWidth/2 + 5, -cubeDepth/2 - 5);
    
    glVertex3d(cubeLength/2 + 5, -cubeWidth/2 - 5, cubeDepth/2 + 5);
    glVertex3d(cubeLength/2 + 5, -cubeWidth/2 - 5, -cubeDepth/2 - 5);
    
    glEnd();
    
    
    // draw spheres
    glBegin(GL_POINTS);
    
    unsigned int color;
    unsigned int R, G, B, W;
    
    for (int z = 0; z < LED_DEPTH; ++z)
    {
        for (int x = 0; x < LED_LENGTH; ++x)
        {
            for (int y = 0; y < LED_WIDTH; ++y)
            {
                color = colors[z * LED_WIDTH * LED_LENGTH + x * LED_WIDTH + y];
                if (color == 0)
                {
                    continue;
                }
                W = color & 0xFF;
                color >>= 8;
                B = color & 0xFF;
                color >>= 8;
                G = color & 0xFF;
                color >>= 8;
                R = color & 0xFF;
                
                glColor4d(1.0 * (R+W) / 0X100, 1.0 * (G+W) / 0x100, 1.0 * (B+W) / 0x100, LED_ALPHA);
                glVertex3d(-cubeLength/2 + LED_LEN_INTERVAL * x, -cubeWidth/2 + LED_WID_INTERVAL * y, -cubeDepth/2 + LED_DEP_INTERVAL * z);
            }
        }
    }
    
    glEnd();
    
    glPopMatrix();
}

void LEDCube::setTestColors()
{
    if (colors == nullptr)
    {
        colors = new unsigned int [length * width * depth];
    }
    
    for (int i = 0; i < length * width * depth; ++i)
    {
        colors[i] = 0xFF;
    }
}