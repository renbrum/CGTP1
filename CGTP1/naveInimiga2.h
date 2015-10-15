#include "naveGenerica.h"
using namespace std;

#pragma once
class naveInimiga2 : public naveGenerica
{
protected:
	
	float pontosT[18][2];	// Matriz de pontos que definem todos os tri�ngulos do modelo.
	GLfloat corT[6][3];		// Matriz de pontos que definem as cores dos tri�ngulos do modelo.
	float pontosR[8][2];	// Matriz de pontos que definem todos os quadril�teros do modelo.
	GLfloat corR[2][3];		// Matriz de pontos que definem as cores dos quadril�teros do modelo.

	float stepX;		// Incremento utilizado para gerar movimento na coordenada x
	float stepY;		// Incremento utilizado para gerar movimento na coordenada y
public:
	naveInimiga2(){}
	// Construtor da classe
	naveInimiga2(string filePath) : naveGenerica(){
		stepX = 0.1f;
		stepY = 0.1f;
		xc = 5;
		yc = 5;
		carregaMatrizes(filePath);
	}
	// M�todo que l� o arquivo do modelo.
	void carregaMatrizes(string filePath){
		readFileVertices(filePath, pontosT, corT, pontosR, corR);
	}
	// Chama o m�todo gen�rico de desenhar
	void desenha(){
		desenhaGenerico(pontosT, corT, pontosR, corR);
	}
};