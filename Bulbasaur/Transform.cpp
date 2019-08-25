
#include "Transform.h"

Transform::Transform()
{
}

Transform::Transform(const Vector3& pos, const Quaternion& rot, const Vector3 _scale)
{
	position = pos;
	rotation = rot;
	scale = scale;
	isDirty = true;
}

Transform::~Transform()
{
}

Matrix4x4 Transform::GetLocalToWorldMatrix()
{
	if (isDirty)
	{
		Matrix4x4 transMatrix(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			position.x, position.y, position.z, 1);

		Matrix4x4 scaleMatrix(scale.x, 0, 0, 0,
			0, scale.y, 0, 0,
			0, 0, scale.z, 0,
			0, 0, 0, 1);

		Matrix4x4 dd = Matrix4x4();
		

		//localToWorldMatrix = transMatrix * rotation.GetRotMatrix() * scaleMatrix;
	}
	return localToWorldMatrix;
}

void Transform::debug()
{
	rotation.debug();
}

