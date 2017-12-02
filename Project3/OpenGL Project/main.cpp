// Project 3 - OpenGL: Heightfield (Terrain) Generator
// Team Q:
//  David Orlando de la Fuente Garza - A00817582
//  José María Flores Escalera - A01153458
//  Diego Adolfo Jose Villa - A00815260
// Computer Graphics
// November 29th, 2017

// -------------------------------------------
// Libraries
// -------------------------------------------
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include <math.h>
#include <vector>

#include <GL/glui.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

vector<vector<float> > globalTerrain;
bool recalculateTerrain = true;
bool restoreSession = false;

/** These are the live variables passed into GLUI ***/
int   rotar = 0;
int   main_window;
int   iteraciones = 5;
int   corrII = 18;
int   corrID = 18;
int   corrSI = 23;
int   corrSD = 34;
float amplitud = 4;
float smoothness= 1.2;

// Using a char buffer as a live var is also possible, but it is dangerous
// because GLUI doesn't know how big your buffer is.
// But still, it works as long as text doesn't happen to overflow.
//char  text[200] = {"Hello World!"};

GLUI_EditText   *txtIteraciones;
GLUI_EditText   *txtII;
GLUI_EditText   *txtID;
GLUI_EditText   *txtSI;
GLUI_EditText   *txtSD;
GLUI_EditText   *txtAmp;
GLUI_EditText   *txtSmo;

// -------------------------------------------

GLfloat X = 0.0f; // Variable del coordenada X.
GLfloat Y = 0.0f; // Variable del coordenada Y.
GLfloat Z = 0.0f; // Variable del coordenada Z.
GLfloat rotX = 0.0f; // Rotar sobre el eje X (Dolly)
GLfloat rotY = 0.0f; // Rotar sobre el eje Y (Truck)
GLfloat rotZ = 0.0f; // Rotar sobre el eje z (Boom)
GLfloat rotLx = 0.0f; // Trasladar en el eje X por medio de la funcion glulookAt (Tilt)
GLfloat rotLy = 0.0f; // Trasladar en el eje Y por medio de la funcion glulookAt (Roll)
GLfloat rotLz = 0.0f; // Trasladar en el eje Z por medio de la funcion glulookAt (Pan)

GLfloat angle = 0.0f;
int refreshMills = 15;

void glDisplayLines(void);

void createObject() {
    /// IMPORTANT NOTE: Files may be generated on a folder that is not the folder of the .exe
    /// This may be caused due to links and references
    /// For simplicty, put the full path to the folder's path
    ofstream outfile;
    ofstream outfile2;
    outfile.open("object.obj");
    outfile2.open("object.inc");

    outfile2 << "#declare Mountain = mesh {" << endl;

    int k = 0;
    for(int i=0; i < globalTerrain.size() - 1; i++)
    {
        for(int j=0; j < globalTerrain.size() - 1; j++)
        {
            outfile2 << "triangle {";
            outfile2 << "<" << float(i+1) << ", " << float(j) << ", " << globalTerrain[i+1][j] << ">";
            outfile2 << "<" << float(i) << ", " << float(j+1) << ", " << globalTerrain[i][j+1] << ">";
            outfile2 << "<" << float(i) << ", " << float(j) << ", " << globalTerrain[i][j] << ">";
            outfile2 << "}" << endl;

            outfile2 << "triangle {";
            outfile2 << "<" << float(i+1) << ", " << float(j+1) << ", " << globalTerrain[i+1][j+1] << ">";
            outfile2 << "<" << float(i) << ", " << float(j+1) << ", " << globalTerrain[i][j+1] << ">";
            outfile2 << "<" << float(i+1) << ", " << float(j) << ", " << globalTerrain[i+1][j] << ">";
            outfile2 << "}" << endl;

            outfile << "v " << float(i+1) << " " << float(j) << " " << globalTerrain[i+1][j] << endl;
            outfile << "v " << float(i) << " " << float(j+1) << " " << globalTerrain[i][j+1] << endl;
            outfile << "v " << float(i) << " " << float(j) << " " << globalTerrain[i][j] << endl;

            outfile << "v " << float(i+1) << " " << float(j+1) << " " << globalTerrain[i+1][j+1] << endl;
            outfile << "v " << float(i) << " " << float(j+1) << " " << globalTerrain[i][j+1] << endl;
            outfile << "v " << float(i+1) << " " << float(j) << " " << globalTerrain[i+1][j] << endl;

            k += 6;
        }
    }

    outfile2 << "}" << endl;

    outfile << "f";
    int j = 1;
    for(int i=1; i <= k; i++) {
        if(i % 3 == 0) {
            outfile << " " << i << "//" << endl;
            if (i < k) {
                outfile << "f";
            }
        } else {
            outfile << " " << i << "//";
        }
    }

    outfile.close();
    outfile2.close();
}

