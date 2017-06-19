#include <GL\freeglut.h>
#include "..\include\skyBox.h"

extern GLuint skyBoxTetureID[5];

// x£º-2.5~2.5
// y£º-2.5~2.5
// z£º-2.5~2.5
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