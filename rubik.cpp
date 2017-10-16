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
 * Se utilizan las flechas del teclado para rotarlo
 */

#include <GL/glut.h>

#define UNIDAD_CUBO 0.45

typedef struct _color {
    float r,g,b;
} COLOR_RGB;

// Posición en el eje ortogonal a la pantalla
float transZ = -5.0f;

// Para rotar el cubo
float angulo_y = 0.0;
float angulo_x = 0.0;

// Colores del rubik
COLOR_RGB red = { 1.0, 0.0, 0.0 };
COLOR_RGB green = { 0.0,1.0,0.0 };
COLOR_RGB yellow= {1,1,0};
COLOR_RGB blue = { 0.0,0.0,1.0 };
COLOR_RGB white = { 1.0,1.0,1.0 };
COLOR_RGB orange = {1, .549, 0};
COLOR_RGB black = {0.0 , 0.0, 0.0};

// Colores de los centros de cada cara
COLOR_RGB centro_front[6] = {
    orange, black, black, black, black, black
};
COLOR_RGB centro_back[6] = {
    black, white, black, black, black, black
};
COLOR_RGB centro_left[6] = {
    black, black, green, black, black, black
};
COLOR_RGB centro_right[6] = {
    black, black, black, red, black, black
};
COLOR_RGB centro_top[6] = {
    black, black, black, black, blue, black
};
COLOR_RGB centro_bottom[6] = {
    black, black, black, black, black, yellow
};

// Colores de las esquinas
COLOR_RGB cubo_esquina_sup_der[6] = {
    orange, black, black, red, blue, black
};
COLOR_RGB cubo_esquina_sup_izq[6] = {
    orange, black, green, black, blue, black
};
COLOR_RGB cubo_esquina_inf_izq[6] = {
    orange, black, green, black, black, yellow
};
COLOR_RGB cubo_esquina_inf_der[6] = {
    orange, black, black, red, black, yellow
};
COLOR_RGB cubo_esquina_sup_der2[6] = {
    black, white, black, red, blue, black
};
COLOR_RGB cubo_esquina_inf_der2[6] = {
    black, white, black, red, black, yellow
};
COLOR_RGB cubo_esquina_sup_izq2[6] = {
    black, white, green, black, blue, black
};
COLOR_RGB cubo_esquina_inf_izq2[6] = {
    black, white, green, black, black, yellow
};

// Colores de las partes en la orilla pero en medio
COLOR_RGB cubo_medio_arriba[6] = {
    orange, black, black, black, blue, black
};
COLOR_RGB cubo_medio_abajo[6] = {
    orange, black, black, black, black, yellow
};
COLOR_RGB cubo_medio_der[6] = {
    orange, black, black, red, black, black
};
COLOR_RGB cubo_medio_izq[6] = {
    orange, black, green, black, black, black
};
COLOR_RGB cubo_medio_arriba2[6] = {
    black, white,  black, black, blue, black
};
COLOR_RGB cubo_medio_abajo2[6] = {
    black, white, black, black, black, yellow
};
COLOR_RGB cubo_medio_der2[6] = {
     black, white, green, black, black, black
};
COLOR_RGB cubo_medio_izq2[6] = {
     black, white, black, red, black, black
};
COLOR_RGB cubo_medio_arriba_der[6] = {
     black, black, black, red, blue, black
};
COLOR_RGB cubo_medio_abajo_der[6] = {
     black, black, black,red, black,yellow
};
COLOR_RGB cubo_medio_arriba_izq[6] = {
     black, black, green, black, blue, black
};
COLOR_RGB cubo_medio_abajo_izq[6] = {
     black, black, green, black, black, yellow
};