// Inicializar la pantalla de OpenGL Glut
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0); // Sin color
    glShadeModel (GL_FLAT);
    glEnable (GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void midPoint(vector<vector<float> > &mapa_iteracion, int izq_x, int der_x, int abajo_y, int arriba_y, float amplitude, float smoothing, int ene)
{
    // Inicializaci�n de los puntos medios de la parte a resolver
    int midx = (izq_x + der_x) / 2;
    int midy = (abajo_y + arriba_y) / 2;
    float LO = -1.0;
    float HI  = 1.0;
    float randNumber = 0.0;

    if(mapa_iteracion[izq_x][midy] == 0)
    {
        randNumber = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
        mapa_iteracion[izq_x][midy] = (0.5) * (mapa_iteracion[izq_x][abajo_y] + mapa_iteracion[izq_x][arriba_y]) +
        (amplitude * randNumber * (pow(2, (-smoothing * ene))));
    }

    if(mapa_iteracion[der_x][midy] == 0)
    {
        randNumber = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
        mapa_iteracion[der_x][midy] = (0.5) * (mapa_iteracion[der_x][abajo_y] + mapa_iteracion[der_x][arriba_y]) +
        (amplitude * randNumber * (pow(2, (-smoothing * ene))));
    }

    if(mapa_iteracion[midx][abajo_y] == 0)
    {
        randNumber = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
        mapa_iteracion[midx][abajo_y] = (0.5) * (mapa_iteracion[izq_x][abajo_y] + mapa_iteracion[der_x][abajo_y]) +
        (amplitude * randNumber * (pow(2, (-smoothing * ene))));
    }


    if(mapa_iteracion[midx][arriba_y] == 0)
    {
        randNumber = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
        mapa_iteracion[midx][arriba_y] = (0.5) * (mapa_iteracion[izq_x][arriba_y] + mapa_iteracion[der_x][arriba_y]) +
        (amplitude * randNumber * (pow(2, (-smoothing * ene))));
    }

    if(mapa_iteracion[midx][midy] == 0)
    {
        randNumber = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI - LO)));
        mapa_iteracion[midx][midy] = (0.25) * (mapa_iteracion[izq_x][midy] +
                                               mapa_iteracion[der_x][midy] +
                                               mapa_iteracion[midx][abajo_y] +
                                               mapa_iteracion[midx][arriba_y] +
                                               (amplitude * randNumber * (pow (2, (-smoothing * ene)))));
    }
}

