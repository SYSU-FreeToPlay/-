#ifndef _VECTOR3_H
#define _VECTOR3_H

class Vector3
{
public:
	Vector3();

	Vector3(float a, float b, float c);

	Vector3(const Vector3& vector);

	void normalize();

	Vector3 normalVector(const Vector3& v);

	Vector3 operator - (const Vector3& v);

	Vector3 operator + (const Vector3& v);

	Vector3 operator * (float scale);

public:
	float x, y, z;
};

#endif
