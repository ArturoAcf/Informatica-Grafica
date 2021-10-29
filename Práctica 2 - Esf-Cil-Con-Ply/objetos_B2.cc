//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido - Prácticas
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b){
	int i;
	glPolygonMode(GL_FRONT,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
	int i;
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if(i%2==0){
			glColor3f(r1,g1,b1);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}else{
			glColor3f(r2,g2,b2);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
		}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo - Práctica
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
vertices.resize(8);
vertices[0].x=0; vertices[0].y=0; vertices[0].z=tam;
vertices[1].x=tam; vertices[1].y=0; vertices[1].z=tam;
vertices[2].x=tam; vertices[2].y=0; vertices[2].z=0;
vertices[3].x=0; vertices[3].y=0; vertices[3].z=0;

vertices[4].x=0; vertices[4].y=tam; vertices[4].z=tam;
vertices[5].x=tam; vertices[5].y=tam; vertices[5].z=tam;
vertices[6].x=tam; vertices[6].y=tam; vertices[6].z=0;
vertices[7].x=0; vertices[7].y=tam; vertices[7].z=0;

// triangulos
caras.resize(12);
// Base
caras[0]._0=3;caras[0]._1=1;caras[0]._2=0;
caras[1]._0=3;caras[1]._1=2;caras[1]._2=1;

// Cara frontal
caras[2]._0=0;caras[2]._1=5;caras[2]._2=4;
caras[3]._0=0;caras[3]._1=1;caras[3]._2=5;

// Cara lateral derecha
caras[4]._0=1;caras[4]._1=2;caras[4]._2=5;
caras[5]._0=2;caras[5]._1=6;caras[5]._2=5;

// Cara lateral izquierda
caras[6]._0=0;caras[6]._1=4;caras[6]._2=7;
caras[7]._0=7;caras[7]._1=3;caras[7]._2=0;

// Tapa
caras[8]._0=4;caras[8]._1=5;caras[8]._2=6;
caras[9]._0=6;caras[9]._1=7;caras[9]._2=4;

// Cara trasera
caras[10]._0=2;caras[10]._1=3;caras[10]._2=7;
caras[11]._0=7;caras[11]._1=6;caras[11]._2=2;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices
vertices.resize(5);
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply()
{
   // leer lista de coordenadas de vértices y lista de indices de vértices

}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;

_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);

// Añadido
for(int i=0; i<n_ver; i++){
	vertices[i].x=ver_ply[3*i];
	vertices[i].y=ver_ply[3*i+1];
	vertices[i].z=ver_ply[3*i+2];
}

caras.resize(n_car);

// Añadido
for(int i=0; i<n_car; i++){
	caras[i]._0=car_ply[3*i];
	caras[i]._1=car_ply[3*i+1];
	caras[i]._2=car_ply[3*i+2];
}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, string x)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértices
num_aux=perfil.size();
vertices.resize(num_aux*num);

