#include "naveGenerica.h"
using namespace std;


class navePrincipal : public naveGenerica
{
private:
	int vidas;				// Define a quantidade de vidas do jogador.
	float stepX;		// Acr�scimo no atributo xc quando a nave se movimento no eixo x.
	float stepY;		// Acr�scimo no atributo yc quando a nave se movimento no eixo y.
	float pontosT[21][2];	// Matriz de pontos que definem todos os tri�ngulos do modelo.
	GLfloat corT[7][3];		// Matriz de pontos que definem as cores dos tri�ngulos do modelo.
	float pontosR[12][2];	// Matriz de pontos que definem todos os quadril�teros do modelo.
	GLfloat corR[3][3];		// Matriz de pontos que definem as cores dos quadril�teros do modelo.
	
public:
	navePrincipal(){}
	// Construtor da classe
	navePrincipal(string filePath) : naveGenerica(){
		stepX = 0.2f;
		stepY = 0.2f;

		xc = 0;
		yc = 5;
		vidas = 5;
		carregaMatrizes(filePath);
	}
	// Construtor da classe com passagem de par�metro
	// x = xc, y = yc, b = boundingBox, h = HP, v = vidas, filePath = Caminho do arquivo
	navePrincipal(float x, float y, float b, int h, int v, string filePath) : naveGenerica(){
		xc = x;
		yc = y;
		boundingBox = b;
		HP = h;
		vidas = v;
		carregaMatrizes(filePath);
		
	}
	// M�todo set do atributo vidas.
	void setVidas(int v){
		vidas = v;
	}
	// M�todo get do atributo vidas.
	int getVidas(){
		return vidas;
	}
	
	// M�todo que l� o arquivo do modelo.
	void carregaMatrizes(string filePath){
		readFileVertices(filePath, pontosT, corT, pontosR, corR);
	}
	// Chama o m�todo gen�rico de desenhar
	void desenha(){
		desenhaGenerico(pontosT, corT, pontosR, corR);
	}
	void movimentaNave(int k, GLfloat telaX, GLfloat telaY){
		switch (k)
		{
		case GLUT_KEY_UP:
			yc += stepY;
			break;
		case GLUT_KEY_DOWN:
			yc -= stepY;
			break;
		case GLUT_KEY_LEFT:
			xc -= stepX;
			break;
		case GLUT_KEY_RIGHT:
			xc += stepX;
			break;
		}
		setCoord(xc, yc);
		colisaoTela(telaX, telaY);
		glutPostRedisplay();
	}
};