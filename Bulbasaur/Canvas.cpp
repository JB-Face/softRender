
#include "math.h"
#include "Color.h"
#include "Canvas.h"
#include "Line2d.h"




void Canvas::DrawPixel(int x, int y, Color c)
{
	PixelData[x + y * width] = c.toUint32();
}

void Canvas::DrawLine(Color c, Line2d *line)
{
	if (!CohenSutherlandLineClip(line, Vector2(0, 0), Vector2(width, height)))
	{
		return;
	}

	int x1 = line->start.x;
	int y1 = line->start.y;
	int x2 = line->end.x;
	int y2 = line->end.y;

	int x, y, rem = 0;

	//line is a pixel
	if (x1 == x2 && y1 == y2)
	{
		DrawPixel(x1, y1, c);
	}
	//vertical line
	else if (x1 == x2)
	{
		int inc = (y1 <= y2) ? 1 : -1;
		for (y = y1; y != y2; y += inc) DrawPixel(x1, y, c);
		DrawPixel(x2, y2, c);
	}
	//horizontal line
	else if (y1 == y2)
	{
		int inc = (x1 <= x2) ? 1 : -1;
		for (x = x1; x != x2; x += inc) DrawPixel(x, y1, c);
		DrawPixel(x2, y2, c);
	}
	else {
		int dx = (x1 < x2) ? x2 - x1 : x1 - x2;
		int dy = (y1 < y2) ? y2 - y1 : y1 - y2;

		// slope < 1
		if (dx >= dy)
		{
			if (x2 < x1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; x <= x2; x++)
			{
				DrawPixel(x, y, c);
				rem += dy;
				if (rem >= dx)
				{
					rem -= dx;
					y += (y2 >= y1) ? 1 : -1;
					//DrawPixel(x, y, c);
				}
			}
			DrawPixel(x2, y2, c);
		}
		// slope > 1
		else {
			if (y2 < y1) x = x1, y = y1, x1 = x2, y1 = y2, x2 = x, y2 = y;
			for (x = x1, y = y1; y <= y2; y++)
			{
				DrawPixel(x, y, c);
				rem += dx;
				if (rem >= dy)
				{
					rem -= dy;
					x += (x2 >= x1) ? 1 : -1;
					//DrawPixel(x, y, c);
				}
			}
			DrawPixel(x2, y2, c);
		}
	}
}

bool Canvas::CohenSutherlandLineClip(Line2d* line, Vector2 min, Vector2 max) {
	int x0 = line->start.x;
	int x1 = line->end.x;

	int y0 = line->start.y;
	int y1 = line->end.y;

	int outcode0 = EnCode(line->start, min, max);
	int outcode1 = EnCode(line->end, min, max);
	bool accept = false;

	Vector2 tmpVec2;

	while (true) {
		// Bitwise OR is 0. Trivially accept and get out of loop. start and end all in center.
		if (!(outcode0 | outcode1))
		{
			accept = true;
			break;
		}
		else if (outcode0 & outcode1) { // Bitwise AND is not 0. Trivially reject and get out of loop
			break;
		}
		else {

			double x, y;


			int outcodeOut = outcode0 ? outcode0 : outcode1;

			if (outcodeOut & LINE_TOP) {        
				x = x0 + (x1 - x0) * (max.y - y0) / (y1 - y0);
				y = max.y;
			}
			else if (outcodeOut & LINE_BOTTOM) {
				x = x0 + (x1 - x0) * (min.y - y0) / (y1 - y0);
				y = min.y;
			}
			else if (outcodeOut & LINE_RIGHT) { 
				y = y0 + (y1 - y0) * (max.x - x0) / (x1 - x0);
				x = max.x;
			}
			else if (outcodeOut & LINE_LEFT) { 
				y = y0 + (y1 - y0) * (min.x - x0) / (x1 - x0);
				x = min.x;
			}

			if (outcodeOut == outcode0) {
				x0 = x;
				y0 = y;
				tmpVec2.x = x0;
				tmpVec2.y = y0;
				outcode0 = EnCode(tmpVec2, min, max);
			}
			else {
				x1 = x;
				y1 = y;
				tmpVec2.x = x1;
				tmpVec2.y = y1;
				outcode1 = EnCode(tmpVec2, min, max);
			}
		}
	}
	if (accept) {
		line->start.x = x0;
		line->start.y = y0;
		line->end.x = x1;
		line->end.y = y1;
	}
	return accept;
}



