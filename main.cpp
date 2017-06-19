#include <GL/freeglut.h>
#include <soil.h>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>

#define WINDOW_W 400
#define WINDOW_H 400
#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16

using namespace std;

#define M_PI 3.14159265358979323846
#define GLUT_WHEEL_UP 3
#define GLUT_WHEEL_DOWN 4

void generateDisplayList();

void display();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void specialKeyboard(int key, int x, int y);
void upSpecialKeyboard(int key, int x, int y);
void idle();

// 绘制迷宫墙壁
void drawWalls();
void drawWallUnit();
void drawWallFace();
void loadTexture(string filename, GLuint &textureID); // 载入纹理

// 绘制地面
void drawGround();

// 绘制天空盒
void drawSkyBox();
void loadSkyBoxTexture();

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
GLuint wallTextureID, groundTexureID;
GLuint skyBoxTetureID[5];

// 显示列表
GLuint wallList, groundList, skyBoxList;

char mazeData[MAZE_HEIGHT][MAZE_WIDTH] = {
	{ 'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ','W','W','W',' ','W',' ','W',' ',' ',' ',' ','W' },
	{ 'W',' ','W','W',' ',' ','W',' ','W','W',' ','W',' ','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' },
	{ 'W',' ','W','W','W','W','W','W','W','W',' ','W','W','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','W',' ',' ','W' },
	{ 'W',' ','W','W','W','W','W',' ','W','W','W',' ','W','W','W','W' },
	{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ','W','W','W','W','W','W','W',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ',' ',' ','W',' ',' ',' ','W',' ',' ','W',' ','W' },
	{ 'W',' ','W','W','W','W','W',' ','W','W','W','W',' ','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ','W',' ',' ',' ',' ',' ',' ','W',' ','W' },
	{ 'W',' ',' ','W','W',' ','W','W','W','W',' ','W','W','W',' ','W' },
	{ 'W',' ',' ',' ','W',' ','W',' ',' ',' ',' ','W',' ',' ',' ','W' },
	{ 'W','W','W','W','W','W','W','W','W','W','W','W','W',' ','W','W' },
};



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
	loadTexture("Texture/wall.png", wallTextureID);
	loadTexture("Texture/ground.jpg", groundTexureID);
	loadSkyBoxTexture();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    //设置纹理环境
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
	glutMainLoop();

	return 0;
}



void generateDisplayList() {
	wallList = glGenLists(1);
	glNewList(wallList, GL_COMPILE);
	drawWalls();
	glEndList();

	groundList = glGenLists(1);
	glNewList(groundList, GL_COMPILE);
	drawGround();
	glEndList();

	skyBoxList = glGenLists(1);
	glNewList(skyBoxList, GL_COMPILE);
	drawSkyBox();
	glEndList();
}

void display(void) {
	cout << posX << " " << posY << endl;
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
	//if (rotateX > 75)
	//	rotateX = 75;
	//if (rotateX < -75)
	//	rotateX = -75;

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

void drawWalls() {
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-0.5, -0.5, 0.5);
	for (int i = 0; i < MAZE_HEIGHT; i++) {
		for (int j = 0; j < MAZE_WIDTH; j++) {
			if (mazeData[i][j] == 'W') {
				// 通过平移，将“墙壁”平移到他们在地图的相对位置上
				glPushMatrix();
				glTranslatef(j, -i, 0);
				drawWallUnit();
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

// 创建一个带纹理的立方体，作为墙壁单元
// x：0~1
// y：0~1
// z：-1~0
void drawWallUnit() {
	glPushMatrix();
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -1);
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	drawWallFace();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(1, 0, 0);
	glRotatef(90, 0, 1, 0);
	drawWallFace();
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	drawWallFace();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	drawWallFace();
	glPopMatrix();

	//glFlush();
}

// x：0~1
// y：0~1
// z：0
void drawWallFace() {
	glBindTexture(GL_TEXTURE_2D, wallTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	//glNormal3f(0, 0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0, 1);
	//glNormal3f(0, 0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 1, 0);

	glTexCoord2f(1, 1);
	//glNormal3f(0, 0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(1, 1, 0);

	glTexCoord2f(1, 0);
	//glNormal3f(0, 0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(1, 0, 0);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

// x：-1~1
// y：-1~1
// z：0
void drawGround() {
	glBindTexture(GL_TEXTURE_2D, groundTexureID);
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			glPushMatrix();
			glRotatef(90, 1, 0, 0);
			glTranslatef(j - 0.5, MAZE_WIDTH - 1.5 - i, 0);
			glBegin(GL_QUADS);
			glTexCoord2f(1, 1);
			glVertex3f(1, 1, 0);
			glTexCoord2f(1, 0);
			glVertex3f(1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(0, 1);
			glVertex3f(0, 1, 0);
			glEnd();

			glPopMatrix();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	/*glPushMatrix();
	glRotatef(90, 1, 0, 0);

	glBegin(GL_QUADS);
	glVertex3f(1, 1, 0);
	glVertex3f(1, -1, 0);
	glVertex3f(-1, -1, 0);
	glVertex3f(-1, 1, 0);
	glEnd();

	glPopMatrix();*/
}

// x：-2.5~2.5
// y：-2.5~2.5
// z：-2.5~2.5
void drawSkyBox() {
	glPushMatrix();
	glScalef(5, 5, 5);

	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);

	glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	glPopAttrib();
	glPopMatrix();
}

void loadTexture(string filename, GLuint &textureID) {
	cout << "start loading texture of wall" << endl;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    //设置纹理参数
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	cout << "Texture: " << filename << " loaded." << endl;
	cout << "loading texture of wall completes" << endl;
	cout << endl;
}

void loadSkyBoxTexture() {
	cout << "start loading textures of SkyBox" << endl;
	string filename[] = {"1_left.jpg", "2_front.jpg", "3_right.jpg", "4_back.jpg", "5_top.jpg"};
	glGenTextures(5, &skyBoxTetureID[0]);
	int width, height;
	unsigned char* image;
	for (int i = 0; i < 5; i++) {
		filename[i] = string("Texture/skybox/") + filename[i];

		glBindTexture(GL_TEXTURE_2D, skyBoxTetureID[i]);
		image = SOIL_load_image(filename[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		cout << width << " " << height << endl;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    //设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		glBindTexture(GL_TEXTURE_2D, 0);
		cout << "Texture: " << filename[i] << " loaded." << endl;
	}
	cout << "loading textures of SkyBox completes" << endl;
	cout << endl;
}
