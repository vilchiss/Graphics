/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @Autor: Oropeza Vilchis Luis Alberto <vilchissfi@gmail.com>
 * Representación del cubo rubik en OpenGL con freeGlut
 * Se utilizan las flechas del teclado para rotarlo y las teclas a, s, d y w
 * para trasladarlo
 *
 */

#include <GL/glut.h>
#include <stdio.h>
#include <sys/time.h>

// Para el tamaño de cada lado
#define UNIDAD_CUBO 0.46

// Variables para crear los fps
int angulo = 0;
unsigned long dwFrames = 0;
unsigned long dwCurrentTime = 0;
unsigned long dwLastUpdateTime = 0;
unsigned long dwElapsedTime = 0;

// Posición inicial en el eje ortogonal a la pantalla
float POSICION_INICIAL_Z = -10.0f;

// Para mover el cubo
float moverEjeX = 0.0;
float moverEjeY = 0.0;

// Para rotar el cubo
float rotarEjeX = 0.0;
float rotarEjeY = 0.0;

class Cubo {
    float COLORES[7][3] = {
        {1.0, 0.0, 0.0}, // 0 rojo
        {0.0, 1.0, 0.0}, // 1 verde
        {1.0, 1.0 ,0.0}, // 2 amarillo
        {0.0, 0.0, 1.0}, // 3 azul
        {1.0, .55, 0.0}, // 4 naranja
        {1.0, 1.0, 1.0}, // 5 blanco
        {0.0, 0.0, 0.0}  // 6 negro
    };
    GLfloat vertice [8][3] = {
		{ UNIDAD_CUBO, -UNIDAD_CUBO,  UNIDAD_CUBO},
		{-UNIDAD_CUBO, -UNIDAD_CUBO,  UNIDAD_CUBO},
		{-UNIDAD_CUBO, -UNIDAD_CUBO, -UNIDAD_CUBO},
		{ UNIDAD_CUBO, -UNIDAD_CUBO, -UNIDAD_CUBO},
		{ UNIDAD_CUBO,  UNIDAD_CUBO,  UNIDAD_CUBO},
		{ UNIDAD_CUBO,  UNIDAD_CUBO, -UNIDAD_CUBO},
		{-UNIDAD_CUBO,  UNIDAD_CUBO, -UNIDAD_CUBO},
		{-UNIDAD_CUBO,  UNIDAD_CUBO,  UNIDAD_CUBO},
	};
    float colores[6][3];

    public:
        short posicion_actual; // "casilla" que ocupa en el rubik
        int angulo_rotacion;
        int flag_animacion;
        float coordenadas_iniciales[3];

        Cubo() {}
        Cubo(short colores[6], float coordenadas[3], int posicion);
        void dibujar();
        void rotar(int angulo, float eje[3]);
        void setColor(short colores[6]);
        void setCoordenadasInicial(float coordenadas[3]);
        void setPosicion(int p);
        int getPosicion();
};

Cubo::Cubo(short colores[6], float coordenadas[3], int posicion) {
    setPosicion(posicion);
    setColor(colores);
    setCoordenadasInicial(coordenadas);
}

int Cubo::getPosicion() {
    return posicion_actual;
}

void Cubo::setPosicion(int p) {
    posicion_actual = p;
}

void Cubo::setColor(short c[6]) {
    int i = 0, j = 0;
    
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++)
            colores[i][j] = COLORES[c[i]][j];
    }
}
void Cubo::setCoordenadasInicial(float coordenadas[3]) {
    int i = 0;

    for (i = 0; i < 3; i++)
        coordenadas_iniciales[i] = coordenadas[i];
}

void Cubo::rotar(int angulo, float eje[3]) {
    glPushMatrix();
    glRotatef(angulo, eje[0], eje[1], eje[2]);
    dibujar();
    glPopMatrix();
}

