#include <GL\freeglut.h>
#include "..\include\arrow.h"

void drawArrow()
{
	glPushMatrix();

	// ��ͷ�������β��֣��±���
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, 0, 0.8);
	glVertex3f(0.3, 0, 0.6);
	glVertex3f(0.7, 0, 0.6);
	glEnd();

	// ��ͷ�ĳ����β��֣��±���
	glBegin(GL_QUADS);
	glVertex3f(0.45, 0, 0.6);
	glVertex3f(0.55, 0, 0.6);
	glVertex3f(0.55, 0, 0.2);
	glVertex3f(0.45, 0, 0.2);
	glEnd();

	// ��ͷ�������Σ��ϱ���
	glBegin(GL_TRIANGLES);
	glVertex3f(0.5, 0.2, 0.8);
	glVertex3f(0.3, 0.2, 0.6);
	glVertex3f(0.7, 0.2, 0.6);
	glEnd();

	// ��ͷ�ĳ����β��֣��ϱ���
	glBegin(GL_QUADS);
	glVertex3f(0.45, 0.2, 0.6);
	glVertex3f(0.55, 0.2, 0.6);
	glVertex3f(0.55, 0.2, 0.2);
	glVertex3f(0.45, 0.2, 0.2);
	glEnd();

	// ��ͷ�������β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0, 0.8);
	glVertex3f(0.3, 0, 0.6);
	glVertex3f(0.3, 0.2, 0.6);
	glVertex3f(0.5, 0.2, 0.8);
	glEnd();

	// ��ͷ�������β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.5, 0, 0.8);
	glVertex3f(0.7, 0, 0.6);
	glVertex3f(0.7, 0.2, 0.6);
	glVertex3f(0.5, 0.2, 0.8);
	glEnd();

	// ��ͷ�������β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.3, 0, 0.6);
	glVertex3f(0.7, 0, 0.6);
	glVertex3f(0.7, 0.2, 0.6);
	glVertex3f(0.3, 0.2, 0.6);
	glEnd();

	// ��ͷ�ĳ����β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.45, 0, 0.6);
	glVertex3f(0.45, 0, 0.2);
	glVertex3f(0.45, 0.2, 0.2);
	glVertex3f(0.45, 0.2, 0.6);
	glEnd();

	// ��ͷ�ĳ����β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.55, 0, 0.6);
	glVertex3f(0.55, 0, 0.2);
	glVertex3f(0.55, 0.2, 0.2);
	glVertex3f(0.55, 0.2, 0.6);
	glEnd();

	// ��ͷ�ĳ����β��ֵĲ���
	glBegin(GL_QUADS);
	glVertex3f(0.4, 0, 0.6);
	glVertex3f(0.6, 0, 0.6);
	glVertex3f(0.6, 0.2, 0.6);
	glVertex3f(0.4, 0.2, 0.6);
	glEnd();

	glPopMatrix();
}

void drawRoadToExit()
{
	// ���Ƽ�ͷ
	glPushMatrix();
	glTranslatef(1, -0.5, 1);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.5, 2);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.5, 3);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.5, 4);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.5, 5);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(7, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(8, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(9, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, -0.5, 6 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11, -0.5, 6);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11, -0.5, 7);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(11, -0.5, 8 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(12, -0.5, 8 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, -0.5, 8 + 1);
	glRotatef(90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 8);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 9);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 10);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 11);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 12);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(14, -0.5, 13);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -0.5, 13 + 1);
	glRotatef(-90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(15, -0.5, 13 + 1);
	glRotatef(-90, 0, 1, 0);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, -0.5, 14);
	drawArrow();
	glPopMatrix();

	glPopMatrix();
}