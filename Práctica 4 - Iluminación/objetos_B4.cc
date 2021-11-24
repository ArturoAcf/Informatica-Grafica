//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"
#include <GL/glut.h>


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D(){
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	//**** usando vertex_array ****
	glPointSize(grosor);
	glColor3f(r,g,b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawArrays(GL_POINTS,0,vertices.size());

	/*int i;
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
	for (i=0;i<vertices.size();i++){
		glVertex3fv((GLfloat *) &vertices[i]);
		}
	glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D(){
	// Práctica 4
	b_normales_caras=false;
	b_normales_vertices=false;

	ambiente_difusa=_vertex4f(0.2,0.4,0.9,1.0);  // coeficientes ambiente y difuso
	especular=_vertex4f(0.5,0.5,0.5,1.0);        // coeficiente especular
	brillo=50;                                   // exponente del brillo
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
	//**** usando vertex_array ****
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
	glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

	/*int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
		}
	glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

	void _triangulos3D::draw_solido(float r, float g, float b){
	int i;

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
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

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){
	int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i=0;i<caras.size();i++){
		if (i%2==0) glColor3f(r1,g1,b1);
		else glColor3f(r2,g2,b2);
			glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
			glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	switch (modo){
		case POINTS:draw_puntos(r1, g1, b1, grosor);break;
		case EDGES:draw_aristas(r1, g1, b1, grosor);break;
		case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
		case SOLID:draw_solido(r1, g1, b1);break;
		case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana( );break; // Pŕactiac 4
		case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break; // Práctica 4
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){
	//vertices
	vertices.resize(8);
	vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
	vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
	vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
	vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
	vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
	vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

	// triangulos
	caras.resize(12);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
	caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
	caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
	caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
	caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
	caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
	caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
	caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
	caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
	caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
	caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
	caras[11]._0=1;caras[11]._1=5;caras[11]._2=4;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al){
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


_objeto_ply::_objeto_ply(){
   // leer lista de coordenadas de vértices y lista de indices de vértices
}



int _objeto_ply::parametros(char *archivo){
	int n_ver,n_car;

	vector<float> ver_ply ;
	vector<int>   car_ply ;

	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;
	n_car=car_ply.size()/3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	//if (n_ver<3 || n_car<1){
	//	printf("Error %d %d\n",__FILE__,__LINE__);
	//	exit(-1);
	//	}

	vertices.resize(n_ver);
	caras.resize(n_car);

	_vertex3f ver_aux;
	_vertex3i car_aux;

	for (int i=0;i<n_ver;i++)
		{ver_aux.x=ver_ply[i*3];
		 ver_aux.y=ver_ply[i*3+1];
		 ver_aux.z=ver_ply[i*3+2];
		 vertices[i]=ver_aux;
		}

	for (int i=0;i<n_car;i++)
		{car_aux.x=car_ply[i*3];
		 car_aux.y=car_ply[i*3+1];
		 car_aux.z=car_ply[i*3+2];
		 caras[i]=car_aux;
		}

	return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion(){
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa, float hesf){
	int i,j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice

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

	// tratamiento de las caras
	caras.resize(2*(num_aux-1)*num);

		for (j=0;j<num;j++)
			{for (i=0;i<num_aux-1;i++){
				cara_aux._0=i+((j+1)%num)*num_aux;
				cara_aux._1=i+j*num_aux;
				cara_aux._2=i+1+j*num_aux;
				caras.push_back(cara_aux);

				cara_aux._0=i+1+j*num_aux;
				cara_aux._1=i+1+((j+1)%num)*num_aux;
				cara_aux._2=i+((j+1)%num)*num_aux;
				caras.push_back(cara_aux);
			}
		}

		if(tapa==2){ // Cilindro
			// Tapa Superior
			if(fabs(perfil[0].x)>0.0){
				vertice_aux.x=0.0; vertice_aux.y=perfil[0].y /*Nice*/; vertice_aux.z=0.0;
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
		}else if(tapa==0){ // Esfera
			// Tapa inferior
			if(fabs(perfil[0].x)>0.0){
				vertice_aux.x=0.0; vertice_aux.y=-hesf; vertice_aux.z=0.0;
				vertices.push_back(vertice_aux);

				for(i=0; i<num_aux*num; i+=perfil.size()){
					cara_aux._0=(i+perfil.size())%(vertices.size()-1);
					cara_aux._1=vertices.size()-1;
					cara_aux._2=i;
					caras.push_back(cara_aux);
				}
			}

			// Tapa superior
			if(fabs(perfil[num_aux-1].x)>0.0){
				vertice_aux.x=0.0; vertice_aux.y=hesf; vertice_aux.z=0.0;
				vertices.push_back(vertice_aux);

				for(i=perfil.size(); i<num_aux*num; i+=perfil.size()){
					cara_aux._0=vertices.size()-1;
					cara_aux._1=(i+perfil.size()-1)%(vertices.size()-1); // (i+perfil.size())%(vertices.size()-1)
					cara_aux._2=i-1;
					caras.push_back(cara_aux);
				}

				// Introduzco la cara restante
				cara_aux._0=perfil.size()-1+perfil.size()*(num-1);
				cara_aux._1=vertices.size()-1;
				cara_aux._2=perfil.size()-1;
				caras.push_back(cara_aux);
			}
		}else{ // Caso sin tapas
			// Nada
		}

	 // tapa inferior
	 /*if (fabs(perfil[0].x)>0.0 && tapa==1)
	  {
	  }

	 // tapa superior
	 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
	  {
	  }*/
}

