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

	// 使天空盒与eye相对静止
	void moveSkyBox();

	Vector3 getPostion();

	Vector3 getCenter();

	Vector3 getUp();

	Vector3 getTranslate();

private:
	// 简单的碰撞检测
	bool collision();

	Vector3 position; //位置 
	Vector3 center; //朝向 
	Vector3 upVector; //向上方向 
	Vector3 translate;
	int mouseX;
	int mouseY;
	float speed;
};

#endif
