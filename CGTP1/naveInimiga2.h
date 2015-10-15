#include "naveGenerica.h"
using namespace std;

#pragma once
class naveInimiga2 : public naveGenerica
{
protected:
	
	float pontosT[18][2];	// Matriz de pontos que definem todos os triângulos do modelo.
	GLfloat corT[6][3];		// Matriz de pontos que definem as cores dos triângulos do modelo.
	float pontosR[8][2];	// Matriz de pontos que definem todos os quadriláteros do modelo.
	GLfloat corR[2][3];		// Matriz de pontos que definem as cores dos quadriláteros do modelo.

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
	// Método que lê o arquivo do modelo.
	void carregaMatrizes(string filePath){
		readFileVertices(filePath, pontosT, corT, pontosR, corR);
	}
	// Chama o método genérico de desenhar
	void desenha(){
		desenhaGenerico(pontosT, corT, pontosR, corR);
	}
};