/****************************************************************************/
// Práctica 2
/****************************************************************************/

// Cilindro
_cilindro::_cilindro(){
	_rotacion();
}

// Práctica 2
void _cilindro::dibujarCilindro(int tapas){
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

	parametros(perfil_cilindro, 16, tapas, 0);
}

// Práctica 3
void _cilindro::dibujarCilindroPerfil(vector<_vertex3f> perfil_cilindro, int rotaciones, int tapas){
	parametros(perfil_cilindro, rotaciones, tapas, 0);
}

// Esfera
_esfera::_esfera(){
	_rotacion();
}

// Práctica 2
void _esfera::dibujarEsfera(int tapas){
	vector<_vertex3f> perfil_esfera;
	_vertex3f aux_esfera;
	for(int i=9; i>0; i--){
			aux_esfera.x=cos(M_PI*i/10-M_PI/2.0);
			aux_esfera.y=sin(M_PI*i/10-M_PI/2.0);
			aux_esfera.z=0.0;
			perfil_esfera.push_back(aux_esfera);
	}

	/*aux_esfera.x=0.0; aux_esfera.y=1.0; aux_esfera.z=0.0;
  perfil_esfera.push_back(aux_esfera);
	aux_esfera.x=0.0; aux_esfera.y=-1.0; aux_esfera.z=0.0;
	perfil_esfera.push_back(aux_esfera);*/

	parametros(perfil_esfera, 16, tapas, sin(M_PI*0/10-M_PI/2.0));
	calcular_normales_vertices_esfera();
}

// Práctica 3
void _esfera::dibujarEsferaPerfil(vector<_vertex3f> perfi_esfera, int rotaciones, int tapas, float hesf){
	parametros(perfi_esfera, rotaciones, tapas, hesf);
}

/****************************************************************************/
// Práctica 3
/****************************************************************************/

// Chistera
_chistera::_chistera(){
	giroCte=0.0;

	// Perfil para la copa
	vector<_vertex3f> perfilCopa;
	_vertex3f auxCopa;
	auxCopa.x=0.35;auxCopa.y=0.6;auxCopa.z=0.0;
	perfilCopa.push_back(auxCopa);
	auxCopa.x=0.35;auxCopa.y=0.0;auxCopa.z=0.0;
	perfilCopa.push_back(auxCopa);
	copa.dibujarCilindroPerfil(perfilCopa,16,2);

	// Perfil para la base
	vector<_vertex3f> perfilBase;
	_vertex3f auxBase;
	auxBase.x=0.5;auxBase.y=0.1;auxBase.z=0.0;
	perfilBase.push_back(auxBase);
	auxBase.x=0.5;auxBase.y=0.0;auxBase.z=0.0;
	perfilBase.push_back(auxBase);
	base.dibujarCilindroPerfil(perfilBase,16,2);

	base.ambiente_difusa=_vertex4f(0.01f, 0.01f, 0.01f, 1.0f);
	base.especular=_vertex4f(0.50f, 0.50f, 0.50f, 1.0f);
	base.brillo=50;
	copa.ambiente_difusa=_vertex4f(0.01f, 0.01f, 0.01f, 1.0f);
	copa.especular=_vertex4f(0.50f, 0.50f, 0.50f, 1.0f);
	copa.brillo=50;
}

