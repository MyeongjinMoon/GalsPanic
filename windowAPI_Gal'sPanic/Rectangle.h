#pragma once
#include "Circle.h"

class Circle2D;

class Rectangle2D :public Geometric
{
private:
	int width;
	int height;
	int diagonal;
	int hp;
public:
	Rectangle2D(int _x = 0, int _y = 0, int s = 0, int v = 0, int ag = 0)
		:Geometric(_x, _y, v, ag, s), width(), height(), diagonal(sqrt(pow((getWidth() / 2), 2) + pow((getHeight() / 2), 2))) {}
	~Rectangle2D() {}
	int getWidth()const { return width; }
	int getHeight()const { return height; }
	int getHp()const { return hp; }
	double getDiagonal(int x, int y) { return sqrt(pow(x, 2) + pow(y, 2)); }
	void set_x(int _x);
	void set_y(int _y);
	void set_width(int _w) { width = _w; }
	void set_height(int _h) { height = _h; }
	void set_hp(int _hp) { hp = _hp; }
	void set_diagonal(int r);

	bool Is_contains(Circle2D*);
	bool Is_contains(item*);
	void DrawFigure(HDC);
	void Update();
};