vector<vector<float> > midpoint_displacement(int n, float bb, float bl, float lb, float ll, float amp, float smo)
{
    int beg = 0;
    int last = pow(2, n);

    vector<vector<float> > mapa_final;

    mapa_final.resize(last + 1);

    for(int i = 0; i < mapa_final.size(); i++)
    {
        mapa_final[i].resize(last + 1);
    }

    // Llena el vector de vectores con 0
    for(int i = 0; i < mapa_final.size(); i++)
    {
        for(int j = 0; j < mapa_final.size(); j++)
        {
            mapa_final[i][j] = 0;
        }
    }

    mapa_final[beg][beg] = bb;
    mapa_final[beg][last] = bl;
    mapa_final[last][beg] = lb;
    mapa_final[last][last] = ll;

    int i = 0;
    while (i < n)
    {
        float pedazos = pow(2, i);
        float pedazos_ancho = pow(2, n) / pedazos;
        float xpedazo = 0;

        while (xpedazo < pedazos)
        {
            float ypedazo = 0;
            while (ypedazo < pedazos)
            {
                float izq_x = pedazos_ancho * xpedazo;
                float der_x = pedazos_ancho + izq_x;
                float abajo_y = pedazos_ancho * ypedazo;
                float arriba_y = pedazos_ancho + abajo_y;
                midPoint(mapa_final, izq_x, der_x, abajo_y, arriba_y, amp, smo, i);
                ypedazo = ypedazo + 1;
            }
            xpedazo = xpedazo + 1;
        }
        i = i +1;
    }
/*
    for(int i = 0; i < mapa_final.size(); i++)
    {
        for(int j = 0; j < mapa_final.size(); j++)
        {
            cout << mapa_final[i][j] << " ";
        }
        cout << endl;
    }
*/
    globalTerrain = mapa_final;

    return mapa_final;
}

void displayTerrain(vector<vector<float> > terrain)
{
    glScaled(0.25, 0.25, 0.25);
    glRotated(-90, 1.0, 0.0, 0.0);
    glTranslatef(-15.0f, -40.0f, -20.0f);
    if (rotar){
        glRotatef(angle, 0.0f, 0.0f, 1.0f);
    }

    for(int i=0; i < terrain.size() - 1; i++)
    {
        for(int j=0; j < terrain.size() - 1; j++)
        {
            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(float(95.0/255), float(108.0/255), 0.0f);
            glVertex3f(i+1, j, terrain[i+1][j]);
            glVertex3f(i, j+1, terrain[i][j+1]);
            glVertex3f(i, j, terrain[i][j]);
            glEnd();

            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(float(95.0/255), float(72.0/255), 0.0f);
            glVertex3f(i+1, j+1, terrain[i+1][j+1]);
            glVertex3f(i, j+1, terrain[i][j+1]);
            glVertex3f(i+1, j, terrain[i+1][j]);
            glEnd();
        }
    }
    angle -= 0.15f;
}

void saveSession()
{
    ofstream loadFile;

    /// IMPORTANT NOTE: Files may be generated on a folder that is not the folder of the .exe
    /// This may be caused due to links and references
    /// For simplicty, put the full path to the folder's path
    loadFile.open("PreviousSession.txt");

    loadFile << iteraciones << " " << amplitud << " " << smoothness << endl;

    for(int i = 0; i < globalTerrain.size(); i++)
    {
        for(int j = 0; j < globalTerrain[0].size(); j++)
        {
            loadFile << i << " " << j << " " << globalTerrain[i][j] << endl;
        }
    }

    loadFile.close();
}

void menuInicial()
{
    int opcion = 2;

    int localX, localY;
    float localZ;
    int localIteration;
    float localAmplitud, localSmoothness;

    cout << "Quieres cargar un archivo previo? (1 para Si, 2 para No): ";
    cin >> opcion;

    if (opcion == 1)
    {

        ifstream loadFile;

        /// IMPORTANT NOTE: Files may be generated on a folder that is not the folder of the .exe
        /// This may be caused due to links and references
        /// For simplicty, put the full path to the folder's path
        loadFile.open("PreviousSession.txt");

        // Read iterations, amplitud and smoothness of terrain and set to global variables
        loadFile >> localIteration >> localAmplitud >> localSmoothness;

        iteraciones = localIteration;
        amplitud = localAmplitud;
        smoothness = localSmoothness;
        int longitud = pow(2, iteraciones) + 1;
        // Modify global vector
        globalTerrain.resize(longitud);

        for(int i = 0; i < globalTerrain.size(); i++)
        {
            globalTerrain[i].resize(longitud);
        }

        // Read coordinates
        while(loadFile >> localX >> localY >> localZ)
        {
            globalTerrain[localX][localY] = localZ;
        }

        // Set recalculate terrain to false
        restoreSession = true;
        recalculateTerrain = false;

        displayTerrain(globalTerrain);

        // Close file
        loadFile.close();
    }
}

