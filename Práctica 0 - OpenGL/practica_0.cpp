#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

void Ejes (int width)
{
    glLineWidth(width);
    glBegin(GL_LINES);
       glColor3f(1.0,0.0,0.0);
       glVertex3f(-1.0,0.0,0.0);
       glVertex3f(1.0,0.0,0.0);
       glColor3f(0.0,1.0,0.0);
       glVertex3f(0.0,-1.0,0.0);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,1.0,0.0);
    glEnd();


}

// Círculos
void circle(GLfloat radio, GLfloat cx, GLfloat cy, GLint n, GLenum modo){
  if(modo==GL_LINE){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }else if(modo==GL_FILL){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }else{
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
  }

  glBegin(GL_POLYGON);
    for(int i=0; i<n; i++){
      glVertex3f(cx+radio*cos(2.0*M_PI*i/n), cy+radio*sin(2.0*M_PI*i/n), 0.0);
    }
  glEnd();
}

void poligonoSolido(float v[][3], int n){
  int i;

  glPolygonMode(GL_FRONT, GL_FILL);
  glBegin(GL_POLYGON);
    for(i=0; i<n; i++){
      glVertex3f(v[i][0], v[i][1], v[i][2]);
    }
  glEnd();
}

void poligonoHueco(float v[][3], int n){
  int i;

  glPolygonMode(GL_FRONT, GL_LINE);
  glBegin(GL_POLYGON);
    for(i=0; i<n; i++){
      glVertex3f(v[i][0], v[i][1], v[i][2]);
    }
  glEnd();
}

void Monigote ()
{
// cara
   /* glLineWidth(1);
   glColor3f(1.0,0.8,0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd();

   glColor3f(0.0,0.0,0.);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_POLYGON);
      glVertex3f(-0.2,0.0,0.0);
      glVertex3f(0.2,0.0,0.0);
      glVertex3f(0.2,0.55,0.0);
      glVertex3f(-0.2,0.55,0.0);
   glEnd(); */

   // Pruebas

   // Cabeza
   glColor3f(1.0, 1.0, 0.0);
   circle(0.5, 0.0, 0.0, 40, GL_FILL);

   // Ojos
   // Derecho de frente
   glColor3f(0.0, 0.0, 0.0);
   circle(0.1, 0.2, 0.2, 40, GL_FILL);

   glColor3f(1.0, 1.0, 1.0);
   circle(0.04, 0.19, 0.21, 40, GL_FILL);

   // Izquierdo de frente
   glColor3f(0.0, 0.0, 0.0);
   circle(0.1, -0.2, 0.2, 40, GL_FILL);

   glColor3f(1.0, 1.0, 1.0);
   circle(0.04, -0.19, 0.21, 40, GL_FILL);


   // Mofletes
   // Derecho de frente
   glColor3f(1.0, 0.0, 0.0);
   circle(0.09, 0.3, 0.0, 40, GL_FILL);

   // Izquierdo de frente
   glColor3f(1.0, 0.0, 0.0);
   circle(0.09, -0.3, 0.0, 40, GL_FILL);


   // Nariz
   float nariz[3][3]={{0.0, -0.08 ,0.0},
                      {0.05, -0.0, 0.0},
                      {-0.05, -0.0, 0.0}};
   glColor3f(0.0, 0.0, 0.0);
   poligonoSolido(nariz, 3);


   // Boca
   glColor3f(0.0, 0.0, 0.0);
   // glEnable(GL_LINE_STIPPLE);

   // glLineStipple(1, 0x00FF);
   glBegin(GL_LINES);
      glVertex3f(0.1, -0.23, 0.0);
      glVertex3f(-0.1, -0.23, 0.0);
   glEnd();
   // glDisable(GL_LINE_STIPPLE);


   // Orejas
   float orejaDcha[4][3]={{0.2, 0.3, 0.0},
                          {0.35, 0.3, 0.0},
                          {0.55, 0.6, 0.0},
                          {0.4, 0.6, 0.0}};
   float puntaDcha[3][3]={{0.55, 0.6, 0.0},
                          {0.4, 0.6, 0.0},
                          {0.6, 0.8, 0.0}};
   float orejaIzda[4][3]={{-0.2, 0.3, 0.0},
                          {-0.35, 0.3, 0.0},
                          {-0.55, 0.6, 0.0},
                          {-0.4, 0.6, 0.0}};
   float puntaIzda[3][3]={{-0.55, 0.6, 0.0},
                          {-0.4, 0.6, 0.0},
                          {-0.6, 0.8, 0.0}};

   // Derecha de frente
   glColor3f(1.0, 1.0, 0.0);
   poligonoSolido(orejaDcha, 4);

   glColor3f(0.0, 0.0, 0.0);
   poligonoSolido(puntaDcha, 3);

   // Derecha de frente
   glColor3f(1.0, 1.0, 0.0);
   poligonoSolido(orejaIzda, 4);

   glColor3f(0.0, 0.0, 0.0);
   poligonoSolido(puntaIzda, 3);

   // Fin de pruebas
}

static void Init( )
{

   glShadeModel( GL_FLAT);
}


static void Reshape( int width, int height )
{
    glViewport(0, 0, (GLint)width, (GLint)height);
    glOrtho (-1.0, 1.0,-1.0, 1.0, -10, 10.0);
}

static void Display( )
{

  glClearColor(0.5,0.5,0.5,0.0);
  glClear( GL_COLOR_BUFFER_BIT );



   Ejes(6);
   Monigote();

   glFlush();
}


static void Keyboard(unsigned char key, int x, int y )
{

  if (key==27)
      exit(0);

}


int main( int argc, char **argv )
{
   glutInit(&argc,argv);
   glutInitDisplayMode( GLUT_RGB );

   glutInitWindowPosition( 20, 100 );
   glutInitWindowSize(500, 500 );
   glutCreateWindow("Practica 0 IG");


   Init();

   glutReshapeFunc(Reshape);
   glutDisplayFunc(Display);
   glutKeyboardFunc(Keyboard);

   glutMainLoop( );

   return 0;
}
