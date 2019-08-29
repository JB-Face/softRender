#pragma once

#include <cmath>
#include <iostream>



static float Deg2Rad = 0.0174532924f;
static float Rad2Deg = 57.2957795f;
static float EPSILON = FLT_EPSILON;


class Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float x, float y);
	Vector2(double _x, double _y);
	Vector2(int _x, int _y);
	~Vector2();
};

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float x);

	Vector3& operator+=(const Vector3& v);

	Vector3 operator+(const Vector3& v) const;

	~Vector3();

	void debug();


	//

	friend Vector3 operator*(double lhs, const Vector3& rhs);


	static Vector3 one;

};

class Vector4
{
public:
	float x, y, z, w;
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}
	Vector4(const Vector4& a) : x(a.x), y(a.y), z(a.z), w(a.w) {}
	Vector4(float _x, float _y, float _z) :x(_x), y(_y), z(_z), w(1.0f) {}
	Vector4(float _x, float _y, int _z, int _w) :x(_x), y(_y), z(_z), w(_z) {};
	// 重载赋值运算符并返回引用
	//Vector4& operator=(const Vector4 &a);

	bool operator==(const Vector4& a) const;

	bool operator!=(const Vector4& a) const;

	// 向量点乘,重载"*"运算符
	float operator*(const Vector4& a) const;

	Vector4 operator-() const;

	Vector4 operator+(const Vector4& a) const;

	Vector4 operator-(const Vector4& a) const;

	// 向量与标量相乘，重载"*"运算符
	Vector4 operator*(float a)const;

	Vector4 operator/(float a)const;

	Vector4& operator+=(const Vector4& a);

	Vector4& operator-=(const Vector4& a);

	Vector4& operator*=(float a);

	Vector4& operator/=(float a);

	// 置为零向量
	void zero();

	// 向量标准化
	void normalize();

	// 向量模长
	static inline float Magnitude(const Vector4& a)
	{
		float sq = a.x * a.x + a.y * a.y + a.z * a.z;
		return sqrtf(sq);
	}

	// 向量叉乘
	static inline Vector4 Cross(const Vector4& a, const Vector4& b)
	{
		return Vector4(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}

	// 向量距离
	static inline float Distance(const Vector4& a, const Vector4& b)
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		float dz = a.z - a.z;
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}

	// 向量插值，t取值 [0, 1]
	static inline Vector4 Leap(const Vector4& a, const Vector4& b, float t)
	{
		return Vector4(a + (b - a) * t);
	}
};

class Matrix4x4 {
public:
	float m[16];

	Matrix4x4();
	Matrix4x4(float f);
	Matrix4x4(float f01, float f02, float f03, float f04,
		float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34);

	float operator[](int index) const;

	inline Matrix4x4 operator*(const Matrix4x4& n) const;

	Matrix4x4& transpose();


	void debug()
	{
		for (int i = 0; i < 15; i++)
		{
			std::cout << m[i];
		}
	}



	~Matrix4x4();



};

class Quaternion
{
public:
	float x, y, z, w;
	
	 static Quaternion identity;
	//Constructor:
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	Quaternion(float yaw, float pitch, float roll);

	static Quaternion Euler(float x, float y, float z) {

		x *= Deg2Rad;
		y *= Deg2Rad;
		z *= Deg2Rad;

		float  angle;
		float  sinRoll, sinPitch, sinYaw, cosRoll, cosPitch, cosYaw;

		angle = x * 0.5f;
		sinYaw = sin(angle);
		cosYaw = cos(angle);

		angle = y * 0.5f;
		sinPitch = sin(angle);
		cosPitch = cos(angle);

		angle = z * 0.5f;
		sinRoll = sin(angle);
		cosRoll = cos(angle);

		float _x = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
		float _y = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
		float _z = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
		float _w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;

		float invMag = 1.0f / (_x * _x + _y * _y + _z * _z + _w * _w);

		return Quaternion(_x * invMag, _y * invMag, _z * invMag, _w * invMag);
	}




	friend Quaternion operator* (const Quaternion& lhs, const Quaternion& rhs);
	
	~Quaternion();


	//var:
	 //Quaternion identity = Quaternion(0,0,0,1);//TODO
	Matrix4x4 GetRotMatrix();

	//function



	void debug();
	void setQuaternion(float _yaw, float _pitch, float _roll);
	void setEulerAngle(float x, float y, float z, float w);
	static float Dot(const Quaternion& lhs, Quaternion& rhs);
	static Quaternion Lerp(const Quaternion& lhs, Quaternion& rhs, float f);
	//TODO	
	static Quaternion slerp(const Quaternion& lhs, Quaternion& rhs, float f);


	Quaternion Inverse() const;
	Vector3 EulerAngle() const;

private:
	Vector3 eulerAngles;

};


class Transform {
public :
	Transform();
	Transform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);
	~Transform();

	Matrix4x4 GetLocalToWorldMatrix();
	bool isDirty;
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;

	void Translate(const Vector3& delta);
	void Rotate(float xRot, float yRot, float zRot);
	void Scale(const Vector3& scale);

private:
	Matrix4x4 localToWorldMatrix;
	Matrix4x4 worldToLocalMatrix;

};