void preguntarValores()
{
    vector<vector<float> > terrenoAuxiliar;

    int opcion = 2;

    int numIteraciones = 0;
    int longitud = 0;

    int cantidadIniciales = 0;
    int puntoActual = 0;
    int X, Y;
    float Z;

    cout << "Quieres ingresar puntos para generar el terreno? (1 para Si, 2 para No): ";
    cin >> opcion;

    if (opcion == 1)
    {
        cout << "Ingresa el numero de iteraciones para el terreno: ";
        cin >> numIteraciones;

        // Se asigna al numero de iteraciones global
        iteraciones = numIteraciones;

        // Calcula la longitud
        longitud = pow(2, numIteraciones) + 1;

        // Genera la matriz de ese tamanio
        terrenoAuxiliar.resize(longitud);

        for(int i = 0; i < terrenoAuxiliar.size(); i++)
        {
            terrenoAuxiliar[i].resize(longitud);
        }

        // Llena el vector de vectores con 0
        for(int i = 0; i < terrenoAuxiliar.size(); i++)
        {
            for(int j = 0; j < terrenoAuxiliar.size(); j++)
            {
                terrenoAuxiliar[i][j] = 0;
            }
        }

        // Pide los punto
        cout << "Ingresa la cantidad de puntos iniciales: ";
        cin >> cantidadIniciales;
        cout << endl;

        cout << "A continuacion se pediran los valores de los puntos iniciales" << endl;
        cout << "Los valores X y Y de cada punto deben ser enteros, el valor Z puede ser flotante" << endl << endl;

        // Pide cada uno de los puntos
        for(int i = 0; i < cantidadIniciales; i++)
        {
            cout << "Punto #" << i + 1 << endl;
            cout << "Ingresa los valores X Y Z del punto: ";
            cin >> X >> Y >> Z;

            terrenoAuxiliar[X][Y] = Z;
        }

        // Asigna el terreno auxiliar al global
        globalTerrain = terrenoAuxiliar;

        recalculateTerrain = false;

        cout << "Se ha generado el terreno con los valores dados" << endl;
    }
    else
    {
        cout << "Se ha generado el terreno con valores default" << endl;
    }
}

// Dibujar las lineas que formaran la escena 3D.
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(rotX,1.0,0.0,0.0);
    glRotatef(rotY,0.0,1.0,0.0);
    glRotatef(rotZ,0.0,0.0,1.0);
    glTranslatef(X, Y, Z);

    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0); // Verde para el eje X
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glColor3f(1.0,0.0,0.0); // Rojo para el eje Z
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glColor3f(0.0,0.0,1.0); // Azul para el eje Y
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glEnd();

    // Lineas punteadas para conocer los lados del mapa de ejes
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);     // Patron de lineas punteadas
    glBegin(GL_LINES);
    glColor3f (0.0, 1.0, 0.0);     // Verde para el eje X
    glVertex3f(-10,0,0);
    glVertex3f(0,0,0);
    glColor3f(1.0,0.0,0.0);     // Rojo para el eje Z
    glVertex3f(0,0,0);
    glVertex3f(0,-10,0);
    glColor3f(0.0,0.0,1.0);     // Azul para el eje Y
    glVertex3f(0,0,0);
    glVertex3f(0,0,-10);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    if(recalculateTerrain)
    {
        vector<vector<float> > terrain = midpoint_displacement(iteraciones, corrII, corrID, corrSI, corrSD, amplitud, smoothness);
        displayTerrain(terrain);

        recalculateTerrain = false;
    }
    else
    {
        displayTerrain(globalTerrain);
    }
    glPopMatrix();
    glutSwapBuffers();

}

