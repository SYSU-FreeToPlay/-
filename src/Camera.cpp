#include <GL/freeglut.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include "..\include\Vector3.h"
#include "..\include\Camera.h"
using namespace std;

#include "..\include\maze.h"
extern char mazeData[MAZE_HEIGHT][MAZE_WIDTH];

Camera::Camera()
{
	Vector3 defaultPos = Vector3(1.5, 0, 1.5);
	Vector3 defaultCenter = Vector3(1.5, 0, 5);
	Vector3 defaultUp = Vector3(0.0, 1.0, 0.0);
	Vector3 defaultTranslate = Vector3(0, 0, 0);

	position = defaultPos;
	center = defaultCenter;
	upVector = defaultUp;
	translate = defaultTranslate;
	mouseX = -1;
	mouseY = -1;
	speed = 0.2;
	disableCol = false;
}

Camera::~Camera()
{
}

void Camera::setCamera()
{
	gluLookAt(position.x, position.y, position.z,
		center.x, center.y, center.z,
		upVector.x, upVector.y, upVector.z);
}

void Camera::moveW()
{
	Vector3 backupPos = position;
	Vector3 backupCenter = center;

	Vector3 vector = center - position;
	vector.normalize();

	position.x += vector.x * speed;
	//position.y += vector.y * speed;
	position.z += vector.z * speed;

	center.x += vector.x * speed;
	//center.y += vector.y * speed;
	center.z += vector.z * speed;

	if (!disableCol && collision()) {
		position = backupPos;
		center = backupCenter;
		return;
	}

	translate = translate + Vector3(vector.x * speed, 0, vector.z * speed);
}

void Camera::moveS()
{
	Vector3 backupPos = position;
	Vector3 backupCenter = center;

	Vector3 vector = position - center;
	vector.normalize();

	position.x += vector.x * speed;
	//position.y += vector.y * speed;
	position.z += vector.z * speed;

	center.x += vector.x * speed;
	//center.y += vector.y * speed;
	center.z += vector.z * speed;

	if (!disableCol && collision()) {
		position = backupPos;
		center = backupCenter;
		return;
	}

	translate = translate + Vector3(vector.x * speed, 0, vector.z * speed);
}

void Camera::moveA()
{
	Vector3 backupPos = position;
	Vector3 backupCenter = center;

	Vector3 vector = position - center;
	vector = vector.normalVector(upVector);
	vector.normalize();

	position.x += vector.x * speed;
	//position.y += vector.y * speed;
	position.z += vector.z * speed;

	center.x += vector.x * speed;
	//center.y += vector.y * speed;
	center.z += vector.z * speed;

	if (!disableCol && collision()) {
		position = backupPos;
		center = backupCenter;
		return;
	}

	translate = translate + Vector3(vector.x * speed, 0, vector.z * speed);
}

void Camera::moveD()
{
	Vector3 backupPos = position;
	Vector3 backupCenter = center;

	Vector3 vector = center - position;
	vector = vector.normalVector(upVector);
	vector.normalize();

	position.x += vector.x * speed;
	//position.y += vector.y * speed;
	position.z += vector.z * speed;

	center.x += vector.x * speed;
	//center.y += vector.y * speed;
	center.z += vector.z * speed;

	if (!disableCol && collision()) {
		position = backupPos;
		center = backupCenter;
		return;
	}

	translate = translate + Vector3(vector.x * speed, 0, vector.z * speed);
}

void Camera::moveMouse(int x, int y)
{
	if (mouseX == -1) {
		mouseX = x;
		mouseY = y;
		return;
	}
	else if (mouseX == x && mouseY == y)
	{
		return;
	}
	else
	{
		float aX = (float)(mouseX - x) / 100.0;
		float aY = (float)(mouseY - y) / 250.0;

		Vector3 vector = center - position;
		Vector3 vectorX = vector.normalVector(upVector) * (-1);
		Vector3 vectorY = upVector;

		float length = (float)(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		float radius = (float)(vector.x * vector.x + vector.z * vector.z);

		vectorX.normalize();
		vectorY.normalize();

		Vector3 vectorXY;
		//限制上下视角角度范围 
		if (vector.y > 5 && vectorY.y * aY > 0)
		{
			vectorXY = vectorX * aX;
		}
		else if (vector.y < -5 && vectorY.y * aY < 0)
		{
			vectorXY = vectorX * aX;
		}
		else
		{
			vectorXY = vectorX * aX + vectorY * aY;
		}
		vectorXY = vectorXY * (length + 1.0);
		vector = vector + vectorXY;
		vector.normalize();
		float scale = (float)radius / (vector.x * vector.x + vector.z * vector.z);
		scale = sqrt(scale);
		vector = vector * scale;

		center = position + vector;
		mouseX = x;
		mouseY = y;
	}
}

// 使天空盒与eye相对静止
void Camera::moveSkyBox()
{
	glTranslatef(translate.x, translate.y, translate.z);
}

Vector3 Camera::getPostion()
{
	return position;
}

void Camera::setPosition(Vector3 pos)
{
	position = pos;
}

Vector3 Camera::getCenter()
{
	return center;
}

void Camera::setCenter(Vector3 c)
{
	center = c;
}

Vector3 Camera::getUp()
{
	return upVector;
}

void Camera::setUp(Vector3 up)
{
	upVector = up;
}

Vector3 Camera::getTranslate()
{
	return translate;
}

void Camera::disableCollision() {
	disableCol = true;
}

// 简单的碰撞检测
bool Camera::collision()
{
	if (mazeData[(int)(position.z + 0.2)][(int)(position.x + 0.2)] == 'W')
	{
		return true;
	}
	else if (mazeData[(int)(position.z + 0.2)][(int)(position.x - 0.2)] == 'W')
	{
		return true;
	}
	else if (mazeData[(int)(position.z - 0.2)][(int)(position.x - 0.2)] == 'W')
	{
		return true;
	}
	else if (mazeData[(int)(position.z - 0.2)][(int)(position.x + 0.2)] == 'W')
	{
		return true;
	}
	return false;
}
