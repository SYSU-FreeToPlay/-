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

// 碰撞检测，未实现
bool collision(double x, double y);

// 用于移动玩家位置
bool keyUpPressed = false, keyDownPressed = false, keyLeftPressed = false, keyRightPressed = false;
clock_t start, now;

// 用于旋转视角
static int oldmy, oldmx;
double rotateY = 0, rotateX = 0;

// 记录玩家当前位置
double posX = 1, posY = 1;
double backupX = 1, backupY = 1;

// 纹理
extern GLuint wallTextureID, groundTexureID;
extern GLuint skyBoxTetureID[5];
// 显示列表
extern GLuint wallList, groundList, skyBoxList;
// 迷宫
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];



int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("OpenGL");

	//// 光照
	//float ambientLight[] = { 0.3f, 0.5f, 0.8f, 1.0f };  // 环境光
	//float diffuseLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };  // 散射光
	//													   //float lightPosition[] = {0.0f, 0.0f, 1.0f, 0.0f};  // 光源位置
	//float lightPosition[] = { 0.0f, 1.5f, .0f, 0.0f };  // 光源位置
	//													// 材质变量
	//float matAmbient[] = { 1.0f,1.0f,1.0f,1.0f };
	//float matDiff[] = { 1.0f,1.0f,1.0f,1.0f };
	//glEnable(GL_LIGHTING);      //启用光照
	//							//为LIGHT0设置析质
	//glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiff);
	////现在开始调协LIGHT0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); //设置环境光分量
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); //设置散射光分量
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); //设置光源在场景中的位置
	//												  //启用光
	//glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	loadTexture("../Texture/wall.png", wallTextureID);
	loadTexture("../Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    //设置纹理环境
	glEnable(GL_TEXTURE_2D);                                //启用二维纹理
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

void display(void) {
	//cout << posX << " " << posY << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(rotateY, 0, 1, 0);
	//glRotatef(rotateX, 1, 0, 0);

	// 绘制天空盒
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	glCallList(skyBoxList);
	glPopMatrix();
	// 绘制地面
	glEnable(GL_LIGHTING);
	glPushMatrix();
	//glTranslatef(0, -0.5, 0);
	glTranslatef(0, -0.5, 0);
	//glScalef(10, 10, 10);
	//glTranslatef(-1, 0, -1);
	glTranslatef(-posX, 0, -posY);
	glCallList(groundList);
	glPopMatrix();
	// 绘制迷宫
	glPushMatrix();
	glTranslatef(-posX, 0, -posY);
	glCallList(wallList);
	glPopMatrix();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) { //  处理鼠标点击
												  //  第一次鼠标按下时,记录鼠标在窗口中的初始坐标
	if (state == GLUT_DOWN) {
		oldmx = x, oldmy = y;
	}
}

void motion(int x, int y) {  // 处理鼠标拖动
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
	// 根据当前的角度范围，以及按下的方向键是哪一个，来判断应该对坐标进行什么计算
	// 如，角度为-45~45，代表脸朝北，按下方向键：上 时，应该增加y坐标的值
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
