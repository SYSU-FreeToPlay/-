#ifndef _CAMERA_H
#define _CAMERA_H

#include <GL/freeglut.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include "Vector3.h"
using namespace std;

#include "..\include\maze.h"
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];

class Camera
{
public:
	Camera();

	~Camera();

	void setCamera();

	void moveW();

	void moveS();

	void moveA();

	void moveD();

	void moveMouse(int x, int y);

	// ʹ��պ���eye��Ծ�ֹ
	void moveSkyBox();

	Vector3 getPostion();

	Vector3 getCenter();

	Vector3 getUp();

	Vector3 getTranslate();

private:
	// �򵥵���ײ���
	bool collision();

	Vector3 position; //λ�� 
	Vector3 center; //���� 
	Vector3 upVector; //���Ϸ��� 
	Vector3 translate;
	int mouseX;
	int mouseY;
	float speed;
};

#endif