int  Canvas::EnCode(Vector2 & pos, Vector2 & min, Vector2& max) {
	int code;
	code = LINE_INSIDE;

	if (pos.x < min.x)
	{
		code |= LINE_LEFT;
	}
	else if (pos.x>max.x)
	{
		code |= LINE_RIGHT;
	}
	if (pos.y < min.y)
		code |= LINE_BOTTOM;
	else if (pos.y > max.y)
		code |= LINE_TOP;

	return code;
}

Vector3 Canvas::BarycentrivFast(Vector4& a, Vector4& b, Vector4& c, Vector4& p, bool& isInLine)
{

		Vector4 v0 = b - a, v1 = c - a, v2 = p - a;

		float d00 = v0.x * v0.x + v0.y * v0.y;
		float d01 = v0.x * v1.x + v0.y * v1.y;
		float d11 = v1.x * v1.x + v1.y * v1.y;
		float d20 = v2.x * v0.x + v2.y * v0.y;
		float d21 = v2.x * v1.x + v2.y * v1.y;

		float denom = d00 * d11 - d01 * d01;
		if (abs(denom) < 0.000001)
		{
			isInLine = true;
			return -1 * Vector3::one;
		}
		else
		{
			isInLine = false;
		}


		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;

		return Vector3(u, v, w);
	}



void Canvas::RasterizeTriangleLarabeeDepthMode(VSOutput* pVSOutput0, VSOutput* pVSOutput1, VSOutput* pVSOutput2)
{
	Vector2 bboxmin(INFINITY, INFINITY);
	Vector2 bboxmax(INFINITY, INFINITY);
	Vector2 clamp(width - 1, height - 1);
	//Screen space clip by bounding box
	bboxmin.x = (0.f, fmax(bboxmin.x, pVSOutput0->position.x));
	bboxmin.y = fmax(0.f, fmin(bboxmin.y, pVSOutput0->position.y));

	bboxmax.x = fmin(clamp.x, fmax(bboxmax.x, pVSOutput0->position.x));
	bboxmax.y = fmin(clamp.y, fmax(bboxmax.y, pVSOutput0->position.y));

	bboxmin.x = fmax(0.f, fmin(bboxmin.x, pVSOutput1->position.x));
	bboxmin.y = fmax(0.f, fmin(bboxmin.y, pVSOutput1->position.y));

	bboxmax.x = fmin(clamp.x, fmax(bboxmax.x, pVSOutput1->position.x));
	bboxmax.y = fmin(clamp.y, fmax(bboxmax.y, pVSOutput1->position.y));

	bboxmin.x = fmax(0.f, fmin(bboxmin.x, pVSOutput2->position.x));
	bboxmin.y = fmax(0.f, fmin(bboxmin.y, pVSOutput2->position.y));

	bboxmax.x = fmin(clamp.x, fmax(bboxmax.x, pVSOutput2->position.x));
	bboxmax.y = fmin(clamp.y, fmax(bboxmax.y, pVSOutput2->position.y));

	Vector2 P;


	bool isInline = false;
	for (P.x = bboxmin.x; P.x <= bboxmax.x; P.x++) {
		for (P.y = bboxmin.y; P.y <= bboxmax.y; P.y++)
		{
			Vector4 currentPoint(P.x, P.y, 0, 0);

			Vector3 barycentricCoord = BarycentrivFast(pVSOutput0->position, pVSOutput1->position, pVSOutput2->position, currentPoint, isInline);
			float fInvW = 1.0f / (barycentricCoord.x * pVSOutput0->position.w + barycentricCoord.y * pVSOutput1->position.w + barycentricCoord.z * pVSOutput2->position.w);
			barycentricCoord;
			
			Color col = barycentricCoord.x * pVSOutput0->color + barycentricCoord.y * pVSOutput1->color  + barycentricCoord.z * pVSOutput2->color ;
			
			//Color col = pVSOutput1->color * barycentricCoord.y ;
			if (isInline)
				continue;
			float threshold = -0.000001;
			if (barycentricCoord.x < threshold || barycentricCoord.y < threshold || barycentricCoord.z < threshold) continue;
			DrawPixel(P.x, height - P.y - 1, col);



		}
	}
	}