// Función para configurar OpenGL
void InitGL(void)
{
	glClearColor(0.9f, .9f, .9f, 1.0f); // Blanco de fondo
	glClearDepth(1.0f); // Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST); // Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL); // Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/*
 * color: arreglo con cada color para cada cara de un cubo
 * color[0]: front
 * color[1]: back
 * color[2]: left
 * color[3]: right
 * color[4]: top
 * color[5]: bottom
 */
void prisma(float color[6][3])
{
    // Coordenadas del cubo con 2*UNIDAD_CUBO de largo cada lado
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

	glBegin(GL_POLYGON);	//Front
    glColor3fv(color[0]);
		glVertex3fv(vertice[0]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
    glColor3fv(color[1]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[3]);
		glVertex3fv(vertice[2]);
	glEnd();
	glBegin(GL_POLYGON);  //Left
    glColor3fv(color[2]);
		glVertex3fv(vertice[1]);
		glVertex3fv(vertice[7]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[2]);
	glEnd();
    glBegin(GL_POLYGON);	//Right
    glColor3fv(color[3]);
    glVertex3fv(vertice[0]);
    glVertex3fv(vertice[3]);
    glVertex3fv(vertice[5]);
    glVertex3fv(vertice[4]);
    glEnd();
	glBegin(GL_POLYGON);  //Top
    glColor3fv(color[4]);
		glVertex3fv(vertice[4]);
		glVertex3fv(vertice[5]);
		glVertex3fv(vertice[6]);
		glVertex3fv(vertice[7]);
	glEnd();
    glBegin(GL_POLYGON);  //Bottom
    glColor3fv(color[5]);
    glVertex3fv(vertice[0]);
    glVertex3fv(vertice[1]);
    glVertex3fv(vertice[2]);
    glVertex3fv(vertice[3]);
    glEnd();
}

void prisma(COLOR_RGB colores[6])
{
    float cols[6][3] = {
        {colores[0].r, colores[0].g, colores[0].b},
        {colores[1].r, colores[1].g, colores[1].b},
        {colores[2].r, colores[2].g, colores[2].b},
        {colores[3].r, colores[3].g, colores[3].b},
        {colores[4].r, colores[4].g, colores[4].b},
        {colores[5].r, colores[5].g, colores[5].b}
    };
    prisma(cols);
}

void prisma(COLOR_RGB color)
{
    COLOR_RGB colores[6] = {
        color, color, color, color, color, color
    };
	prisma(colores);
}

// Función de dibujo
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpia pantalla y buffer
	glLoadIdentity();

    glTranslatef(0.0f, 0.0f, transZ);
    // Par girar el cubo
    glRotatef(angulo_y, 0.0, 1.0, 0.0);
    glRotatef(angulo_x, 1.0, 0.0, 0.0);
    prisma(white); // Cubo del centro

    glPushMatrix(); // front, cara que se visualiza primero (orange)
	   glTranslatef(0.0f, 0.0f, 1.0);
       prisma(centro_front);
    glPopMatrix();

    glPushMatrix(); // front esquina sup izq
	   glTranslatef(-1.0f, 1.0f, 1.0);
       prisma(cubo_esquina_sup_izq);
    glPopMatrix();

    glPushMatrix(); // front esquina sup derecha
	   glTranslatef(1.0f, 1.0f, 1.0);
       prisma(cubo_esquina_sup_der);
    glPopMatrix();

    glPushMatrix(); // front esquina inf izq
	   glTranslatef(-1.0f, -1.0f, 1.0);
       prisma(cubo_esquina_inf_izq);
    glPopMatrix();

    glPushMatrix(); // front esquina 1
	   glTranslatef(1.0f, -1.0f, 1.0);
       prisma(cubo_esquina_inf_der);
    glPopMatrix();

    glPushMatrix(); // front arriba
	   glTranslatef(0.0f, 1.0f, 1.0);
       prisma(cubo_medio_arriba);
    glPopMatrix();

    glPushMatrix(); // front abajo
	   glTranslatef(0.0f, -1.0f, 1.0);
       prisma(cubo_medio_abajo);
    glPopMatrix();

    glPushMatrix(); // front derecha
	   glTranslatef(1.0f, 0.0f, 1.0);
       prisma(cubo_medio_der);
    glPopMatrix();

    glPushMatrix(); // front izq
	   glTranslatef(-1.0f, 0.0f, 1.0);
       prisma(cubo_medio_izq);
    glPopMatrix();

    glPushMatrix(); // left
	   glTranslatef(-1.0f, 0.0f, 0.0);
       prisma(centro_left);
    glPopMatrix();

    glPushMatrix(); // left arriba
	   glTranslatef(-1.0f, 1.0f, 0.0);
       prisma(cubo_medio_arriba_izq);
    glPopMatrix();

    glPushMatrix(); // left abajo
	   glTranslatef(-1.0f, -1.0f, 0.0);
       prisma(cubo_medio_abajo_izq);
    glPopMatrix();

    glPushMatrix(); // Left esquina superior izquierda
	   glTranslatef(-1.0f, 1.0f, -1.0);
       prisma(cubo_esquina_sup_izq2);
    glPopMatrix();

    glPushMatrix(); // Left esquina inferior izquierda
	   glTranslatef(-1.0f, -1.0f, -1.0);
       prisma(cubo_esquina_inf_izq2);
    glPopMatrix();

    glPushMatrix(); //Right
	   glTranslatef(1.0f, 0.0f, 0.0);
       prisma(centro_right);
    glPopMatrix();

    glPushMatrix(); // Right arriba
	   glTranslatef(1.0f, 1.0f, 0.0);
       prisma(cubo_medio_arriba_der);
    glPopMatrix();

    glPushMatrix(); // right abajo
	   glTranslatef(1.0f, -1.0f, 0.0);
       prisma(cubo_medio_abajo_der);
    glPopMatrix();

    glPushMatrix();  // Right esquina superior derecha
	   glTranslatef(1.0f, 1.0f, -1.0);
       prisma(cubo_esquina_sup_der2);
    glPopMatrix();

    glPushMatrix();  // Right esquina inferior derecha
	   glTranslatef(1.0f, -1.0f, -1.0);
       prisma(cubo_esquina_inf_der2);
    glPopMatrix();

    glPushMatrix(); // back
	   glTranslatef(0.0f, 0.0f, -1.0);
       prisma(centro_back);
    glPopMatrix();
    glPushMatrix(); // back arriba
	   glTranslatef(0.0f, 1.0f, -1.0);
       prisma(cubo_medio_arriba2);
    glPopMatrix();

    glPushMatrix(); // back abajo
	   glTranslatef(0.0f, -1.0f, -1.0);
       prisma(cubo_medio_abajo2);
    glPopMatrix();

    glPushMatrix(); // back derecha
	   glTranslatef(-1.0f, 0.0f, -1.0);
       prisma(cubo_medio_der2);
    glPopMatrix();

    glPushMatrix(); // back izq
	   glTranslatef(1.0f, 0.0f, -1.0);
       prisma(cubo_medio_izq2);
    glPopMatrix();

    glPushMatrix(); // top
	   glTranslatef(0.0f, 1.0f, 0.0);
       prisma(centro_top);
    glPopMatrix();

    glPushMatrix(); // bottom
	   glTranslatef(0.0f, -1.0f, 0.0);
       prisma(centro_bottom);
    glPopMatrix();

  glutSwapBuffers ( );
  // Swap The Buffers
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
        angulo_x +=2.5f;
		break;
    case GLUT_KEY_DOWN:
		angulo_x -= 2.5f;
		break;
	case GLUT_KEY_LEFT:
        angulo_y += 2.5f;
		break;
	case GLUT_KEY_RIGHT:
		angulo_y -= 2.5f;
		break;
  }
  glutPostRedisplay();
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Rubik");
  InitGL();
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutKeyboardFunc( keyboard );
  glutSpecialFunc(arrow_keys); // Manejo de las teclas especiales
  glutMainLoop(); // arranca el loop

  return 0;
}
