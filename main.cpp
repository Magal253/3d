//*****************************************************
// Magy2
// Exemplo3DPiramide.cpp
// Um programa OpenGL que abre uma janela GLUT e desenha
// o wireframe de uma pir�mide.
//
// Navega��o via bot�es do mouse + movimento:
// - bot�o esquerdo: rotaciona objeto
// - bot�o direito:  aproxima/afasta
// - bot�o do meio:  translada objeto
//
// Teclas Home e End fazem zoom in/zoom out
//
// Marcelo Cohen e Isabel H. Manssour
// Este c�digo acompanha o livro
// "OpenGL - Uma Abordagem Pr�tica e Objetiva"
//
//*****************************************************

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Vari�veis para controles de navega��o
GLfloat angle, fAspect, angy = 0, angz = 0;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini = 50,y_ini,bot;
int coliG[] = {0    ,45     ,90     ,135    ,180    ,225    ,270    ,315    };
int coliY[] = {11.25,56.25  ,101.25 ,146.25 ,191.25 ,236.25 ,281.25 ,326.25 };
int coliR[] = {22.5 ,47.5   ,112.5  ,157.5  ,202.5  ,247.5  ,292.5  ,337.5  };
int coliP[] = {33.75,78.75  ,123.75 ,168.75 ,213.75 ,258.75 ,303.75 ,348.75 };

// Define um v�rtice
struct VERT{
	float x,y,z;	// posi��o no espa�o
};

// Define uma face
struct FACE{
	int total;	// total de v�rtices
	int ind[5];	// �ndices para o vetor de v�rtices
};

// Define um objeto 3D
struct OBJ{
	VERT *vertices;		// aponta para os v�rtices
	FACE *faces;		// aponta para as faces
	int total_faces;	// total de faces no objeto
};

// Defini��o dos v�rtices
VERT vertices[] = {
	{ 0, 10, 0},	// 0 canto inf esquerdo tras.
	{ -10, 10, 0},	// 1 canfo inf direito  tras.
	{ -10, -10, 0},	// 2 canto inf direito  diant.
	{ 10, -10, 0},  // 3 canto inf esquerdo diant.
	{ 10, 0, 0},  // 4 topo
};

// Defini��o das faces
FACE faces[] = {
	{ 5, { 0,1,2,3,4 }}	// lado dianteiro
};

// Finalmente, define o objeto pir�mide
OBJ placa = {
	vertices, faces, 1
};

