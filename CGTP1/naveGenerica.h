#include <gl/glut.h>
#include <fstream>
#include <string>
using namespace std;

#pragma once	/* Evita o erro de vários includes iguais sendo chamados num mesmo arquivo
				na hora de compilar.*/
class naveGenerica
{
protected:
	int HP;				// HP: Health Points. Corresponde a vida do personagem
	float xc, yc;		// Define as coordenadas x e y do centro. Corresponde a coordenada inferior esquerda (0,0)
	float boundingBox;	// Define o tamanho de um lado da bounding box que é quadrada.	
	int ct;			// Quantidade de cores para desenhar triângulos
	int pt;			// Quantidade de pontos para desenhar triângulos
	int cr;			// Quantidade de cores para desenhar quadriláteros
	int pr;			// Quantidade de pontos para desenhar quadriláteros
	static int aux[4];
public:
	// Construtor da classe sem passagem de parâmetro.
	// Define a coordenada de centro como (xc,yc) = (0,0), boundingBox = 1 e HP = 100.
	naveGenerica(){
		ct = 0;
		pt = 0;
		cr = 0;
		pr = 0;
		xc = 0;
		yc = 0;
		boundingBox = 1;
		HP = 100;
	}
	// Construtor da classe com passagem de parâmetro
	// x = xc, y = yc, b = boundingBox e h = HP
	naveGenerica(float x, float y, float b, int h){
		xc = x;
		yc = y;
		boundingBox = b;
		HP = h;
	}
	// Método set do atributo xc. 
	void setXC(float x){
		xc = x;
	}
	// Método get do atributo xc. 
	float getXC(){
		return xc;
	}
	// Método set do atributo yc. 
	void setYC(float y){
		yc = y;
	}
	// Método get do atributo yc. 
	float getYC(){
		return yc;
	}
	// Método mais fácil na hora de modificar as duas coordenadas ao mesmo tempo.
	void setCoord(float x, float y){
		xc = x;
		yc = y;
	}
	// Método set do atributo HP. 
	void setHP(int h){
		HP = h;
	}
	// Método get do atributo HP. 
	int getHP(){
		return HP;
	}

	/*Função que descreve o movimento de uma nave. Recebe como parâmetro uma função que retorna um float.
	Deve ser implementada pelos inimigos. Recebe a cordenada xc como parâmetro e calcula a coordenada yc*/
	void funcaoMovimento(float(*func)(float x)){
		yc = func(xc);
	}
	/*
	Método que lê o arquivo do modelo. Parâmetros: 
	filePath = Caminho do arquivo. Adotaremos o padrão "modelos/nomedoModelo.txt" sendo "modelos/" a pasta com os modelos.
	pontosT[][2] = Matriz de pontos que definem todos os triângulos do modelo.
	corT[][3]	 = Matriz de pontos que definem as cores dos triângulos do modelo.
	pontosR[][2] = Matriz de pontos que definem todos os quadriláteros do modelo.
	corR[][3]	 = Matriz de pontos que definem as cores dos quadriláteros do modelo.
	//*/
	void readFileVertices(string filePath, float pontosT[][2], GLfloat corT[][3], float pontosR[][2], GLfloat corR[][3]){		
		ifstream file(filePath);
		char ch;
		ct = 0; pt = 0; cr = 0; pr = 0;
		while (file >> ch){
			switch (ch)
			{
			case 'u':
				file >> corT[ct][0] >> corT[ct][1] >> corT[ct][2];
				ct++;
				break;
			case 't':
				file >> pontosT[pt][0] >> pontosT[pt][1];
				pt++;
				break;
			case 'd':
				file >> corR[cr][0] >> corR[cr][1] >> corR[cr][2];
				cr++;
				break;
			case 'r':
				file >> pontosR[pr][0] >> pontosR[pr][1];
				pr++;
				break;
			}
		}

	}
	//*/

	/*Lê o arquivo do modelo. Essa versão só desenha quadriláteros. Parâmetros:
	filePath = Caminho do arquivo. Adotaremos o padrão "modelos/nomedoModelo.txt" sendo "modelos/" a pasta com os modelos.
	pontosR[][2] = Matriz de pontos que definem todos os quadriláteros do modelo.
	corR[][3]	 = Matriz de pontos que definem as cores dos quadriláteros do modelo.
	*/
	void readFileVertices(string filePath, float pontosR[][2], GLfloat corR[][3]){
		ifstream file(filePath);
		char ch;
		cr = 0; pr = 0;
		while (file >> ch){
			switch (ch)
			{
			case 'd':
				file >> corR[cr][0] >> corR[cr][1] >> corR[cr][2];
				cr++;
				break;
			case 'r':
				file >> pontosR[pr][0] >> pontosR[pr][1];
				pr++;
				break;
			}
		}

	}
	// Verifica as bordas.  Se a window for menor e o 
	// quadrado sair do volume de visualização 
	void colisaoTela(float telaX, float telaY){
		if (xc > telaX - boundingBox)
			xc = telaX - boundingBox;
		else{
			if (xc <= telaX - boundingBox && xc<0)
				xc = 0;
		}


		if (yc > telaY - boundingBox)
			yc = telaY - boundingBox;
		else{
			if (yc < telaY - boundingBox && yc<0)
				yc = 0;
		}
	}
	/* Método que desenha o modelo usando triângulos e quadriláteros.*/
	void desenhaGenerico(float pontosT[][2], GLfloat corT[][3], float pontosR[][2], GLfloat corR[][3]){
		glPushMatrix();
		int aux = 0;
		glColor3fv(corT[aux]);
		glBegin(GL_TRIANGLES);
		for (int t = 0; t < pt; t++){
			if ((t + 1) % 3 == 0 && aux < ct){
				glColor3fv(corT[aux]);
				aux++;
			}
			glVertex2f(xc + pontosT[t][0]*boundingBox, yc + pontosT[t][1]*boundingBox);
		}
		glEnd();
		aux = 0;
		glColor3fv(corR[aux]);
		glBegin(GL_QUADS);
		for (int r = 0; r < pr; r++){
			if ((r + 1) % 4 == 0 && aux < cr){
				glColor3fv(corR[aux]);
				aux++;
			}
			glVertex2f(xc + pontosR[r][0]*boundingBox, yc + pontosR[r][1]*boundingBox);
		}
		glEnd();

		glPopMatrix();
	}
	//*/


	// Método que desenha o modelo usando quadriláteros.
	void desenhaGenerico(float pontosR[][2], GLfloat corR[][3]){
		glPushMatrix();		

		int aux = 0;
		glColor3fv(corR[aux]);
		glBegin(GL_QUADS);
		for (int r = 0; r < pr; r++){
			if ((r + 1) % 4 == 0 && aux < cr){
				glColor3fv(corR[aux]);
				aux++;
			}
			glVertex2f(xc + pontosR[r][0]*boundingBox, yc + pontosR[r][1]*boundingBox);
		}
		glEnd();

		glPopMatrix();
	}
	
};