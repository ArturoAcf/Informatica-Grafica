//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION,
						 CILINDRO /*Práctica 2*/,
						 ESFERA, /*Práctica 2,*/ MAGO, /*Práctica 3*/} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply;
_rotacion rotacion;

// Práctica 2
_cilindro cilindro;
_esfera esfera;

// Práctica 3
_mago mago;
int mov=0; // Para la animación

// _objeto_ply *ply1;

// Práctica 4
int gLuz=0;
int gL=0;

//***************************************************************************//

void clean_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis(){
	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1,0,0);
	glVertex3f(-AXIS_SIZE,0,0);
	glVertex3f(AXIS_SIZE,0,0);
	// eje Y, color verde
	glColor3f(0,1,0);
	glVertex3f(0,-AXIS_SIZE,0);
	glVertex3f(0,AXIS_SIZE,0);
	// eje Z, color azul
	glColor3f(0,0,1);
	glVertex3f(0,0,-AXIS_SIZE);
	glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************************************************************

void draw_objects(){
	switch (t_objeto){
		case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	  case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
	  case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
		case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break; // Práctica 2
		case ESFERA: esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break; // Práctica 2
		case MAGO: mago.draw(modo,0.0,0.0,0.0,1.0,1.0,1.0,2);break; // Práctica 3
	}
}

// Práctica 4
void luces(){
	float  luz1[]={1.0, 1.0, 1.0, 1.0},
	       pos1[]= {10.0, 20.0, 40.0, 1.0},
				 luz2[]={1.0, 0.0, 0.0, 1.0},
				 pos2[]={15.0, 10.0, 20.0, 0.0};

	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
	glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);
	glLightfv (GL_LIGHT1, GL_POSITION, pos1);

	glPushMatrix();
		glRotatef(gLuz,0,1,0);
		glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
		glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);
		glLightfv (GL_LIGHT2, GL_POSITION, pos2);
		glEnable (GL_LIGHT2);
	glPopMatrix();

	glDisable (GL_LIGHT0);
	glEnable (GL_LIGHT1);
}


//**************************************************************************
//
//***************************************************************************

void draw(void){
	clean_window();
	change_observer();
	draw_axis();
	luces(); // Práctica 4
	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
	float Aspect_ratio;

	Aspect_ratio=(float) Alto1/(float )Ancho1;
	Size_y=Size_x*Aspect_ratio;
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y){
	switch (toupper(Tecla1)){
		case 'Q':exit(0);
		case '1':modo=POINTS;break;
		case '2':modo=EDGES;break;
		case '3':modo=SOLID;break;
		case '4':modo=SOLID_CHESS;break;
		case '5':modo=SOLID_ILLUMINATED_FLAT;break; // Práctica 4
		case '6':modo=SOLID_ILLUMINATED_GOURAUD;break; // Práctica 4
	        case 'P':t_objeto=PIRAMIDE;break;
	        case 'C':t_objeto=CUBO;break;
	        case 'O':t_objeto=OBJETO_PLY;break;
	        case 'R':t_objeto=ROTACION;break;
					case 'I':t_objeto=CILINDRO;break; // Práctica 2
					case 'E':t_objeto=ESFERA;break; // Práctica 2
					case 'M':t_objeto=MAGO;break; // Práctica 3
		}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y){
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;break;
		case GLUT_KEY_UP:Observer_angle_x--;break;
		case GLUT_KEY_DOWN:Observer_angle_x++;break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
			// Práctica 3
	        case GLUT_KEY_F1:mago.brazos.giroBrazo+=1;
	                         if (mago.brazos.giroBrazo>mago.brazos.giroBMax) mago.brazos.giroBrazo=mago.brazos.giroBMax;
	                         break;
	        case GLUT_KEY_F2:mago.brazos.giroBrazo-=1;
	                         if (mago.brazos.giroBrazo<mago.brazos.giroBMin) mago.brazos.giroBrazo=mago.brazos.giroBMin;
	                         break;break;
					case GLUT_KEY_F5:mago.giroB1+=1;
	                         if (mago.giroB1>mago.giroMax) mago.giroB1=mago.giroMax;
	                         break;
					case GLUT_KEY_F4:mov++;
													 break;
	        case GLUT_KEY_F6:mago.giroB1-=1;
	                         if (mago.giroB1<mago.giroMin) mago.giroB1=mago.giroMin;
	                         break;break;
				  case GLUT_KEY_F7:mago.giroB2+=1;
	                         if (mago.giroB2>mago.giroMax) mago.giroB2=mago.giroMax;
	                         break;
	        case GLUT_KEY_F8:mago.giroB2-=1;
	                         if (mago.giroB2<mago.giroMin) mago.giroB2=mago.giroMin;
	                         break;break;
					case GLUT_KEY_F9:mago.giroChistera+=1;
										 			 mago.giroBrillo-=1;
													 break;
					case GLUT_KEY_F10:mago.giroCC+=1;
		                       if (mago.giroCC>mago.giroMaxCC) mago.giroCC=mago.giroMaxCC;
		                       break;
		      case GLUT_KEY_F11:mago.giroCC-=1;
		                       if (mago.giroCC<mago.giroMinCC) mago.giroCC=mago.giroMinCC;
		                       break;break;
			  	case GLUT_KEY_F3:gL++;
 		                       break;break;
		}
	glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Size_x=0.5;
	Size_y=0.5;
	Front_plane=1;
	Back_plane=1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance=4*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


// Práctica 3

// Función para el movimiento constante del brillo y la chistera
void movimiento(){
	if(mov%2==1){
		mago.chistera.giroCte++;
		mago.giroBCte++;
		glutPostRedisplay();
	}

	if(gL%2==1){
		gLuz++;
		glutPostRedisplay();
	}
}


int main(int argc, char **argv){
	// creación del objeto ply
	ply.parametros(argv[1]);


	// perfil
	vector<_vertex3f> perfil2;
	_vertex3f aux;
	aux.x=1.0;aux.y=-1.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=1.0;aux.y=-1.1;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=-0.7;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=-0.4;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.4;aux.y=0.5;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=0.6;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=0.8;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.55;aux.y=1.0;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.5;aux.y=1.2;aux.z=0.0;
	perfil2.push_back(aux);
	aux.x=0.3;aux.y=1.4;aux.z=0.0;
	perfil2.push_back(aux);
	rotacion.parametros(perfil2,6,1,0);

	/****************************************************************************/
	// Práctica 2  -  Sin Cono
	/****************************************************************************/

	// Cilindro
	cilindro.dibujarCilindro(2);

	// Esfera
	esfera.dibujarEsfera(0);

	/****************************************************************************/
	// Práctica 4
	/****************************************************************************/

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x,Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width,Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	glutIdleFunc(movimiento);

	// funcion de inicialización
	initialize();

	// inicio del bucle de eventos
	glutMainLoop();

	return 0;
}