void Cubo::dibujar() {
    glPushMatrix();
    glTranslatef(coordenadas_iniciales[0],coordenadas_iniciales[1], coordenadas_iniciales[2]);
	glBegin(GL_POLYGON); // Frontal
    glColor3fv(colores[0]);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();
	glBegin(GL_POLYGON); // Trasera
    glColor3fv(colores[1]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();
	glBegin(GL_POLYGON);  // Izquierda
    glColor3fv(colores[2]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();
    glBegin(GL_POLYGON); // Derecha
        glColor3fv(colores[3]);
        glVertex3fv(vertice[0]);
        glVertex3fv(vertice[3]);
        glVertex3fv(vertice[5]);
        glVertex3fv(vertice[4]);
    glEnd();
	glBegin(GL_POLYGON);  // Arriba
    glColor3fv(colores[4]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
    glBegin(GL_POLYGON); // Abajo
        glColor3fv(colores[5]);
        glVertex3fv(vertice[0]);
        glVertex3fv(vertice[1]);
        glVertex3fv(vertice[2]);
        glVertex3fv(vertice[3]);
    glEnd();
    glPopMatrix();
}

class Rubik {
    short MAPA_COLORES_RUBIK[27][6] = {
        {0, 6, 4, 6, 3, 6},
        {0, 6, 6, 6, 3, 6},
        {0, 6, 6, 5, 3, 6},
        {0, 6, 4, 6, 6, 6},
        {0, 6, 6, 6, 6, 6},
        {0, 6, 6, 5, 6, 6},
        {0, 6, 4, 6, 6, 2},
        {0, 6, 6, 6, 6, 2},
        {0, 6, 6, 5, 6, 2},
        {6, 6, 4, 6, 3, 6},
        {6, 6, 6, 6, 3, 6},
        {6, 6, 6, 5, 3, 6},
        {6, 6, 4, 6, 6, 6},
        {6, 6, 6, 6, 6, 6},
        {6, 6, 6, 5, 6, 6},
        {6, 6, 4, 6, 6, 2},
        {6, 6, 6, 6, 6, 2},
        {6, 6, 6, 5, 6, 2},
        {6, 1, 4, 6, 3, 6},
        {6, 1, 6, 6, 3, 6},
        {6, 1, 6, 5, 3, 6},
        {6, 1, 4, 6, 6, 6},
        {6, 1, 6, 6, 6, 6},
        {6, 1, 6, 5, 6, 6},
        {6, 1, 4, 6, 6, 2},
        {6, 1, 6, 6, 6, 2},
        {6, 1, 6, 5, 6, 2}
    };

    float MAPA_POSICIONES_RUBIK[27][3] = {
        {-1,  1,  1},
        { 0,  1,  1},
        { 1,  1,  1},
        {-1,  0,  1},
        { 0,  0,  1},
        { 1,  0,  1},
        {-1, -1,  1},
        { 0, -1,  1},
        { 1, -1,  1},
        {-1,  1,  0},
        { 0,  1,  0},
        { 1,  1,  0},
        {-1,  0,  0},
        { 0,  0,  0},
        { 1,  0,  0},
        {-1, -1,  0},
        { 0, -1,  0},
        { 1, -1,  0},
        {-1,  1, -1},
        { 0,  1, -1},
        { 1,  1, -1},
        {-1,  0, -1},
        { 0,  0, -1},
        { 1,  0, -1},
        {-1, -1, -1},
        { 0, -1, -1},
        { 1, -1, -1}
    };
    static const int TAMANO = 3;
    static const int PIEZAS = 27;
    Cubo cubos[PIEZAS];
    int MAPA_ROTACIONES[9][9] = {
        // Se toma izquierda en el origen
        {0,1,2,3,4,5,6,7,8},          // Z derecha
        {9,10,11,12,13,14,15,16,17},  // Z medio
        {18,19,20,21,22,23,24,25,26}, // Z izquierda
        {6,7,8,15,16,17,24,25,26},    // Y derecha
        {3,4,5,12,13,14,21,22,23},    // Y medio
        {0,1,2,9,10,11,18,19,20},     // Y izquierda
        {2,5,8,11,14,17,20,23,26},    // X derecha
        {1,4,7,10,13,16,19,22,25},    // X medio
        {0,3,6,9,12,15,18,21,24},     // X izquierda
    };
    public:
        Rubik();
        void dibujar();
        bool estaEnMapaDeRotacion(int rotacion, int posicion);
        void rotar(int cara, int angulo, float eje[3]);
        void rotarZ(int cara, int angulo);
        void rotarZDer(int angulo);
        void rotarZMed(int angulo);
        void rotarZIzq(int angulo);
        void rotarY(int cara, int angulo);
        void rotarYDer(int angulo);
        void rotarYMed(int angulo);
        void rotarYIzq(int angulo);
        void rotarX(int cara, int angulo);
        void rotarXDer(int angulo);
        void rotarXMed(int angulo);
        void rotarXIzq(int angulo);
};

/*
 * Genera todas las piezas asignandoles su color, y su posición en el cubo
 * (ver MAPA_COLORES_RUBIK y MAPA_POSICIONES_RUBIK)
 */
Rubik::Rubik() {
    int i = 0;

    for (i = 0; i < PIEZAS; i++)
        cubos[i] = Cubo(MAPA_COLORES_RUBIK[i], MAPA_POSICIONES_RUBIK[i], i);
}

/*
 * Genera la rotaciones para una cara del cubo
 * cara: entero que indica cuál cara del cubo se quiere rotar
 *       (ver mapa de rotaciones)
 * angulo: ángulo que se queire rotar la cara
 * eje: Eje sobre el cual se quiere rotar (x, y, z)
 */
void Rubik::rotar(int cara, int angulo, float eje[3]) {
    int i = 0;

    for (i = 0; i < PIEZAS; i++) {
        if (estaEnMapaDeRotacion(cara, cubos[i].getPosicion()))
            cubos[i].rotar(angulo, eje);
        else
            cubos[i].dibujar();
    }
}

void Rubik::rotarX(int cara, int angulo) {
    float ejeX[3] = {1,0,0};

    rotar(cara, angulo, ejeX);
}

void Rubik::rotarY(int cara, int angulo) {
    float ejeY[3] = {0,1,0};

    rotar(cara, angulo, ejeY);
}

void Rubik::rotarZ(int cara, int angulo) {
    float ejeZ[3] = {0,0,1};

    rotar(cara, angulo, ejeZ);
}

void Rubik::rotarXDer(int angulo) {
    rotarX(6, angulo);
}

void Rubik::rotarXMed(int angulo) {
    rotarX(7, angulo);
}

void Rubik::rotarXIzq(int angulo) {
    rotarX(8, angulo);
}

void Rubik::rotarYDer(int angulo) {
    rotarY(3, angulo);
}

void Rubik::rotarYMed(int angulo) {
    rotarY(4, angulo);
}

void Rubik::rotarYIzq(int angulo) {
    rotarY(5, angulo);
}

void Rubik::rotarZDer(int angulo) {
    rotarZ(0, angulo);
}

void Rubik::rotarZMed(int angulo) {
    rotarZ(1, angulo);
}

void Rubik::rotarZIzq(int angulo) {
    rotarZ(2, angulo);
}

/*
 * Dibuja todas las piezas que componen al rubik
 */
void Rubik::dibujar() {
    int i = 0;

    for (i = 0; i < 27; i++) {
        cubos[i].dibujar();
    }
}

/*
 * Verifica si alguna pieza del cubo debe rotar
 * return: devuelve true si la pieza debe rotar
 * ( ver MAPA_ROTACIONES)
 */
bool Rubik::estaEnMapaDeRotacion(int rotacion, int posicion) {
    int i = 0;

    for (i = 0; i < 9; i++)
        if (MAPA_ROTACIONES[rotacion][i] == posicion)
            return true;
    return false;
}

/*
 * Función para generar los fps, en GNU/Linux
 */
unsigned GetTickCount() {
    struct timeval tv;

    return (gettimeofday(&tv, NULL) != 0) ? 0 :
                                    (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void animacion()
{
    // Calcula el número de frames por segundo
    dwCurrentTime = GetTickCount();
    dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

    if(dwElapsedTime >= 30) {
        angulo = (angulo + 1) % 360;
        dwLastUpdateTime = dwCurrentTime;
    }
    glutPostRedisplay();
}

// Función para configurar OpenGL
void InitGL(void)
{
    glClearColor(0.9f, .9f, .9f, 1.0f); // Blanco de fondo
    glClearDepth(1.0f); // Configuramos Depth Buffer
    glEnable(GL_DEPTH_TEST); // Habilitamos Depth Testing
    glDepthFunc(GL_LEQUAL); // Tipo de Depth Testing a realizar
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}



// Función de dibujo
void display(void)
{
    Rubik r[9] = {
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik(),
            Rubik()
    };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla y buffer
	glLoadIdentity();
    glTranslatef(moverEjeX, 0.0f, moverEjeY + POSICION_INICIAL_Z);
    glRotatef(rotarEjeX, 1.0, 0.0, 0.0);
    glRotatef(rotarEjeY, 0.0, 1.0, 0.0);
    r[3].rotarZMed(angulo);
    glTranslatef(-4.0f, 4.0f,0);
    r[1].rotarYIzq(angulo);
    glTranslatef(4.0f, 0.0f,0);
    r[2].rotarYMed(angulo);
    glTranslatef(4.0f, 0.0f,0);
    r[0].rotarYDer(angulo);
    glTranslatef(0.0f, -4.0f,0);
    r[4].rotarZIzq(angulo);
    glTranslatef(0.0f, -4.0f,0);
    r[6].rotarXIzq(angulo);
    glTranslatef(-4.0f, 0.0f,0);
    r[8].rotarXMed(angulo);
    glTranslatef(-4.0f, 0.0f,0);
    r[7].rotarXDer(angulo);
    glTranslatef(0.0f, 4.0f,0);
    r[5].rotarZDer(angulo);
    glutSwapBuffers ( ); // Swap The Buffers
}

// Para actualizar parámetros cuando cambia de tamaño la ventana
void reshape ( int width , int height )
{
    height = (height == 0) ? 1 : height; // Evita división por cero
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Tipo de Vista
    glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

// Para manejar el teclado
void keyboard ( unsigned char key, int x, int y )
{
	switch(key) {
        case 'a':
        case 'A':
            rotarEjeY += 3;
            break;
        case 'd':
        case 'D':
            rotarEjeY -= 3;
            break;
        case 'w':
        case 'W':
            rotarEjeX += 3;
            break;
        case 's':
        case 'S':
            rotarEjeX -= 3;
            break;
        case 27: // Tecla ESC para salir
            exit(0);
            break;
    }
  glutPostRedisplay();
}

// Para el manejo de teclas especiales (flechas)
void arrow_keys (int a_keys, int x, int y)
{
    switch ( a_keys ) {
    case GLUT_KEY_UP:
        moverEjeY +=2.5f;
        break;
    case GLUT_KEY_DOWN:
        moverEjeY -= 2.5f;
        break;
    case GLUT_KEY_LEFT:
        moverEjeX += 2.5f;
        break;
    case GLUT_KEY_RIGHT:
        moverEjeX -= 2.5f;
        break;
    }
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Rubik");
    InitGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys); // Manejo de las teclas especiales
    glutIdleFunc(animacion); // Para crear las animacione
    glutMainLoop(); // arranca el loop

  return 0;
}
