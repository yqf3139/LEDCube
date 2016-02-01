#include <iostream>

#include <GLUT/GLUT.h>
#include <math.h>

#include "Window.h"
#include "LEDCube.h"
#include "Matrix4.h"
#include "main.h"
#include "Vector3D.h"

using namespace std;

int Window::width  = 1440;   // set window width in pixels here
int Window::height = 900;   // set window height in pixels here

bool spinToggle = false;
int mouseButton = 0;

Vector3D mouse_start;

Vector3D trackBallMapping(int x, int y);

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback()
{
    if (spinToggle)
    {
        Globals::ledCube.spin(SPIN_RATE);
    }
    
    displayCallback();         // call display routine to show the cube
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
  cerr << "Window::reshapeCallback called" << endl;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -500);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers

  Globals::ledCube.draw();
  
  glFlush();  
  glutSwapBuffers();
}

void Window::processNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
        case ' ':
            spinToggle = !spinToggle;
            break;
            
        case 's':
        {
            double scale = .9;
            Matrix4 scaleMatrix;
            scaleMatrix.makeScale(scale, scale, scale);
            Globals::ledCube.transform(scaleMatrix);
            Globals::ledCube.scalePointSize(scale);
            break;
        }
        
        case 'S':
        {
            double scale = 1.1;
            Matrix4 scaleMatrix;
            scaleMatrix.makeScale(scale, scale, scale);
            Globals::ledCube.transform(scaleMatrix);
            Globals::ledCube.scalePointSize(scale);
            break;
        }
            
        case 'L':
        {
            glEnable(GL_DEPTH_TEST);
            break;
        }
            
        case 'l':
        {
            glDisable(GL_DEPTH_TEST);
            break;
        }
            
        default:
            break;
    }
}

void Window::processPressMouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            switch (state) {
                case GLUT_UP:
                    mouseButton = 0xffff;
                    break;
                    
                case GLUT_DOWN:
                    mouseButton = GLUT_LEFT_BUTTON;
                    mouse_start = trackBallMapping(x, y);
                    break;
                    
                default:
                    break;
            }
            
        default:
            break;
    }
}

void Window::processMouseMove(int x, int y)
{
    switch (mouseButton) {
        case GLUT_LEFT_BUTTON:
        {
            Vector3D mouse_current = trackBallMapping(x, y);
            Vector3D axis = Vector3D::cross(mouse_start, mouse_current);
            double cosA = Vector3D::cosAngle(mouse_start, mouse_current);
            mouse_start = mouse_current;
            
            // rotate around axis by angle degree
            Matrix4 rotateMatrix;
            rotateMatrix.makeRotate(axis, cosA);
            Globals::ledCube.transform(rotateMatrix);
            break;
        }
            
        default:
            break;
    }
}

void Window::onTimer(int value)
{
    if (spinToggle)
    {
        Globals::ledCube.spin(SPIN_RATE);
    }
    glutPostRedisplay();
    glutTimerFunc(1000.0/FPS, onTimer, 1);
}

/*
 Private Methods:
 */
Vector3D trackBallMapping(int x, int y)    // The CPoint class is a specific Windows class. Either use separate x and y values for the mouse location, or use a Vector3 in which you ignore the z coordinate.
{
    Vector3D v;    // Vector v is the synthesized 3D position of the mouse location on the trackball
    double d;     // this is the depth of the mouse location: the delta between the plane through the center of the trackball and the z position of the mouse
    v.x = (2.0*x - Window::width) / Window::height;   // this calculates the mouse X position in trackball coordinates, which range from -1 to +1
    v.y = (Window::height - 2.0*y) / Window::height;   // this does the equivalent to the above for the mouse Y position
    v.z = 0.0;   // initially the mouse z position is set to zero, but this will change below
    d = v.length();    // this is the distance from the trackball's origin to the mouse location, without considering depth (=in the plane of the trackball's origin)
    d = (d<1.0) ? d : 1.0;   // this limits d to values of 1.0 or less to avoid square roots of negative values in the following line
    v.z = sqrtf(1.001 - d*d);  // this calculates the Z coordinate of the mouse position on the trackball, based on Pythagoras: v.z*v.z + d*d = 1*1
    v.normalize(); // Still need to normalize, since we only capped d, not v.
    return v;  // return the mouse location on the surface of the trackball
}