void _chistera::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	  // Copa
		glPushMatrix();
			glTranslatef(0.0,1.3,0.0);
			glRotatef(giroCte/2,0,1,0);
			copa.draw(modo, r2, g2, b2, 0.6, 0.6, 0.6, grosor);
		glPopMatrix();

		// Base
		glPushMatrix();
			glTranslatef(0.0,1.26,0.0);
			glRotatef(giroCte/2,0,1,0);
			base.draw(modo, r2, g2, b2, 0.6, 0.6, 0.6, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Cabeza
_cabeza::_cabeza(){
	// Perfil de la esfera de la cabeza
	vector<_vertex3f> perfilCabeza;
	_vertex3f auxCabeza;
	for(int i=9; i>0; i--){
			auxCabeza.x=cos(M_PI*i/10-M_PI/2.0)/2;
			auxCabeza.y=sin(M_PI*i/10-M_PI/2.0)/2;
			auxCabeza.z=0.0;
			perfilCabeza.push_back(auxCabeza);
	}
	cab.dibujarEsferaPerfil(perfilCabeza, 16, 0, sin(M_PI*0/10-M_PI/2.0)/2);

	cab.ambiente_difusa=_vertex4f(0.5f,0.0f,0.0f,1.0f);
	cab.especular=_vertex4f(0.7f,0.6f,0.6f,1.0f);
	cab.brillo=50;
}

void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
		glTranslatef(0.0,0.8,0.0);
		cab.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
	glPopMatrix();
}

// Cuerpo
_cuerpo::_cuerpo(){
	// Perfil para el cuello
	vector<_vertex3f> perfilTronco;
	_vertex3f auxTronco;
	auxTronco.x=0.5;auxTronco.y=1.44;auxTronco.z=0.0;
	perfilTronco.push_back(auxTronco);
	auxTronco.x=0.5;auxTronco.y=0;auxTronco.z=0.0;
	perfilTronco.push_back(auxTronco);
	tronco.dibujarCilindroPerfil(perfilTronco,16,2);

	// Perfil para el cuello
	vector<_vertex3f> perfilCuello;
	_vertex3f auxCuello;
	auxCuello.x=0.2;auxCuello.y=0.1;auxCuello.z=0.0;
	perfilCuello.push_back(auxCuello);
	auxCuello.x=0.2;auxCuello.y=0;auxCuello.z=0.0;
	perfilCuello.push_back(auxCuello);
	cuello.dibujarCilindroPerfil(perfilCuello,16,2);

	tronco.ambiente_difusa=_vertex4f(0.0f,0.50980392f,0.50980392f,1.0f);
	tronco.especular=_vertex4f(0.50196078f,0.50196078f,0.50196078f,1.0f);
	tronco.brillo=50;
	cuello.ambiente_difusa=_vertex4f(0.0f,0.50980392f,0.50980392f,1.0f);
	cuello.especular=_vertex4f(0.50196078f,0.50196078f,0.50196078f,1.0f);
	cuello.brillo=50;
}

void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	  // Tronco
		glPushMatrix();
			glTranslatef(0.0,-1.2,0.0);
			tronco.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor); // DarkSlateBlue
		glPopMatrix();

		// Cuello
		glPushMatrix();
			glTranslatef(0.0,0.24,0.0);
			cuello.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Brazos
_brazos::_brazos(){
	giroBrazo=2.0;
	giroBMin=-50;
	giroBMax=30;

	// Perfil para los antebrazos + muñecas + biceps
	vector<_vertex3f> perfilAMB;
	_vertex3f auxAMB;
	auxAMB.x=0.1;auxAMB.y=0.5;auxAMB.z=0.0;
	perfilAMB.push_back(auxAMB);
	auxAMB.x=0.1;auxAMB.y=0.0;auxAMB.z=0.0;
	perfilAMB.push_back(auxAMB);
	br1.dibujarCilindroPerfil(perfilAMB,15,2);
	br2.dibujarCilindroPerfil(perfilAMB,15,2);
	biceps1.dibujarCilindroPerfil(perfilAMB,15,2);
	biceps2.dibujarCilindroPerfil(perfilAMB,15,2);

	// Perfil para los codos, hombros y manos
	vector<_vertex3f> perfilCHM;
	_vertex3f auxCHM;
	for(int i=9; i>0; i--){
			auxCHM.x=cos(M_PI*i/10-M_PI/2.0)/7;
			auxCHM.y=sin(M_PI*i/10-M_PI/2.0)/7;
			auxCHM.z=0.0;
			perfilCHM.push_back(auxCHM);
	}
	codo1.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
	hombro1.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
	mano1.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
	codo2.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
	hombro2.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
	mano2.dibujarEsferaPerfil(perfilCHM, 16, 0, sin(M_PI*0/10-M_PI/2.0)/7);
}

