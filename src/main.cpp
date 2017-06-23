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

#define FPS false
#define TPS true
bool cameraFlag = FPS;
Camera *camera1 = new Camera();
Camera *camera3 = new Camera();

AssimpLoad model;

bool arriveExit = false;

// 纹理
extern GLuint wallTextureID, groundTexureID;
extern GLuint skyBoxTetureID[5];
// 显示列表
extern GLuint wallList, groundList, skyBoxList;
// 迷宫
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

	// 载入模型
	if (!model.Load("Model/spider.obj"))
	{
		cout << "Failed to load spider.obj" << endl;
		cout << endl;
	}

	// 载入纹理
	loadTexture("Texture/wall.png", wallTextureID);
	loadTexture("Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	// 启用二维纹理
	glEnable(GL_TEXTURE_2D);

	// 生成显示列表
	generateDisplayList();

	// 设置相机
	camera3->setPosition(Vector3(8, 16, 8));
	camera3->setCenter(Vector3(8, 0, 8));
	camera3->setUp(Vector3(0, 0, -1));

	// 设置投影
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, 1.0, 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, WINDOW_W, WINDOW_H);

	// 设置背景颜色
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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

//设置光源
void SetupLights() {
    GLfloat light_position[] ={3.0f,3.0f,0.0f,1.0f}; 
    GLfloat ambientLight[]={0.5f,0.5f,0.5f,1.0f};	//白色环境光  
    GLfloat diffuseLight[]={0.8f,0.8f,0.8f,0.8f};	//白色漫反射  
    GLfloat specularLight[]={1.0f,1.0f,1.0f,1.0f};	//白色镜面光
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);   //设置环境光源  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);   //设置漫反射光源  
    glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight); //设置镜面光源  
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);//设置灯光位置 
    glEnable(GL_LIGHT0); //打开白色主光源
    glEnable(GL_LIGHTING); 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	// 通过相机来实现第一人称漫游
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
	

	// 绘制天空盒
	glDisable(GL_LIGHTING);
	glPushMatrix();
	// 使天空盒与eye相对静止
	if (cameraFlag == FPS)
	{
		camera1->moveSkyBox();
	}
	glTranslatef(8, 0, 8);
	glCallList(skyBoxList);
	glPopMatrix();
	// 绘制地面
	glEnable(GL_LIGHTING);
	glPushMatrix();
	glCallList(groundList);
	glPopMatrix();

	// 绘制迷宫
	glPushMatrix();
	glCallList(wallList);
	glPopMatrix();

	// 绘制模型
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
	// 通过相机来实现第一人称漫游
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
		cout << "恭喜到达迷宫出口！" << endl;
	}
}

void reshape(int width, int height)
{
	// 设置投影
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75.0, (float)width / height, 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, width, height);
}
