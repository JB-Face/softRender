#pragma once

#include "math.h"

class Matrix4x4 {
public:
	Matrix4x4();  

	Matrix4x4(float f) {
		set(f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f);
	}
	Matrix4x4(float m00, float m01, float m02, float m03, // 1st column
		float m04, float m05, float m06, float m07, // 2nd column
		float m08, float m09, float m10, float m11, // 3rd column
		float m12, float m13, float m14, float m15);// 4th column

	~Matrix4x4();

	void	set(float m00, float m01, float m02, float m03, // 1st column
		float m04, float m05, float m06, float m07, // 2nd column
		float m08, float m09, float m10, float m11, // 3rd column
		float m12, float m13, float m14, float m15);// 4th column








	static Matrix4x4 zero;
	static Matrix4x4 identity;




private:
	float m[16];
	float tm[16];
	
};
//Matrix4x4 zero;
//Matrix4x4 identity;
//inline  Matrix4x4::Matrix4x4() { identity; }

class Matrix
{
};
