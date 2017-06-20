#include <GL\freeglut.h>
#include "..\include\ground.h"
#include "..\include\maze.h"

extern GLuint groundTexureID;

// x£º0~1
// y£º-0.5
// z£º0~16
void drawGround()
{
	glBindTexture(GL_TEXTURE_2D, groundTexureID);
	for (int i = 0; i < MAZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAZE_WIDTH; j++)
		{
			glPushMatrix();
			glTranslatef(0, -0.5, 0);
			glTranslatef(j, 0, i);
			glBegin(GL_QUADS);
			glTexCoord2f(1, 1);
			glNormal3f(0, 1, 0);
			glVertex3f(0, 0, 0);

			glTexCoord2f(1, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(1, 0, 0);

			glTexCoord2f(0, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(1, 0, 1);

			glTexCoord2f(0, 1);
			glNormal3f(0, 1, 0);
			glVertex3f(0, 0, 1);
			glEnd();

			glPopMatrix();
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}
