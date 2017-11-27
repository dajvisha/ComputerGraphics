// Diego Adolfo Jose Villa - A00815260
// Computer Graphics
// HW 10 - Three-Dimensional Viewing Projects
// Project 1 - Keyboard: Move the camera
// November 17th, 2017

// This project was based on the tutorial Keyboard Example: Moving the Camera
// From: http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/

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
// Camera setup
// -------------------------------------------
// Angle of rotation for the camera direction
float angle = 0.0f;

// Actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f, z=5.0f;
// -------------------------------------------

// -------------------------------------------
// Key Controllers
// -------------------------------------------
void processSpecialKeys(int key, int xx, int yy) {
    float fraction = 0.1f;
    
    switch (key) {
        case GLUT_KEY_LEFT :
            angle -= 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_RIGHT :
            angle += 0.01f;
            lx = sin(angle);
            lz = -cos(angle);
            break;
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
            break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
            break;
    }
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 27) {
        exit(0);
    }
}
// -------------------------------------------

// -------------------------------------------
// Environment setup
// -------------------------------------------
void drawSnowMan() {
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Draw Body
    glTranslatef(0.0f ,0.75f, 0.0f);
    glutSolidSphere(0.75f,20,20);
    
    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f,20,20);
    
    // Draw Eyes
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();
    
    // Draw Nose
    glColor3f(1.0f, 0.5f , 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}
// -------------------------------------------

// -------------------------------------------
// Render Function
// -------------------------------------------
void renderScene(void) {
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Reset transformations
    glLoadIdentity();
    
    // Set the camera
    gluLookAt(x, 1.0f, z,
              x+lx, 1.0f, z+lz,
              0.0f, 1.0f, 0.0f);
    
    // Draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f,  100.0f);
    glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();
    
    // Draw 36 SnowMen
    for(int i = -3; i < 3; i++) {
        for(int j=-3; j < 3; j++) {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);
            drawSnowMan();
            glPopMatrix();
        }
    }
    
    glutSwapBuffers();
}
// -------------------------------------------

// -------------------------------------------
// Change Size Function
// -------------------------------------------
void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    if (h == 0) {
        h = 1;
    }
    
    float ratio = w * 1.0 / h;
    
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    
    // Reset Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}
// -------------------------------------------

int main(int argc, char **argv) {
    // Init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Project 1 - Keyboard: Move the camera");
    
    // Register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    
    // Enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}