// Funcion que es llamada cuando el tamano de la pantalla cambia
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(75, (GLfloat) w /(GLfloat) h , 0.10, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Funcion que asigna acciones de acuerdo a la tecla oprimida,
// haciendo asi las traslaciones y movimientos especificados
// en las isntrucciones
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'x': // Rota la pantalla en el eje x //Truck
            rotX -= 0.5f;
            break;
        case 'X': // Sentido contrario
            rotX += 0.5f;
            break;
        case 'y': // Rota la pantalla en el eje y //Dolly
            rotY -= 0.5f;
            break;
        case 'Y': // Sentido contrario
            rotY += 0.5f;
            break;
        case 'z': // Rota la pantalla en el eje z  //Boom
            rotZ -= 0.5f;
            break;
        case 'Z': // Sentido contrario
            rotZ += 0.5f;
            break;
            // Funciones de navegacion para la rotacion  en ejes X, Y y Z
        case 'j': // Rota la pantalla en el eje x manteniendo la vista al origen en sentido contrario
            rotLx -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'J': // Rota la pantalla en el eje x manteniendo la vista al origen
            rotLx += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'k': // Rota la pantalla en el eje y manteniendo la vista al origen en sentido contrario
            rotLy -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'K': // Rota la pantalla en el eje y manteniendo la vista al origen
            rotLy += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'l': // Rota la pantalla en el eje z manteniendo la vista al origen en sentido contrario
            if(rotLz + 14 >= 0)
                rotLz -= 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'L': // Rota la pantalla en el eje z manteniendo la vista al origen
            rotLz += 0.2f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, rotLy, 15.0 + rotLz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'o': // Regresa la vista al punto de partida
        case 'O':
            X = Y = 0.0f;
            Z = 0.0f;
            rotX = 0.0f;
            rotY = 0.0f;
            rotZ = 0.0f;
            rotLx = 0.0f;
            rotLy = 0.0f;
            rotLz = 0.0f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(rotLx, rotLy, 15.0f + rotLz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
            break;
    }
    glutPostRedisplay(); // Redibuja la escena
}

// Funcion que se llama cuando se ha oprimido una tecla especial
void specialKey(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_LEFT : // Rotar en el eje X
            X -= 0.1f;
            break;
        case GLUT_KEY_RIGHT : // Rotar en el eje X (opuesto)
            X += 0.1f;
            break;
        case GLUT_KEY_UP : // Rotar en el eje Y
            Y += 0.1f;
            break;
        case GLUT_KEY_DOWN : // Rotar en el eje Y (opuesto)
            Y -= 0.1f;
            break;
        case GLUT_KEY_PAGE_UP: // Rotar en el eje Z
            Z -= 0.1f;
            break;
        case GLUT_KEY_PAGE_DOWN: // Rotar en el eje Z (opuesto)
            Z += 0.1f;
            break;
    }
    glutPostRedisplay(); // Redibuja la escena
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMills, timer, 0);
}


void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  glutPostRedisplay();
}


void control_cb( int control )
{
  if (control == 1) {
      specialKey(GLUT_KEY_LEFT, 0, 0);
  } else if (control == 2){
      specialKey(GLUT_KEY_RIGHT, 0, 0);
  } else if (control == 3){
      specialKey(GLUT_KEY_DOWN, 0, 0);
  } else if (control == 4){
      specialKey(GLUT_KEY_UP, 0, 0);
  } else if (control == 5){
      specialKey(GLUT_KEY_PAGE_DOWN, 0, 0);
  } else if (control == 6){
      specialKey(GLUT_KEY_PAGE_UP, 0, 0);
  } else if (control == 7){
      corrII = atoi(txtII->get_text());
      recalculateTerrain = true;
  } else if (control == 8){
      corrID = atoi(txtID->get_text());
      recalculateTerrain = true;
  } else if (control == 9){
      corrSI = atoi(txtSI->get_text());
      recalculateTerrain = true;
  } else if (control == 10){
      corrSD = atoi(txtSD->get_text());
      recalculateTerrain = true;
  } else if (control == 11){
      amplitud = atof(txtAmp->get_text());
      recalculateTerrain = true;
  } else if (control == 12){
      smoothness = atof(txtSmo->get_text());
      recalculateTerrain = true;
  } else if (control == 13){
      glutReshapeWindow(640,480);
  } else if (control == 14){
      glutReshapeWindow(800,600);
  } else if (control == 15){
      glutReshapeWindow(1024,768);
  } else if (control == 16){
      iteraciones = atof(txtIteraciones->get_text());
      recalculateTerrain = true;
  } else if (control == 17){
      createObject();
  } else if (control == 18){
      createObject();
  } else if (control == 19){
      keyboard ('j', 0, 0);
  } else if (control == 20){
      keyboard ('k', 0, 0);
  } else if (control == 21){
      keyboard ('l', 0, 0);
  } else if (control == 22){
      keyboard ('o', 0, 0);
  } else if (control == 23){
      saveSession();
  }
}