void _brazos::brazo1(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
		// Antebrazos + Muñecas
		glPushMatrix();
			glTranslatef(0.78,-0.6,0.0);
			glRotatef(-45.0+180,1,0,0);
			glRotatef(giroBrazo,1,0,0);
			br1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
			// Mano 1
			glTranslatef(0.0,0.6,0.0);
			mano1.draw(modo, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, grosor);
		glPopMatrix();

		// Codos
		glPushMatrix();
			glTranslatef(0.78,-0.6,0.0);
			glRotatef(giroBrazo,1,0,0);
			codo1.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();

		// Biceps
		glPushMatrix();
			glTranslatef(0.75,-0.53,0.0);
			glRotatef(20.0,0,0,1);
			biceps1.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();

		// Hombros
		glPushMatrix();
			glTranslatef(0.55,0.0,0.0);
			hombro1.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();
	glPopMatrix();
}

void _brazos::brazo2(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	// Antebrazos + Muñecas
		glPushMatrix();
			glTranslatef(-0.78,-0.6,0.0);
			glRotatef(-45.0+180,1,0,0);
			br2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();

		// Codos
		glPushMatrix();
			glTranslatef(-0.78,-0.6,0.0);
			codo2.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();

		// Biceps
		glPushMatrix();
			glTranslatef(-0.75,-0.53,0.0);
			glRotatef(-20.0,0,0,1);
			biceps2.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();

		// Hombros
		glPushMatrix();
			glTranslatef(-0.55,0.0,0.0);
			hombro2.draw(modo, 0.419608, 0.137255, 0.556863, 1.0, 1.0, 0.0, grosor);
		glPopMatrix();

		// Mano 2
		glPushMatrix();
			glTranslatef(-0.78,-1.0,0.4);
			mano2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Varita
_varita::_varita(){
	// Perfil para los extremos de la varita
	vector<_vertex3f> perfilEV;
	_vertex3f auxEV;
	auxEV.x=0.05;auxEV.y=0.15;auxEV.z=0.0;
	perfilEV.push_back(auxEV);
	auxEV.x=0.05;auxEV.y=0.0;auxEV.z=0.0;
	perfilEV.push_back(auxEV);
	c1.dibujarCilindroPerfil(perfilEV,6,2);
	c3.dibujarCilindroPerfil(perfilEV,6,2);

	// Perfil para el tronco de la varita
	vector<_vertex3f> perfilVar;
	_vertex3f auxVar;
	auxVar.x=0.05;auxVar.y=0.5;auxVar.z=0.0;
	perfilVar.push_back(auxVar);
	auxVar.x=0.05;auxVar.y=0.0;auxVar.z=0.0;
	perfilVar.push_back(auxVar);
	c2.dibujarCilindroPerfil(perfilVar,6,2);

	c2.ambiente_difusa=_vertex4f(0.01f, 0.01f, 0.01f, 1.0f);
	c2.especular=_vertex4f(0.50f, 0.50f, 0.50f, 1.0f);
	c2.brillo=50;
	c1.ambiente_difusa=_vertex4f(1.0f, 0.829f, 0.829f, 0.922f);
	c1.especular=_vertex4f(0.296648f, 0.296648f, 0.296648f, 0.922f);
	c1.brillo=50;
	c3.ambiente_difusa=_vertex4f(1.0f, 0.829f, 0.829f, 0.922f);
	c3.especular=_vertex4f(0.296648f, 0.296648f, 0.296648f, 0.922f);
	c3.brillo=50;
}

void _varita::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
		// Extremo 1
		glPushMatrix();
			glTranslatef(-0.78,0.65,0.4);
			c1.draw(modo, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0, grosor);
		glPopMatrix();

		// Extremo 2
		glPushMatrix();
			glTranslatef(-0.78,0.0,0.4);
			c3.draw(modo, 0.0, 0.5, 1.0, 0.0, 0.5, 1.0, grosor);
		glPopMatrix();

		// Tronco
		glPushMatrix();
			glTranslatef(-0.78,0.15,0.4);
			c2.draw(modo, r1, g1, b1, r1, g1, b1, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Brillo
_brillo::_brillo(){
	// Perfil de la esfera de la cabeza
	vector<_vertex3f> perfilBrillo;
	_vertex3f auxBrillo;
	for(int i=9; i>0; i--){
			auxBrillo.x=cos(M_PI*i/10-M_PI/2.0)/15;
			auxBrillo.y=sin(M_PI*i/10-M_PI/2.0)/15;
			auxBrillo.z=0.0;
			perfilBrillo.push_back(auxBrillo);
	}
	e1.dibujarEsferaPerfil(perfilBrillo, 16, 0, sin(M_PI*0/10-M_PI/2.0)/15);
	e2.dibujarEsferaPerfil(perfilBrillo, 16, 0, sin(M_PI*0/10-M_PI/2.0)/15);
	e3.dibujarEsferaPerfil(perfilBrillo, 16, 0, sin(M_PI*0/10-M_PI/2.0)/15);
	e4.dibujarEsferaPerfil(perfilBrillo, 16, 0, sin(M_PI*0/10-M_PI/2.0)/15);
	e5.dibujarEsferaPerfil(perfilBrillo, 16, 0, sin(M_PI*0/10-M_PI/2.0)/15);

	e1.ambiente_difusa=_vertex4f(0.75164f, 0.60648f, 0.22648f, 1.0f); e1.especular=_vertex4f(0.628281f, 0.555802f, 0.366065f, 1.0f); e1.brillo=50;
	e2.ambiente_difusa=_vertex4f(0.75164f, 0.60648f, 0.22648f, 1.0f); e2.especular=_vertex4f(0.628281f, 0.555802f, 0.366065f, 1.0f); e2.brillo=50;
	e3.ambiente_difusa=_vertex4f(0.75164f, 0.60648f, 0.22648f, 1.0f); e3.especular=_vertex4f(0.628281f, 0.555802f, 0.366065f, 1.0f); e3.brillo=50;
	e4.ambiente_difusa=_vertex4f(0.75164f, 0.60648f, 0.22648f, 1.0f); e4.especular=_vertex4f(0.628281f, 0.555802f, 0.366065f, 1.0f); e4.brillo=50;
	e5.ambiente_difusa=_vertex4f(0.75164f, 0.60648f, 0.22648f, 1.0f); e5.especular=_vertex4f(0.628281f, 0.555802f, 0.366065f, 1.0f); e5.brillo=50;
}

void _brillo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.0,1.0,1.3); e1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0,1.0,1.0); e2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0,-1.0,1.0); e3.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0,-1.0,-1.3); e4.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0,1.0,-1.0); e5.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Piernas
_piernas::_piernas(){
	// Perfil para los muslos + tobillos
	vector<_vertex3f> perfilMT;
	_vertex3f auxMT;
	auxMT.x=0.17;auxMT.y=1.3;auxMT.z=0.0;
	perfilMT.push_back(auxMT);
	auxMT.x=0.17;auxMT.y=0.0;auxMT.z=0.0;
	perfilMT.push_back(auxMT);
	muslo1.dibujarCilindroPerfil(perfilMT,15,2);
	muslo2.dibujarCilindroPerfil(perfilMT,15,2);
}

