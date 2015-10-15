#include <math.h>
#include "naveGenerica.h"
#include "navePrincipal.h"
#include "naveinimiga1.h"
#include "naveinimiga2.h"
#include "naveinimiga3.h"
using namespace std;

const string caminhoNP = "modelos/navePrincipal.txt";
const string caminhoNI1 = "modelos/naveInimiga1.txt";
const string caminhoNI2 = "modelos/naveInimiga2.txt";
const string caminhoNI3 = "modelos/naveInimiga3.txt";

class principal {
protected:
	navePrincipal np;			// Nave Principal
	naveInimiga1 ni1;			// Inimigo 1
	naveInimiga2 ni2;			// Inimigo 2
	naveInimiga3 ni3;			// Inimigo 3
	GLfloat telaX;		// Valor máximo atingido pela coordenada x. O valor mínimo é 0.
	GLfloat telaY;		// Valor máximo atingido pela coordenada x. O valor mínimo é 0.
	GLfloat stepX;		// Acréscimo no atributo xc quando a nave se movimento no eixo x.
	GLfloat stepY;		// Acréscimo no atributo yc quando a nave se movimento no eixo y.
	int windowWidth;		// Largura da tela
	int windowHeight;		// Altura da tela
	bool fullscreenON;	// Indica se o fullscreen está ou não ativado
	bool anima;			// Indica se haverá ou não animação
	
	
	//bool keyStates[256] = { false };	//
	//GLfloat cor[3] = { 0.3f, 0.6f, 0.3f };
	//GLfloat modCor = -0.1f;
public:
	principal()
	{
		telaX = 15.0f;
		telaY = 15.0f;
		stepX = 0.1f;
		stepY = 0.1f;
		windowWidth = 800;
		windowHeight = 600;
		fullscreenON = false;
		anima = false;
		navePrincipal n(caminhoNP);
		naveInimiga1 ini(caminhoNI1);
		naveInimiga2 ini2(caminhoNI2);

		naveInimiga3 ini2(caminhoNI3);

		np = n;
		ni1 = ini;
		ni2 = ini2;

	}
	void pressionarTecla(unsigned char key){
		GLfloat xc = np.getXC();
		GLfloat yc = np.getYC();
		switch (key) {
		case 'W':
		case 'w':
			yc += stepY;
			break;
		case 'S':
		case 's':
			yc -= stepY;
			break;
		case 'A':
		case 'a':
			xc -= stepX;
			break;
		case 'D':
		case 'd':
			xc += stepX;
			break;
		case 'F':
		case 'f':
			if (fullscreenON){
				fullscreenON = false;
				glutReshapeWindow(windowWidth, windowHeight);
			}
			else{
				glutFullScreen();
				fullscreenON = true;
			}
			break;
		case  27:   // ESC
			exit(0);
		case 13: // Enter
			break;
		}
		np.setCoord(xc, yc);
		//np.colisaoTela(telaX,telaY);

		// Redesenha o quadrado com as novas coordenadas 
		glutPostRedisplay();
	}
	void pressionaSetas(int k){
		np.movimentaNave(k, telaX, telaY);
	}
	/* Desenha a função*/
	void desenhaTela()
	{
		glClearColor(0, 0.5, 0.5, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		np.colisaoTela(telaX, telaY);
		np.desenha();
		ni1.desenha();
		ni2.desenha();
		ni3.desenha();

		glutSwapBuffers();
	}
	void remodelarTela(int w, int h){
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, telaX, 0, telaY);
	}
	float func(float x)
	{
		return sin(x);
	}
	void animacaoInicial(){
		GLfloat xc = np.getXC();			//
		GLfloat yc = np.getYC();
		if (xc < telaX - 1 && (!anima)){
			xc += stepX;
			yc += func(xc);
		}
		else
		{
			anima = true;
		}
		np.setCoord(xc, yc);
		//np.colisaoTela(telaX,telaY);
		glutPostRedisplay();
	}
	void iniciaTela(int argc, char **argv){
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowSize(windowWidth, windowHeight);
		glutInitWindowPosition(5, 5);
		glutCreateWindow("Star War");

		
	}
};
principal p;

/* Função */

/* Redrawing func */
void redraw(void)
{
	p.desenhaTela();
};

/* Função chamada enquanto nenhum evento é disparado */
void idle(void)
{
	glutPostRedisplay();
};

/* Key press processing */
void keyboardDown(unsigned char key, int x, int y) {	
	p.pressionarTecla(key);
}
void keyboardSpecialDown(int k, int x, int y) {
	p.pressionaSetas(k);
}


/* Window reashape */
void reshape(int w, int h)
{
	p.remodelarTela(w, h);
};

void Timer(int value)
{	
	p.animacaoInicial();
	glutTimerFunc(33, Timer, 1);
}

void IniciaJogo(int argc, char **argv)
{
	p.iniciaTela(argc, argv);
	// Register GLUT callbacks. 
	glutDisplayFunc(redraw);
	glutKeyboardFunc(keyboardDown);
	glutSpecialFunc(keyboardSpecialDown);
	glutReshapeFunc(reshape);
	glutTimerFunc(33, Timer, 1);
	glutIdleFunc(idle);


	glutMainLoop(); // Main loop 
}