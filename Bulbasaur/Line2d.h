#pragma once

#include "math.h"
class Line2d
{

public:
	Vector2 start;
	Vector2 end;

	Line2d(Vector2 start,Vector2 end);
	Line2d(int a);

	Line2d();
	~Line2d();
};

