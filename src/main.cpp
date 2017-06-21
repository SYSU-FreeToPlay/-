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
#include "..\include\Camera.h"

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

Camera *camera = new Camera();

// ����
extern GLuint wallTextureID, groundTexureID;
extern GLuint skyBoxTetureID[5];
// ��ʾ�б�
extern GLuint wallList, groundList, skyBoxList;
// �Թ�
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("OpenGL");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// ��������
	loadTexture("../Texture/wall.png", wallTextureID);
	loadTexture("../Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	// ���ö�ά����
	glEnable(GL_TEXTURE_2D);

	generateDisplayList();

	// ����ͶӰ
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

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	// ͨ�������ʵ�ֵ�һ�˳�����
	camera->setCamera();

	// ������պ�
	glDisable(GL_LIGHTING);
	glPushMatrix();
	// ʹ��պ���eye��Ծ�ֹ
	camera->moveSkyBox();
	glCallList(skyBoxList);
	glPopMatrix();
	// ���Ƶ���
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glCallList(groundList);
	glPopMatrix();

	// �����Թ�
	glPushMatrix();
	glCallList(wallList);
	glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
}

void motion(int x, int y)
{
	// ͨ�������ʵ�ֵ�һ�˳�����
	camera->moveMouse(x, y);
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		camera->moveW();
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		camera->moveS();
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		camera->moveA();
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		camera->moveD();
		glutPostRedisplay();
		break;
	default:break;
	}
	return;
}

void upSpecialKeyboard(int key, int x, int y)
{
}

void idle()
{
}