void _piernas::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
	  // Piernas
		glPushMatrix();
			glTranslatef(-0.25,-2.5,0.0);
			muslo1.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0.25,-2.5,0.0);
			muslo2.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();

		// Pies
			glScalef(0.2,0.18,0.5);
		glPushMatrix();
			glTranslatef(-1.5,-14.45,0.3);
			pie1.draw(modo, r1, g1, b1, r1, g1, b1, grosor);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.5,-14.45,0.3);
			pie2.draw(modo, r1, g1, b1, r1, g1, b1, grosor);
		glPopMatrix();
	glPopMatrix();
}

// Mago
_mago::_mago(){
	giroB1=2.0;
	giroB2=2.0;
	giroMax=20;
	giroMin=-50;
	giroChistera=0.0;
	giroBrillo=0.0;
	giroCC=0.0;
	giroMaxCC=20;
	giroMinCC=-20;
	giroBCte=0.0;
}

void _mago::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){
	glPushMatrix();
		// Cabeza
		glPushMatrix();
			glRotatef(giroCC,0,1,0);
			cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();

		// Chistera
		glPushMatrix();
			glTranslatef(0.0,-0.057,0.0);
			glRotatef(giroChistera,0,1,0);
			glRotatef(giroCC,0,1,0);
			chistera.draw(modo, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, grosor);
		glPopMatrix();

		// Cuerpo
		glPushMatrix();
			cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();

		// Brazos y Varita
		glPushMatrix();
			glRotatef(giroB1,1,0,0);
			brazos.brazo1(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
		glPushMatrix();
			glRotatef(giroB2,1,0,0);
			brazos.brazo2(modo, r1, g1, b1, r2, g2, b2, grosor);
			glTranslatef(0.0,-0.65,0.32);
			glRotatef(60,1,0,0);
			varita.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();

		// Brillo
		glPushMatrix();
			glRotatef(giroBrillo,0,1,0);
			glRotatef(-giroBCte/2,0,1,0);
			brillo.draw(modo, 0.8, 0.498039, 0.196078, 1.0, 1.0, 0.0, grosor); // Gold
		glPopMatrix();

		// Piernas
		glPushMatrix();
			piernas.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
		glPopMatrix();
	glPopMatrix();
}

/****************************************************************************/
// Práctica 4
/****************************************************************************/

// Iluminación plana
void _triangulos3D::draw_iluminacion_plana( ){
	int i;
	if (b_normales_caras==false) calcular_normales_caras();

	glEnable (GL_LIGHTING);
	glShadeModel(GL_FLAT); // GL_SMOOTH
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i=0;i<caras.size();i++){
		glNormal3fv((GLfloat *) &normales_caras[i]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();

	glDisable(GL_LIGHTING);
}

// Cálculo de las normales de las caras
void _triangulos3D::calcular_normales_caras(){
	_vertex3f a1, a2, n;
	normales_caras.resize(caras.size());

	for(int i=0; i<caras.size(); i++){
		// Obtener dos vectores en el triángulo y calcular el producto vectorial
		a1=vertices[caras[i]._1]-vertices[caras[i]._0];
	  a2=vertices[caras[i]._2]-vertices[caras[i]._0];
		n=a1.cross_product(a2);

		// Módulo
		float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);

	  // Normalización
	  normales_caras[i]=_vertex3f(n.x/m, n.y/m, n.z/m);
	}

	b_normales_caras=true;
}

// ------Práctica------ //

// Cálculo de las normales de los vértices
void _triangulos3D::calcular_normales_vertices(){
	_vertex3f n, n_orig;
	n_orig=n;
	normales_vertices.resize(vertices.size());

	if (b_normales_caras==false) calcular_normales_caras();

	for(int i=0; i<vertices.size(); i++){
		for(int j=0; j<caras.size(); j++){
			if(caras[j]._0==i || caras[j]._1==i || caras[j]._2==i){
				// Sumatoria de normales
				n+=normales_caras[j];
			}
		}
		// Media
		// n=n/(normales_caras.size()-1);

		// Módulo
		// float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);

		// Normalización
		normales_vertices[i]=_vertex3f(n.x/*/m*/, n.y/*/m*/, n.z/*/m*/);

		n=n_orig;
	}

	b_normales_vertices=true;
}

// Iluminación suave
void _triangulos3D::draw_iluminacion_suave(){
	int i;
	if (b_normales_vertices==false) calcular_normales_vertices();

	glEnable (GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);

	for (i=0;i<caras.size();i++){
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	  glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}

	glEnd();

	glDisable(GL_LIGHTING);
}

// Esfera - Práctica 4

// Normales de los vértices
void _triangulos3D::calcular_normales_vertices_esfera(){
	_vertex3f n;
	normales_vertices.resize(vertices.size());

	for(int i=0; i<vertices.size(); i++){
		n=vertices[i];
		normales_vertices[i]=_vertex3f(n.x, n.y, n.z);
	}

	b_normales_vertices=true;
}
