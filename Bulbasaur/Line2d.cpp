#include "Line2d.h"

Line2d::Line2d()
{

}

Line2d::Line2d(Vector2 _start, Vector2 _end)
{
	start = _start;
	end = _end;
}

Line2d::Line2d(int a)
{
	start.x = 0;
	start.y = 0;

	end.x = a;
	end.y = a;


}

Line2d::~Line2d()
{
}
