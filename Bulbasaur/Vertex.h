#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Color.h"
struct VSOutput
{
	Vector4 position;
	Vector3 normal;
	Vector2 uv;
	Color color;

	Vector3 varying[4];
};

class Vertex
{
public:
	Vertex();
	~Vertex();
};

