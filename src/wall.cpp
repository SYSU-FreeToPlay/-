#include <GL\freeglut.h>
#include "..\include\maze.h"
#include "..\include\wall.h"

extern GLuint wallTextureID;
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];

// ͨ���ظ�����ǽ�ڵ�Ԫ��������Թ�
// x��0~16
// y��-0.5~0.5
// z��0~-16
void drawWalls()
{
	glPushMatrix();
	glTranslatef(0, -0.5, 0);
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			if (mazeData[i][j] == 'W')
			{
				// ͨ��ƽ�ƣ�����ǽ�ڡ�ƽ�Ƶ������ڵ�ͼ�����λ����
				glPushMatrix();
				glTranslatef(j, 0, i);
				drawWallUnit();
				glPopMatrix();
			}
		}
	}

	glPopMatrix();
}

// ����һ��������������壬��Ϊǽ�ڵĻ��Ƶ�Ԫ
// x��0~1
// y��0~1
// z��0~1
void drawWallUnit()
{
	/*glPushMatrix();
	glTranslatef(0.5, 0.5, 0.5);
	glutSolidCube(1);
	glPopMatrix();
	return;*/

	glPushMatrix();
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1);
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glRotatef(-90, 0, 1, 0);
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	drawWallFace();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	drawWallFace();
	glPopMatrix();
}

// ����һ�������Σ���Ϊ�������һ����
// x��0~1
// y��0~1
// z��0
void drawWallFace()
{
	glBindTexture(GL_TEXTURE_2D, wallTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0);

	glTexCoord2f(0, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 1, 0);

	glTexCoord2f(1, 1);
	glNormal3f(0, 0, -1);
	glVertex3f(1, 1, 0);

	glTexCoord2f(1, 0);
	glNormal3f(0, 0, -1);
	glVertex3f(1, 0, 0);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}
