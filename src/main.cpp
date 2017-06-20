#include <GL/freeglut.h>
#include <soil.h>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include "..\include\maze.h"
#include "..\include\texture.h"
#include "..\include\wall.h"
#include "..\include\skyBox.h"
#include "..\include\ground.h"
#include "..\include\displayList.h"

using namespace std;

#define WINDOW_W 400
#define WINDOW_H 400
#define M_PI 3.14159265358979323846
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4


void display();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void specialKeyboard(int key, int x, int y);
void upSpecialKeyboard(int key, int x, int y);
void idle();
void SetupLights();

// ��ײ��⣬δʵ��
bool collision(double x, double y);

// �����ƶ����λ��
bool keyUpPressed = false, keyDownPressed = false, keyLeftPressed = false, keyRightPressed = false;
clock_t start, now;

// ������ת�ӽ�
static int oldmy, oldmx;
double rotateY = 0, rotateX = 0;

// ��¼��ҵ�ǰλ��
double posX = 1, posY = 1;
double backupX = 1, backupY = 1;

// ����
extern GLuint wallTextureID, groundTexureID;
extern GLuint skyBoxTetureID[5];
// ��ʾ�б�
extern GLuint wallList, groundList, skyBoxList;
// �Թ�
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];



int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("OpenGL");

	//// ����
	//float ambientLight[] = { 0.3f, 0.5f, 0.8f, 1.0f };  // ������
	//float diffuseLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  // ɢ���
	//													   //float lightPosition[] = {0.0f, 0.0f, 1.0f, 0.0f};  // ��Դλ��
	//float lightPosition[] = { 0.0f, 1.5f, .0f, 0.0f };  // ��Դλ��
	//													// ���ʱ���
	//float matAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	//float matDiff[] = { 1.0f,1.0f,1.0f,1.0f };
	//glEnable(GL_LIGHTING);      //���ù���
	//							//ΪLIGHT0��������
	//glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	////���ڿ�ʼ��ЭLIGHT0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //���û��������
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //����ɢ������
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //���ù�Դ�ڳ����е�λ��
	//												  //���ù�
	//glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	loadTexture("../Texture/wall.png", wallTextureID);
	loadTexture("../Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    //����������
	glEnable(GL_TEXTURE_2D);                                //���ö�ά����
	generateDisplayList();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1.0, 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(specialKeyboard);
	glutSpecialUpFunc(upSpecialKeyboard);
	glutIdleFunc(idle);
	SetupLights();
	glutMainLoop();

	return 0;
}

//���ù�Դ
void SetupLights() {
    GLfloat light_position[] ={3.0f,3.0f,0.0f,1.0f}; 
    GLfloat ambientLight[]={0.5f,0.5f,0.5f,1.0f};	//��ɫ������  
    GLfloat diffuseLight[]={0.8f,0.8f,0.8f,0.8f};	//��ɫ������  
    GLfloat specularLight[]={1.0f,1.0f,1.0f,1.0f};	//��ɫ�����
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   //���û�����Դ  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);   //�����������Դ  
    glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight); //���þ����Դ  
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);//���õƹ�λ�� 
    glEnable(GL_LIGHT0); //�򿪰�ɫ����Դ
    glEnable(GL_LIGHTING); 
}

void display(void) {
	//cout << posX << " " << posY << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(rotateY, 0, 1, 0);
	//glRotatef(rotateX, 1, 0, 0);

	// ������պ�
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glCallList(skyBoxList);
	glPopMatrix();
	// ���Ƶ���
	glEnable(GL_LIGHTING);
	glPushMatrix();
	//glTranslatef(0, -0.5, 0);
	glTranslatef(0, -0.5, 0);
	//glScalef(10, 10, 10);
	//glTranslatef(-1, 0, -1);
	glTranslatef(-posX, 0, -posY);
	glCallList(groundList);
	glPopMatrix();
	// �����Թ�
	glPushMatrix();
	glTranslatef(-posX, 0, -posY);
	glCallList(wallList);
	glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) { //  ���������
												  //  ��һ����갴��ʱ,��¼����ڴ����еĳ�ʼ����
	if (state == GLUT_DOWN) {
		oldmx = x, oldmy = y;
	}
}

void motion(int x, int y) {  // ��������϶�
	rotateY += (oldmx - x);
	//rotateX += (oldmy - y);

	while (rotateY < 0)
		rotateY += 360;
	while (rotateY >= 360)
		rotateY -= 360;

	oldmx = x;
	oldmy = y;

	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		keyUpPressed = true;
		start = clock();
		break;
	case GLUT_KEY_DOWN:
		keyDownPressed = true;
		start = clock();
		break;
	case GLUT_KEY_LEFT:
		keyLeftPressed = true;
		start = clock();
		break;
	case GLUT_KEY_RIGHT:
		keyRightPressed = true;
		start = clock();
		break;
	default:break;
	}
}

void upSpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		keyUpPressed = false;
		break;
	case GLUT_KEY_DOWN:
		keyDownPressed = false;
		break;
	case GLUT_KEY_LEFT:
		keyLeftPressed = false;
		break;
	case GLUT_KEY_RIGHT:
		keyRightPressed = false;
		break;
	default:break;
	}
	glutPostRedisplay();
}

void idle() {
	if (keyUpPressed || keyDownPressed || keyLeftPressed || keyRightPressed) {
		backupX = posX;
		backupY = posY;
		now = clock();
	}
	// ���ݵ�ǰ�ĽǶȷ�Χ���Լ����µķ��������һ�������ж�Ӧ�ö��������ʲô����
	// �磬�Ƕ�Ϊ-45~45�����������������·�������� ʱ��Ӧ������y�����ֵ
	if (keyUpPressed) {
		if ((rotateY >= 0 && rotateY < 45) || rotateY >= 315) {
			posY -= (double)(now - start) / 1000;
		}
		else if (rotateY >= 45 && rotateY < 135) {
			posX += (double)(now - start) / 1000;
		}
		else if (rotateY >= 135 && rotateY < 225) {
			posY += (double)(now - start) / 1000;
		}
		else if (rotateY >= 225 && rotateY < 315) {
			posX -= (double)(now - start) / 1000;
		}
	}
	else if (keyDownPressed)
	{
		if ((rotateY >= 0 && rotateY < 45) || rotateY >= 315) {
			posY += (double)(now - start) / 1000;
		}
		else if (rotateY >= 45 && rotateY < 135) {
			posX -= (double)(now - start) / 1000;
		}
		else if (rotateY >= 135 && rotateY < 225) {
			posY -= (double)(now - start) / 1000;
		}
		else if (rotateY >= 225 && rotateY < 315) {
			posX += (double)(now - start) / 1000;
		}
	}
	else if (keyRightPressed)
	{
		rotateY += (double)(now - start) / 10;
	}
	else if (keyLeftPressed)
	{
		rotateY -= (double)(now - start) / 10;
	}

	if (keyUpPressed || keyDownPressed || keyLeftPressed || keyRightPressed) {
		if (collision(posX, posY)) {
			posX = backupX;
			posY = backupY;
		}

		while (rotateY < 0)
			rotateY += 360;
		while (rotateY >= 360)
			rotateY -= 360;
		start = now;
		glutPostRedisplay();
	}

}

bool collision(double x, double y) {
	return false;
	//return mazeData[int(y)][int(x)] == 'W';
}
