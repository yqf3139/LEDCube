#ifndef _WINDOW_H_
#define _WINDOW_H_

#define FPS 30 // 30HZ

#define LED_LENGTH 64 // 640
#define LED_WIDTH 48   // 480
#define LED_DEPTH 64   // 640

#define LED_LEN_INTERVAL 3.0 // interval between two leds, from center to center
#define LED_WID_INTERVAL 3.0
#define LED_DEP_INTERVAL 3.0

#define LED_SIZE 1.0 // size of a single LED, diameter
#define LED_ALPHA 0.3

#define SPIN_RATE 1.0

class Window	  // OpenGL output window related routines
{
public:
    static int width, height; 	            // window size

public:
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processNormalKeys(unsigned char, int, int);
    static void processPressMouse(int, int, int, int);
    static void processMouseMove(int, int);
    static void onTimer(int);
};

#endif

