#pragma once
#include "math.h"
#include <iostream>
class Quaternion
{

public:
	Quaternion(float x, float y, float z, float w);
	Quaternion(float yaw, float pitch, float roll);
	~Quaternion();
	static Quaternion identity;
	//Cos theta of two quaternion
	static float Dot(const Quaternion& lhs, const Quaternion& rhs);
	static Quaternion Lerp(const Quaternion& a, const Quaternion& b, float t);
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
	static float Angle(const Quaternion& lhs, const Quaternion& rhs);
	void SetEulerAngle(float yaw, float pitch, float roll);
	void Set(float _x, float _y, float _z, float _w);

	Quaternion Conjugate() const;
	Quaternion Inverse() const;
	Vector3 EulerAngle() const;

	void operator+(const Quaternion& q);
	void operator*(float s);
	void operator-(const Quaternion& q);
	friend Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
	friend Vector3 operator *(const Quaternion& rotation, const Vector3& point);


	void debug()
	{
		std::cout << "(" << x << "," << y << "," << z << "," << w << ")";

	}

	float x;
	float y;
	float z;
	float w;

private:

	Vector3 eulerAngles;


};

