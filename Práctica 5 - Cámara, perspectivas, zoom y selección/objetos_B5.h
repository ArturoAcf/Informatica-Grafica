//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,
             SOLID_ILLUMINATED_FLAT, /*Práctica 4*/
             SOLID_ILLUMINATED_GOURAUD, /*Práctica 4*/
             SELECT /*Práctica 5*/} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
	_puntos3D();
  void draw_puntos(float r, float g, float b, int grosor);
  vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:
	_triangulos3D();
  void draw_aristas(float r, float g, float b, int grosor);
  void    draw_solido(float r, float g, float b);
  void draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);

  void	calcular_normales_caras(); // P4
  void 	draw_iluminacion_plana( ); // P4

  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

  void 	calcular_normales_vertices(); // P4
  void 	draw_iluminacion_suave( ); // P4

  void calcular_normales_vertices_esfera(); // Práctica 4

  void draw_seleccion(int r, int g, int b); // Práctica 5

  vector<_vertex3i> caras;

  vector<_vertex3f> normales_caras; // P4
  vector<_vertex3f> normales_vertices; // P4

  bool b_normales_caras; // P4 -> Asegurarse de que solo se calculan una vez
  bool b_normales_vertices; // P4

  _vertex4f ambiente_difusa;     // coeficientes ambiente y difuso // P4 -> Ka = Ks
  _vertex4f especular;           // coeficiente especular // P4
  float brillo;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:
	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:
	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();
   int parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
  _rotacion();
  void parametros(vector<_vertex3f> perfil1, int num1, int tapas, float hesf);
  vector<_vertex3f> perfil;
  int num;
};

/****************************************************************************/
// Práctica 2
/****************************************************************************/

// Cilindro
class _cilindro: public _rotacion{
public:
  _cilindro();
  void dibujarCilindro(int tapas);
  void dibujarCilindroPerfil(vector<_vertex3f> perfil_cilindro,int rotaciones, int tapas);
};

// Esfera
class _esfera: public _rotacion{
public:
  _esfera();
  void dibujarEsfera(int tapas);
  void dibujarEsferaPerfil(vector<_vertex3f> perfi_esfera, int rotaciones, int tapas, float hesf);
};


/****************************************************************************/
// Práctica 3
/****************************************************************************/

// Clase _chistera
class _chistera: public _triangulos3D{
public:
  _chistera();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
  float giroCte;

protected:
  _cilindro copa, base;
};

// Clase _cabeza
class _cabeza: public _triangulos3D{
public:
  _cabeza();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _esfera cab;
};

// Clase _cuerpo
class _cuerpo: public _triangulos3D{
public:
  _cuerpo();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _cilindro tronco, cuello;
};

// Clase _piernas
class _piernas: public _triangulos3D{
public:
  _piernas();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _cilindro muslo1, muslo2;
  _cubo pie1, pie2;
};

// Clase _brazos
class _brazos: public _triangulos3D{
public:
  _brazos();
  void brazo1(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
  void brazo2(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
  float giroBrazo, giroBMin, giroBMax;

  _cilindro br1, br2, biceps1, biceps2;
  _esfera mano1, mano2, codo1, codo2, hombro1, hombro2;
};

// Clase _conejo
/* class _conejo: public _triangulos3D{
public:
  _conejo();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _esfera cuerpo, cabeza, oreja1, oreja2, cola; // Chafar orejas tal que x=x/2
}; */

// Clase _brillo
class _brillo: public _triangulos3D{
public:
  _brillo();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _esfera e1, e2, e3, e4, e5;
};

// Clase _varita
class _varita: public _triangulos3D{
public:
  _varita();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
  _cilindro c1, c2, c3;
};

// Clase _mago para construir el objeto final
class _mago: public _triangulos3D{
public:
  _mago();
  void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
  float giroMax, giroMin, giroB1, giroB2, giroChistera, giroBrillo, giroCC, giroMaxCC, giroMinCC, giroBCte;

  // Práctica 5
  void seleccion();

  float color_pick[3];
  int color_selec[8][8];
  int activo[8];
  int piezas;

  // Práctica 2
  _cabeza cabeza;
  _chistera chistera;
  _cuerpo cuerpo;
  _brazos brazos;
  _varita varita;
  _brillo brillo;
  _piernas piernas;
};