// Funcion principal del programa, haciendo las llamadas a funciones necesarias
// y las callbacks que se ocupan
int main(int argc, char** argv)
{
    menuInicial();

    // We only need to ask for initial values if the user didn't restore the session
    if(!restoreSession)
    {
        preguntarValores();
    }

    srand (static_cast <unsigned> (time(0)));
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (640,480);
    main_window = glutCreateWindow("Blender Project");
    init ();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutTimerFunc(0, timer, 0);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/
  GLUI *glui = GLUI_Master.create_glui( "Controller", 0, 400, 200); /* name, flags,
								 x, and y */

  GLUI_Panel *obj_panelterreno = new GLUI_Panel( glui, "Terrain" );

  new GLUI_StaticText( obj_panelterreno, "Coordinates, Amplitude and Smoothing" );
  new GLUI_Separator( obj_panelterreno );
  txtIteraciones = new GLUI_EditText( obj_panelterreno, "Iterations:", &iteraciones, 16, control_cb );
  txtII = new GLUI_EditText( obj_panelterreno, "Lower Left:", &corrII, 7, control_cb );
  txtID = new GLUI_EditText( obj_panelterreno, "Lower Right:", &corrID, 8, control_cb );
  txtSI = new GLUI_EditText( obj_panelterreno, "Upper Left:", &corrSI, 9, control_cb );
  txtSD = new GLUI_EditText( obj_panelterreno, "Upper Right:", &corrSD, 10, control_cb );
  txtAmp = new GLUI_EditText( obj_panelterreno, "Amplitude:", &amplitud, 11, control_cb );
  txtSmo = new GLUI_EditText( obj_panelterreno, "Smoothing:", &smoothness, 12, control_cb );

  //new GLUI_Checkbox(obj_panelterreno, "Rotate Terrain", &rotar );


  GLUI_Panel *obj_panelcamara = new GLUI_Panel( glui, "Camera" );
  new GLUI_Button( obj_panelcamara, "Dolly Left", 1, control_cb);
  new GLUI_Button( obj_panelcamara, "Dolly Right", 2, control_cb);
  //new GLUI_Button( obj_panelcamara, "Tilt", 19, control_cb);
  new GLUI_Button( obj_panelcamara, "Boom Up", 3, control_cb);
  new GLUI_Button( obj_panelcamara, "Boom Down", 4, control_cb);
  //new GLUI_Button( obj_panelcamara, "Pan", 20, control_cb);
  new GLUI_Button( obj_panelcamara, "Truck In", 5, control_cb);
  new GLUI_Button( obj_panelcamara, "Truck Out", 6, control_cb);
  //new GLUI_Button( obj_panelcamara, "Roll", 21, control_cb);
  new GLUI_Button( glui, "Restart Camera", 22, control_cb);


  GLUI_Panel *obj_panelresolucion = new GLUI_Panel( glui, "Resolution" );
  new GLUI_Button( obj_panelresolucion, "640 x 480", 13, control_cb);
  new GLUI_Button( obj_panelresolucion, "800 x 600", 14, control_cb);
  new GLUI_Button( obj_panelresolucion, "1024 x 768", 15, control_cb);

  new GLUI_Button( glui, "Save Session", 23, control_cb);
  new GLUI_Button( glui, "Export to OBJ", 17, control_cb);
  new GLUI_Button( glui, "Export to INC", 18, control_cb);

  new GLUI_Button( glui, "Exit", 0,(GLUI_Update_CB)exit );


  glui->set_main_gfx_window( main_window );

  /* We register the idle callback with GLUI, *not* with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle );

  glutMainLoop();


    return 0;
}

