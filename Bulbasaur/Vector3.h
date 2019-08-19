#pragma once
class Vector3
{
public:
	float x;
	float y;
	float z;
	static Vector3 one;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float x);

	Vector3& operator+=(const Vector3& v);

	Vector3 operator+(const Vector3& v) const;

	~Vector3();


	//

	friend Vector3 operator*(double lhs, const Vector3& rhs);
	
};


static inline float Dot(const Vector3& v1, const Vector3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


static inline Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
	return Vector3((v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x));
}