#ifndef CANVAS_H
#define CANVAS_H

#include <SDL.h>
#include "math.h"
#include "graph.h"
class Canvas
{
public:
	Uint32* PixelData;
	int width, height;
	SDL_Rect rect;

	Canvas(int _w, int _h) : width(_w), height(_h)
	{
		PixelData = new Uint32[width * height];
		rect.x = 0;
		rect.y = 0;
		rect.w = width;
		rect.h = height;
	}

	void DrawPixel(int x, int y, Color c);

	void DrawLine(Color c, Line2d *line);

	bool CohenSutherlandLineClip(Line2d* line, Vector2 min, Vector2 max);
	int EnCode(Vector2& pos, Vector2& min, Vector2& max);
	Vector3 BarycentrivFast(Vector4& a, Vector4& b, Vector4& c, Vector4& p, bool& isInLine);

	void RasterizeTriangleLarabeeDepthMode(VSOutput* pVSOutput0, VSOutput* pVSOutput1, VSOutput* pVSOutput2);







};


#endif	// £¡CANVAS_H


