#pragma once
#include "math.h"
class Transform
{
public:

	bool isDirty;
	Vector3 position;
	Quaternion rotation;
	Vector3 scale;


	Transform();
	Transform(const Vector3& pos, const Quaternion& rot, const Vector3 _scale);
	~Transform();


	Matrix4x4 GetLocalToWorldMatrix();
	void debug();

private:
	Matrix4x4 localToWorldMatrix;
	Matrix4x4 worldToLocalMatrix;

};
