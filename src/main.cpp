#include <GL/freeglut.h>
#include <soil.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <time.h>
#include "..\include\maze.h"
#include "..\include\texture.h"
#include "..\include\wall.h"
#include "..\include\skyBox.h"
#include "..\include\ground.h"
#include "..\include\displayList.h"
#include "..\include\Camera.h"
#include "..\include\AssimpLoad.h"

using namespace std;

#define WINDOW_W 600
#define WINDOW_H 600
#define M_PI 3.14159265358979323846
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4


void display();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialKeyboard(int key, int x, int y);
void upSpecialKeyboard(int key, int x, int y);
void idle();
void reshape(int width, int height);

void SetupLights();

void showHelpInfo();

#define FPS false
#define TPS true
bool cameraFlag = FPS;
Camera *camera1 = new Camera();
Camera *camera3 = new Camera();

AssimpLoad model;

bool arriveExit = false;

// ����
GLuint wallTextureID, groundTexureID;
vector<GLuint> skyBoxTetureID(5);
// ��ʾ�б�
GLuint wallList, groundList, skyBoxList;
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

	// ����ģ��
	if (!model.Load("Model/spider.obj"))
	{
		cout << "Failed to load spider.obj" << endl;
		cout << endl;
	}

	// ��������
	loadTexture("Texture/wall.png", wallTextureID);
	loadTexture("Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture(skyBoxTetureID);
	// ���ö�ά����
	glEnable(GL_TEXTURE_2D);

	// ������ʾ�б�
	generateDisplayList(wallList, groundList, skyBoxList);

	// �������
	camera3->setPosition(Vector3(8, 16, 8));
	camera3->setCenter(Vector3(8, 0, 8));
	camera3->setUp(Vector3(0, 0, -1));

	// ����ͶӰ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1.0, 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, WINDOW_W, WINDOW_H);

	// ���ñ�����ɫ
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	// ��ʾ������Ϣ
	showHelpInfo();

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutSpecialUpFunc(upSpecialKeyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
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
	if (cameraFlag == FPS)
	{
		camera1->setCamera();
	}
	else
	{
		camera3->setCamera();
		Vector3 pos = camera1->getPostion();

		glBegin(GL_QUADS);
		glVertex3f(pos.x + 0.2, pos.y, pos.z + 0.2);
		glVertex3f(pos.x + 0.2, pos.y, pos.z - 0.2);
		glVertex3f(pos.x - 0.2, pos.y, pos.z - 0.2);
		glVertex3f(pos.x - 0.2, pos.y, pos.z + 0.2);
		glEnd();
	}
	

	// ������պ�
	glDisable(GL_LIGHTING);
	glPushMatrix();
	// ʹ��պ���eye��Ծ�ֹ
	if (cameraFlag == FPS)
	{
		camera1->moveSkyBox();
	}
	glTranslatef(8, 0, 8);
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

	// ����ģ��
	glPushMatrix();
	glTranslatef(13.5, 0, 16.5);
	glRotatef(-90, 0, 1, 0);
	model.Display();
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
	if (cameraFlag == FPS)
	{
		camera1->moveMouse(x, y);
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case '1':
		cameraFlag = FPS;
		glutPostRedisplay();
		break;

	case '3':
		cameraFlag = TPS;
		glutPostRedisplay();
		break;

	case 'w':
		if (cameraFlag == FPS)
		{
			camera1->moveW();
		}
		glutPostRedisplay();
		break;

	case 'W':
		if (cameraFlag == FPS)
		{
			camera1->moveW();
		}
		glutPostRedisplay();
		break;

	case 's':
		if (cameraFlag == FPS)
		{
			camera1->moveS();
		}
		glutPostRedisplay();
		break;

	case 'S':
		if (cameraFlag == FPS)
		{
			camera1->moveS();
		}
		glutPostRedisplay();
		break;

	case 'a':
		if (cameraFlag == FPS)
		{
			camera1->moveA();
		}
		glutPostRedisplay();
		break;

	case 'A':
		if (cameraFlag == FPS)
		{
			camera1->moveA();
		}
		glutPostRedisplay();
		break;

	case 'd':
		if (cameraFlag == FPS)
		{
			camera1->moveD();
		}
		glutPostRedisplay();
		break;

	case 'D':
		if (cameraFlag == FPS)
		{
			camera1->moveD();
		}
		glutPostRedisplay();
		break;

	default:
		break;

	}
}

void specialKeyboard(int key, int x, int y)
{
	switch (key)
	{

	case GLUT_KEY_UP:
		if (cameraFlag == FPS)
		{
			camera1->moveW();
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:
		if (cameraFlag == FPS)
		{
			camera1->moveS();
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_LEFT:
		if (cameraFlag == FPS)
		{
			camera1->moveA();
		}
		glutPostRedisplay();
		break;

	case GLUT_KEY_RIGHT:
		if (cameraFlag == FPS)
		{
			camera1->moveD();
		}
		glutPostRedisplay();
		break;

	default:
		break;

	}

	return;
}

void upSpecialKeyboard(int key, int x, int y)
{
}

void idle()
{
	Vector3 pos = camera1->getPostion();
	if (!arriveExit && (int)(pos.x + 0.2) == 13 && (int)(pos.z + 0.2) == 15)
	{
		arriveExit = true;
		cout << "��ϲ�����Թ����ڣ�" << endl;
	}
}

void reshape(int width, int height)
{
	// ����ͶӰ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (float)width / height, 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
}

void showHelpInfo()
{
	cout << "---------- ";
	cout << "Welcome to Maze: The Lost World!";
	cout << "---------- ";
	cout << endl;
	cout << "---------- ";
	cout << endl;
	cout << "---------- ";
	cout << "This is a simple maze game.";
	cout << endl;
	cout << "---------- ";
	cout << endl;
	cout << "---------- ";
	cout << "Use direction key to move up, down, left, or right.";
	cout << endl;
	cout << "---------- ";
	cout << "Keys W, A, S, D also work. Either upper case and lower case is ok.";
	cout << endl;
	cout << "---------- ";
	cout << "If you feels difficult to arrive at the exit,";
	cout << endl;
	cout << "---------- ";
	cout << "press 3 on the keyboard, and enjoy a third person perspective.";
	cout << endl;
	cout << "---------- ";
	cout << "But you can't move under the third person perspective.";
	cout << endl;
	cout << "---------- ";
	cout << "You can find your current position in the maze.";
	cout << endl;
	cout << "---------- ";
	cout << "So please try to remember the maze structure.";
	cout << endl;
	cout << "---------- ";
	cout << "If you finish remembering, press 1 on the keyboard, and return to the first person perspective";
	cout << endl;
	cout << "---------- ";
	cout << "Fight!";
	cout << endl;
}
