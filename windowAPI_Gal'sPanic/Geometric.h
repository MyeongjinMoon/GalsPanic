#pragma once
#include "header.h"

class Geometric
{
private:
	int x, y;
public:
	Geometric(int _x = 0, int _y = 0, int _v = 0, int ag = 0, int s = 0) :x(_x), y(_y) {}
	virtual ~Geometric() {}
	int get_x()const { return x; }
	int get_y()const { return y; }
	void set_x(double _x) { x = _x; }
	void set_y(double _y) { y = _y; }

	virtual void DrawFigure(HDC) = 0;
	virtual void Update() = 0;
};