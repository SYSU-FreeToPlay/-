#include "..\include\Vector3.h"

Vector3::Vector3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3::Vector3(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector3::Vector3(const Vector3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3::normalize() {
	float length = (float)(x * x + y * y + z * z);
	if (length == 0) length = 1;
	x = x / length;
	y = y / length;
	z = z / length;
}

Vector3 Vector3::normalVector(const Vector3& v)
{
	Vector3 vec;

	vec.x = y * v.z - z * v.y;
	vec.y = z * v.x - x * v.z;
	vec.z = x * v.y - y * v.x;

	return vec;
}

Vector3 Vector3::operator - (const Vector3& v)
{
	Vector3 vec;

	vec.x = x - v.x;
	vec.y = y - v.y;
	vec.z = z - v.z;

	return vec;
}

Vector3 Vector3::operator + (const Vector3& v)
{
	Vector3 vec;

	vec.x = x + v.x;
	vec.y = y + v.y;
	vec.z = z + v.z;

	return vec;
}

Vector3 Vector3::operator * (float scale)
{
	x = x * scale;
	y = y * scale;
	z = z * scale;

	return *this;
}
