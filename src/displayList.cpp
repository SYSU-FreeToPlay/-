#include <GL\freeglut.h>
#include "..\include\displayList.h"
#include "..\include\wall.h"
#include "..\include\ground.h"
#include "..\include\skyBox.h"

GLuint wallList, groundList, skyBoxList;

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
