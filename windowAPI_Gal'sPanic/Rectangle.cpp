#include "Rectangle.h"

void Rectangle2D::set_x(int _x)
{
	Geometric::set_x(_x);
}

void Rectangle2D::set_y(int _y)
{
	Geometric::set_y(_y);
}

void Rectangle2D::set_diagonal(int r)
{
	this->diagonal = sqrt(pow((r / 2), 2) + pow((r / 2), 2));
}

bool Rectangle2D::Is_contains(Circle2D* geo)
{
	if (this->getDiagonal(this->get_x() - this->getWidth() / 2 - geo->get_x(), this->get_y() - this->getHeight() / 2 - geo->get_y()) <= geo->getRadius()
		|| this->getDiagonal(this->get_x() - this->getWidth() / 2 - geo->get_x(), this->get_y() + this->getHeight() / 2 - geo->get_y()) <= geo->getRadius()
		|| this->getDiagonal(this->get_x() + this->getWidth() / 2 - geo->get_x(), this->get_y() + this->getHeight() / 2 - geo->get_y()) <= geo->getRadius()
		|| this->getDiagonal(this->get_x() + this->getWidth() / 2 - geo->get_x(), this->get_y() - this->getHeight() / 2 - geo->get_y()) <= geo->getRadius()
		|| (geo->getRadius() + this->getWidth() / 2) > abs(this->get_x() - geo->get_x()) && (geo->getRadius() + this->getHeight() / 2) > abs(this->get_y() - geo->get_y()))
	{
		if (this->getDiagonal(this->get_x() - this->getWidth() / 2 - geo->get_x(), this->get_y() - this->getHeight() / 2 - geo->get_y()) <= geo->getRadius())
			return true;
		if (this->getDiagonal(this->get_x() - this->getWidth() / 2 - geo->get_x(), this->get_y() + this->getHeight() / 2 - geo->get_y()) <= geo->getRadius())
			return true;
		if (this->getDiagonal(this->get_x() + this->getWidth() / 2 - geo->get_x(), this->get_y() + this->getHeight() / 2 - geo->get_y()) <= geo->getRadius())
			return true;
		if (this->getDiagonal(this->get_x() + this->getWidth() / 2 - geo->get_x(), this->get_y() - this->getHeight() / 2 - geo->get_y()) <= geo->getRadius())
			return true;
		if ((geo->getRadius() + this->getWidth() / 2) > abs(this->get_x() - geo->get_x()) && (geo->getRadius() + this->getHeight() / 2) > abs(this->get_y() - geo->get_y()))
			return true;

		return true;
	}
	return false;
}
bool Rectangle2D::Is_contains(item* item)
{
	double temp_x, temp_y;
	temp_x = abs(this->get_x() - item->p.x);
	temp_y = abs(this->get_y() - item->p.y);

	if (temp_x <= (getWidth() / 2 + item->length) && temp_y <= (getHeight() / 2 + item->length))
	{
		return true;
	}
	return false;
}

void Rectangle2D::DrawFigure(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	POINT p[4];

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	p[0] = { this->get_x() - this->getWidth() / 2 ,this->get_y() - this->getHeight() / 2 };
	p[1] = { this->get_x() + this->getWidth() / 2 ,this->get_y() - this->getHeight() / 2 };
	p[2] = { this->get_x() + this->getWidth() / 2 ,this->get_y() + this->getHeight() / 2 };
	p[3] = { this->get_x() - this->getWidth() / 2 ,this->get_y() + this->getHeight() / 2 };

	Polygon(hdc, p, 4);

	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void Rectangle2D::Update()
{

}