// Diego Adolfo Jose Villa - A00815260
// Computer Graphics
// HW 10 - Three-Dimensional Viewing Projects
// Project 2 - Mouse: Navigate
// November 17th, 2017

// This project was based on the tutorial Mouse: Moving the Camera III
// From: http://www.lighthouse3d.com/tutorials/glut-tutorial/mouse-putting-it-all-together/

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

float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;
// -------------------------------------------

// -------------------------------------------
// Mouse Controllers
// -------------------------------------------
void mouseButton(int button, int state, int x, int y) {
    // Only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // When the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        } else {
            // state = GLUT_DOWN
            xOrigin = x;
        }
    }
}

void mouseMove(int x, int y) {
    // This will only be true when the left button is down
    if (xOrigin >= 0) {
        // Update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // Update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}
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

void pressKey(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
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
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(320,320);
    glutCreateWindow("Project 2 - Mouse: Navigate");
    
    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);
    glutSpecialFunc(processSpecialKeys);
    
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    
    // OpenGL init
    glEnable(GL_DEPTH_TEST);
    
    // enter GLUT event processing cycle
    glutMainLoop();
    
    return 1;
}