// Desenha um objeto em wireframe
void DesenhaObjetoWireframe(OBJ *objeto)
{

	// Percorre todas as faces
	for(int f=0; f < objeto->total_faces; f++)
	{
		glBegin(GL_POLYGON);
		// Percorre todos os v�rtices da face
		for(int v=0; v < objeto->faces[f].total; v++)
			glVertex3f(objeto->vertices[objeto->faces[f].ind[v]].x,
				       objeto->vertices[objeto->faces[f].ind[v]].y,
				       objeto->vertices[objeto->faces[f].ind[v]].z);
		glEnd();
	}
}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Altera a cor do desenho para preto


    //glutWireCube(30);
    //glutWireTeapot(30);
    //glutWireCone(10,30, 50, 50);
    //glutWireSphere(5,35,35);

    angy+= 0.075;
    glPushMatrix();
        glPushMatrix();
            glRotatef(angy, 0, 1, 0);
            glRotatef(90, 1, 0, 0);  // Y virou Z e Z virou Y
            glColor3f(0.0f, 0.0f, 1.0f);
            glutSolidTorus(20, 500, 20, 400);
            glColor3f(0.0f, 0.0f, 0.0f);
            glutWireTorus(19.80, 500, 20, 100);
            glPushMatrix();
                for(float i = 0; i < 360 ; i+=45){
                    glPushMatrix();
                        glRotatef(i , 0, 0, 1);
                        glTranslatef(-510, 0, -10);  ///objetos com o centro situado do lado superior esquerdo da tela VERDE
                        glPushMatrix();
                            //glScalef(1, 0.01, 1);
                            glColor3f(0, 1, 0);
                            //glutSolidCube(20);
                            glRotatef(90,1,0,0);
                            DesenhaObjetoWireframe(&placa);

                        glPopMatrix();
                    glPopMatrix();
                }
                for(float i = 11.25; i < 371.25 ; i+=45){
                    glPushMatrix();
                        glRotatef(i , 0, 0, 1);
                        glTranslatef(-510, 0, 10);  ///objetos com o centro situado do lado inferior esquerdo da tela AMARELO
                        glPushMatrix();
                            glColor3f(1, 1, 0);
                            glRotatef(-90,1,0,0);
                            DesenhaObjetoWireframe(&placa);
                        glPopMatrix();
                    glPopMatrix();
                }
                for(float i = 22.5; i < 382.5 ; i+=45){
                    glPushMatrix();
                        glRotatef(i , 0, 0, 1);
                        glTranslatef(-490, 0, 10);  ///objetos com o centro situado do lado inferior direito da tela VERMELHO
                        glPushMatrix();
                            glColor3f(1, 0, 0);
                            glRotatef(-90,1,0,0);
                            glRotatef(90,0,0,1);
                            DesenhaObjetoWireframe(&placa);
                        glPopMatrix();
                    glPopMatrix();
                }
                for(float i = 33.75; i < 393.75 ; i+=45){
                    glPushMatrix();
                        glRotatef(i , 0, 0, 1);
                        glTranslatef(-490, 0, -10);  ///objetos com o centro situado do lado superior direito da tela ROXO
                        glPushMatrix();
                            glColor3f(1, 0, 1);
                            glRotatef(90,1,0,0);
                            glRotatef(90,0,0,1);
                            DesenhaObjetoWireframe(&placa);
                        glPopMatrix();
                    glPopMatrix();
                }
            glPopMatrix();
        glPopMatrix();
        glRotatef(angy, 0.0f, 1.0f, 0.0f);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-500, 0, 0);
        glRotatef(angz, 0.0f, 0.0f, 1.0f);
            glPushMatrix();
                glTranslatef(0,-21,-20);
                glColor3f(0,0,0);
                glutSolidCube(7);
                glColor3f(1,1,1);
                glutWireCube(7.1);
            glPopMatrix();
    glPopMatrix();


    ///glPointSize(2);
    ///glBegin(GL_POINTS);
    ///    glColor3f(1,1,1);
    ///    glVertex3f(-496.5 , -19.6, -21);
    ///    glVertex3f(-503.5 , -19.6, -21);
    ///glEnd();
    /// +/- 3.5 em X

    //glPushMatrix();
    //glPopMatrix();



    //glutWireTetrahedron();
    //glutWireOctahedron();
    //glutWireDodecahedron();
    //glutWireIcosahedron();

    if(angy >= 360){
        angy = 0;
    }



    //Desenha o objeto definido anteriormente: uma pir�mide
	//DesenhaObjetoWireframe(&piramide);

    glutPostRedisplay();
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX+500,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);


	//gluLookAt(500,0,0,500,0,10,0,1,0);
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.1,5200);

	PosicionaObservador();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
	{
		// Libera mem�ria e finaliza programa
		exit(0);
	}
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)
{
	switch (tecla)
	{
		case GLUT_KEY_HOME: 	if(angle>=10)  angle -=5;
                                break;
		case GLUT_KEY_END:	    if(angle<=150) angle +=5;
                                break;
        case GLUT_KEY_LEFT:	    angz -=2;
                                if(angz < 0) angz = 360;
                                break;
        case GLUT_KEY_RIGHT:	angz +=2;
                                if(angz >= 360) angz = 0;
                                break;
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}
/*
// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}
*/


// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	10.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0

/*
void GerenciaMovim(int x, int y)
{
	// Bot�o esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica �ngulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Bot�o direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
		// Calcula diferen�a
		int deltaz = y_ini - y;
		// E modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Bot�o do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posi��es
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}
*/

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle=60;

	// Inicializa as vari�veis usadas para alterar a posi��o do
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 20;
	glEnable(GL_DEPTH_TEST);
}
/*
void Anima(int value)
{
	// Muda o angulo de rota��o, e se chegar a 360, passa para zero

        angy++;

	if( angy >= 360.0 )
	    angy = 0.0f;

    // Redesenha o "teapot" em outra posi��o
	glutPostRedisplay();
	glutTimerFunc(41,Anima, 1);
}
*/
// Programa Principal
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5,5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho do wireframe de uma pir�mide");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	//glutTimerFunc(41,Anima, 1);

	// Registra a fun��o callback para eventos de bot�es do mouse
	//glutMouseFunc(GerenciaMouse);

	// Registra a fun��o callback para eventos de movimento do mouse
	//glutMotionFunc(GerenciaMovim);

	// Registra a fun��o callback para tratamento das teclas normais
	glutKeyboardFunc (Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);

	// Chama a fun��o respons�vel por fazer as inicializa��es
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}
