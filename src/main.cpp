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

	// 载入纹理
	loadTexture("../Texture/wall.png", wallTextureID);
	loadTexture("../Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	// 启用二维纹理
	glEnable(GL_TEXTURE_2D);

	generateDisplayList();

	// 设置投影
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
	camera->setCamera();

	// 绘制天空盒
	glDisable(GL_LIGHTING);
	glPushMatrix();
	// 使天空盒与eye相对静止
	camera->moveSkyBox();
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
