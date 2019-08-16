#pragma once
#include "math.h"
#include "graph.h"


struct VSOutput
{
	Vector4 position;
	Vector3 normal;
	Vector2 uv;
	Color color;

	Vector3 varying[4];
}; 
