#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include <GLUT/GLUT.h>

#include "Window.h"
#include "LEDCube.h"
#include "Matrix4.h"
#include "main.h"

using namespace std;

namespace Globals
{
    LEDCube ledCube(LED_LENGTH, LED_WIDTH, LED_DEPTH);
};

int main(int argc, char *argv[])
{
    srand((int)time(0));
    
//    float specular[]  = {1.0, 1.0, 1.0, 1.0};
//    float shininess[] = {100.0};
//    float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
    
    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("LEDs Lab");    	      // open window and set window title
    
    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
//    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    
    // Generate material properties:
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
//    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
//    glEnable(GL_COLOR_MATERIAL);
    
    // Generate light source:
//    glLightfv(GL_LIGHT0, GL_POSITION, position);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
//  glutIdleFunc(Window::idleCallback);
    glutKeyboardFunc(Window::processNormalKeys);
    glutMouseFunc(Window::processPressMouse);
    glutMotionFunc(Window::processMouseMove);
    
    glutTimerFunc(1000.0/FPS, Window::onTimer, 1);
    
  glutMainLoop();
    
  return 0;
}

