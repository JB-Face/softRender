#include "Vector3.h"



Vector3::Vector3()
{
}
Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(float x)
{
	x = x;
	y = x;
	z = x;
}

Vector3 Vector3::one(1, 1, 1);



Vector3 operator * (double lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);

}

Vector3 operator * (int lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);

}

Vector3::~Vector3()
{
}