for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

	// tratamiento de las caras - Añadido
	caras.resize(2*(num_aux-1)*num);
	int c=0;

	for(int j=0; j<num; j++){
		for(int i=0; i<num_aux-1; i++){
			// CONO
			if(x=="k"){
				// Lados
				caras[c]._0=i+1+j*num_aux;
				caras[c]._1=i+1+((j+1)%num)*num_aux;
				caras[c]._2=i+((j+1)%num)*num_aux;
				c++;

			// CILINDRO
			}else if(x=="i"){ // Tapas del cilindro
				// Lados
				caras[c]._0=i+((j+1)%num)*num_aux;
				caras[c]._1=i+j*num_aux;
				caras[c]._2=i+1+j*num_aux;
				c++;

				caras[c]._0=i+1+j*num_aux;
				caras[c]._2=i+((j+1)%num)*num_aux;
				caras[c]._1=i+1+((j+1)%num)*num_aux;
				c++;

			// ESFERA
			}else if(x=="e"){
				// Lados
				caras[c]._0=i+1+j*num_aux;
				caras[c]._1=i+j*num_aux;
				caras[c]._2=i+((j+1)%num)*num_aux;
				c++;

				caras[c]._0=i+((j+1)%num)*num_aux;
				caras[c]._1=i+1+((j+1)%num)*num_aux;
				caras[c]._2=i+1+j*num_aux;
				c++;

				// Resto de casos
			}else{
				caras[c]._0=i+1+j*num_aux;
				caras[c]._1=i+j*num_aux;
				caras[c]._2=i+((j+1)%num)*num_aux;
				c++;

				caras[c]._0=i+((j+1)%num)*num_aux;
				caras[c]._1=i+1+((j+1)%num)*num_aux;
				caras[c]._2=i+1+j*num_aux;
				c++;
			}
		} // Fin for 2
	} // Fin for 1

	if(x=="i"){ // Cilindro
		// Tapa Superior
		if(fabs(perfil[0].x)>0.0){
			vertice_aux.x=0.0; vertice_aux.y=1.7; vertice_aux.z=0.0;
			vertices.push_back(vertice_aux);

			for(i=0; i<num_aux*num; i+=2){
				cara_aux._0=vertices.size()-1;
				cara_aux._1=i;
				cara_aux._2=(i+2)%(vertices.size()-1);
				caras.push_back(cara_aux);
			}
		}

		// Tapa inferior
		if(fabs(perfil[num_aux-1].x)>0.0){
			vertice_aux.x=0.0; vertice_aux.y=0.0; vertice_aux.z=0.0;
			vertices.push_back(vertice_aux);

			for(i=1; i<num_aux*num; i+=2){
				cara_aux._0=vertices.size()-1;
				cara_aux._1=(i+2)%(vertices.size()-2);
				cara_aux._2=i;
				caras.push_back(cara_aux);
			}
		}
	}else if(x=="k"){ // Cono
		// Tapa inferior
		vertice_aux.x=0.0; vertice_aux.y=0.0; vertice_aux.z=0.0;
		vertices.push_back(vertice_aux);

		for(i=3; i<num_aux*num; i+=2){
			cara_aux._0=vertices.size()-1;
			cara_aux._1=(i+2)%(vertices.size()-1);
			cara_aux._2=i;
			caras.push_back(cara_aux);
		}

		// Introduzco al final la primera cara de la base para
		// que se alternen los colores con respecto a los de los lados
		cara_aux._0=vertices.size()-1;
		cara_aux._1=(3)%(vertices.size()-1);
		cara_aux._2=1;
		caras.push_back(cara_aux);
	}else if(x=="e"){ // Esfera
		// Tapa inferior
		if(fabs(perfil[0].x)>0.0){
			vertice_aux.x=0.0; vertice_aux.y=-1.0; vertice_aux.z=0.0;
			vertices.push_back(vertice_aux);

			for(i=0; i<num_aux*num; i+=perfil.size()){
				cara_aux._0=(i+perfil.size())%(vertices.size()-1);
				cara_aux._1=i;
				cara_aux._2=vertices.size()-1;
				caras.push_back(cara_aux);
			}
		}

		// Tapa superior
		if(fabs(perfil[num_aux-1].x)>0.0){
			vertice_aux.x=0.0; vertice_aux.y=1.0; vertice_aux.z=0.0;
			vertices.push_back(vertice_aux);

			for(i=perfil.size(); i<num_aux*num; i+=perfil.size()){
				cara_aux._0=vertices.size()-1;
				cara_aux._1=i-1;
				cara_aux._2=(i+perfil.size()-1)%(vertices.size()-1); // (i+perfil.size())%(vertices.size()-1)
				caras.push_back(cara_aux);
			}

			// Introduzco la cara con el primer vértice y el último del primer círculo superior y el (0.0, 1.0, 0.0).
			cara_aux._0=8+9*15;
			cara_aux._1=8;
			cara_aux._2=vertices.size()-1;
			caras.push_back(cara_aux);
		}
	}else{ // Caso sin tapas
		// Nada
	}
} // Fin de función


/****************************************************************************/
// Práctica 2
/****************************************************************************/

// Cono
_cono::_cono(){
	_rotacion();
}

void _cono::dibujarCono(string x){
	vector<_vertex3f> perfil_cono;
	_vertex3f aux_cono;

	aux_cono.x=0.0; aux_cono.y=1.7; aux_cono.z=0.0;
	perfil_cono.push_back(aux_cono);
	aux_cono.x=1.0; aux_cono.y=0.0; aux_cono.z=0.0;
	perfil_cono.push_back(aux_cono);
	//aux_cono.x=0.0; aux_cono.y=0.0; aux_cono.z=0.0;
	//perfil_cono.push_back(aux_cono);

	parametros(perfil_cono, 16, x);
}

// Cilindro
_cilindro::_cilindro(){
	_rotacion();
}

void _cilindro::dibujarCilindro(string x){
	vector<_vertex3f> perfil_cilindro;
	_vertex3f aux_cilindro;

	aux_cilindro.x=1.0; aux_cilindro.y=1.7; aux_cilindro.z=0.0;
	perfil_cilindro.push_back(aux_cilindro);
	aux_cilindro.x=1.0; aux_cilindro.y=0.0; aux_cilindro.z=0.0;
	perfil_cilindro.push_back(aux_cilindro);
	/*aux_cilindro.x=0.0; aux_cilindro.y=0.0; aux_cilindro.z=0.0;
  perfil_cilindro.push_back(aux_cilindro);
	aux_cilindro.x=0.0; aux_cilindro.y=1.7; aux_cilindro.z=0.0;
  perfil_cilindro.push_back(aux_cilindro);*/

	parametros(perfil_cilindro, 16, x);
}

// Esfera
_esfera::_esfera(){
	_rotacion();
}

void _esfera::dibujarEsfera(string x){
	vector<_vertex3f> perfil_esfera;
	_vertex3f aux_esfera;
	for(int i=1; i<10; i++){
			aux_esfera.x=cos(M_PI*i/10-M_PI/2.0);
			aux_esfera.y=sin(M_PI*i/10-M_PI/2.0);
			aux_esfera.z=0.0;
			perfil_esfera.push_back(aux_esfera);
	}

	/*aux_esfera.x=0.0; aux_esfera.y=1.0; aux_esfera.z=0.0;
  perfil_esfera.push_back(aux_esfera);
	aux_esfera.x=0.0; aux_esfera.y=-1.0; aux_esfera.z=0.0;
	perfil_esfera.push_back(aux_esfera);*/

	parametros(perfil_esfera, 16, x);
}
