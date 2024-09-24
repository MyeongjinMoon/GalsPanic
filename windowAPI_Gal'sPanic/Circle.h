#pragma once
#include "Geometric.h"
#include "Rectangle.h"

class Rectangle2D;

class Circle2D :public Geometric
{
private:
	int velocity;
	int direction;
	int radius;
	double PI = 3.14;
	bool deleteBall = false;
public:
	Circle2D(int _x = 0, int _y = 0, int v = 0, int ag = 0, double r = 0) :Geometric(_x, _y, v, ag, r), radius(), velocity(MAX_VELOCITY), direction(INITDIR) {}
	~Circle2D() {}
	int getRadius()const { return radius; }
	int get_velocity()const { return velocity; }
	int get_direction() { return direction; }
	bool get_deleteBall()const { return deleteBall; }
	void set_x(int _x);
	void set_y(int _y);
	void set_radius(int _radius);
	void set_velocity(int _vec) { velocity = _vec; }
	void set_direction(int _dir) { direction = _dir; }
	void set_deleteBall() { deleteBall = true; }

	void DrawFigure(HDC);
	void Update();
	void Update(int length);
	void Update(Rectangle2D);
	void Update(Rectangle2D*);
	void Interpolate(Rectangle2D);
};

struct Ball {
	Circle2D* geo;

	bool IsStick = false;
	Ball* next = nullptr;
	Ball* pre = nullptr;
};