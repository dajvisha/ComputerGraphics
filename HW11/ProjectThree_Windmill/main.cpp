// Diego Adolfo Jose Villa - A00815260
// Computer Graphics
// HW 11 - Modelling Projects
// Project 3 - Windmill
// November 18th, 2017

// This project was based on the code OpenGl Cart and Windmill from
// Hobart and William Smith Colleges
// Link: http://math.hws.edu/graphicsbook/source/glut/
// Note: I did an orginal composition taken that code
// as reference

// -------------------------------------------
// Libraries
// -------------------------------------------
#include <stdlib.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
// -------------------------------------------

// -------------------------------------------
// Global variables and constants
// -------------------------------------------
int frameNumber = 0;
const double PI = 3.141592654;
// -------------------------------------------

// -------------------------------------------
// Draw Disk
// -------------------------------------------
// Explanation:
// Draw a 32-sided regular polygon as an
// approximation for a circular disk.
// (This is necessary since OpenGL has no
// commands for drawing ovals, circles,
// or curves.) The disk is centered at (0,0)
// with a radius given by the parameter.
// -------------------------------------------
void drawDisk(double radius) {
    int d;
    glBegin(GL_POLYGON);
    for (d = 0; d < 32; d++) {
        double angle = 2*PI/32 * d;
        glVertex2d( radius*cos(angle), radius*sin(angle));
    }
    glEnd();
}
// -------------------------------------------

// -------------------------------------------
// Draw Sun
// -------------------------------------------
// Explanation:
// Draw a sun with radius 0.5 centered at (0,0).
// There are also 13 rays which extend outside
// from the sun for another 0.25 units.
// -------------------------------------------
void drawSun() {
    int i;
    glColor3f(1,1,0);
    for (i = 0; i < 24; i++) {
        glRotatef( 360 / 24, 0, 0, 1 );
        glBegin(GL_LINES);
        glVertex2f(0, 0);
        glVertex2f(0.75f, 0);
        glEnd();
    }
    drawDisk(0.40);
    glColor3f(0,0,0);
}
// -------------------------------------------

void drawHill() {
    glColor3f(0.2f, 0.7f, 0.2f);
    drawDisk(3);
    glColor3f(0,0,0);
}


// -------------------------------------------
// Draw Windmill
// -------------------------------------------
// Explanation:
// Draw a windmill, consisting of a pole and
// three vanes.  The pole extends from the
// point (0,0) to (0,3).  The vanes radiate
// out from (0,3).  A rotation that depends
// on the frame number is applied to the whole
// set of vanes, which causes the windmill to
// rotate as the animation proceeds. Note that
// this method changes the current transform in
// the GL context gl!  The caller of this
// subroutine should take care to save and
// restore the original transform, if necessary.
// -------------------------------------------
void drawWindmill() {
    int i;
    glColor3f(0.8f, 0.8f, 0.9f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, 0);
    glVertex2f(0.05f, 0);
    glVertex2f(0.05f, 3);
    glVertex2f(-0.05f, 3);
    glEnd();
    glTranslatef(0, 3, 0);
    glRotated(frameNumber * (180.0/46), 0, 0, 1);
    glColor3f(0.4f, 0.4f, 0.8f);
    for (i = 0; i < 3; i++) {
        glRotated(120, 0, 0, 1);
        glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(1.5f,0);
        glVertex2f(0.5f, -0.1f);
        glEnd();
    }
}
// -------------------------------------------

// -------------------------------------------
// Draw Display
// -------------------------------------------
// Explanation:
// This function is called when the image needs
// to be redrawn. It is installed by main()
// as the GLUT display function. It draws
// the current frame of the animation.
// -------------------------------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Draw the sun
    glPushMatrix();
    glTranslated(1.0,3,0);
    glRotated(-frameNumber*0.7,0,0,1);
    drawSun();
    glPopMatrix();
    
    // Draw hills
    glColor3f(0.2f, 0.6f, 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(0,-1);
    glVertex2f(6,1.2f);
    glVertex2f(20,-1);
    glEnd();
    
    glPushMatrix();
    glTranslated(1,-2.35,0);
    drawHill();
    glPopMatrix();
    
    
    // Draw Windmill
    glPushMatrix();
    glTranslated(1.25,-0.90,0);
    glScaled(0.75,0.75,1);
    drawWindmill();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(6,1.05,0);
    glScaled(0.4,0.4,1);
    drawWindmill();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(4.0,0.15,0);
    glScaled(0.5,0.5,1);
    drawWindmill();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(6.5,0.27,0);
    glScaled(0.43,0.43,1);
    drawWindmill();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(5.2,-0.60,0);
    glScaled(0.60,0.60,1);
    drawWindmill();
    glPopMatrix();
    
    glutSwapBuffers();
}
// -------------------------------------------

// -------------------------------------------
// Do Frame
// -------------------------------------------
// Explanation:
// This function is set as the glutTimerFunc
// to drive the animation
// -------------------------------------------
void doFrame(int v) {
    frameNumber++;
    glutPostRedisplay();
    glutTimerFunc(30,doFrame,0);
}
// -------------------------------------------

// -------------------------------------------
// Init
// -------------------------------------------
// Explanation:
// This method is called from main() to
// initialize OpenGL.
// -------------------------------------------
void init() {
    glClearColor(0.4f, 0.8f, 0.95f, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 7, -1, 4, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}
// -------------------------------------------

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(700,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 3: Windmill");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(200,doFrame,0);
    
    glutMainLoop();
    return 0;
}
