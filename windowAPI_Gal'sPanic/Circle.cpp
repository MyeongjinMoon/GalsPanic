#include "Circle.h"

void Circle2D::set_x(int _x)
{
	Geometric::set_x(_x);
}

void Circle2D::set_y(int _y)
{
	Geometric::set_y(_y);
}

void Circle2D::set_radius(int _radius)
{
	radius = _radius;
}

void Circle2D::DrawFigure(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	oldPen = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, this->get_x() - getRadius(), this->get_y() - getRadius(), this->get_x() + getRadius(), this->get_y() + getRadius());

	SelectObject(hdc, oldPen);
	DeleteObject(hPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);
}

void Circle2D::Update()
{
	int dir = this->get_direction();

	double new_x = round(this->get_x() + cos(dir * 3.14 / 180) * this->get_velocity());
	double new_y = round(this->get_y() + -sin(dir * 3.14 / 180) * this->get_velocity());

	if (new_x <= WINDOW_WIDTH / 2 - MAP_WIDTH / 2 + getRadius())
	{
		new_x = getRadius() + WINDOW_WIDTH / 2 - MAP_WIDTH / 2;
		int ag = abs(180 - dir);
		if (dir <= 180)
			set_direction(ag);
		else
			set_direction(360 - ag);
	}
	if (new_y <= WINDOW_HEIGHT / 2 - MAP_HEIGHT / 2 + getRadius())
	{
		new_y = WINDOW_HEIGHT / 2 - MAP_HEIGHT / 2 + getRadius();
		int ag = abs(180 - dir);
		if (dir >= 90)
			set_direction(180 + ag);
		else
			set_direction(180 + ag);
	}
	if (new_x >= WINDOW_WIDTH / 2 + MAP_WIDTH / 2 - getRadius())
	{
		new_x = WINDOW_WIDTH / 2 + MAP_WIDTH / 2 - getRadius();
		int ag = abs(180 - dir);
		if (dir >= 180)
			set_direction(180 + (180 - ag));
		else
			set_direction(ag);
	}
	if (new_y >= WINDOW_HEIGHT / 2 + MAP_HEIGHT / 2 + getRadius())
	{
		// 공 삭제
		set_deleteBall();
	}

	set_x(new_x);
	set_y(new_y);
}

void Circle2D::Update(int length)
{
	int dir = this->get_direction();

	double new_x = this->get_x() + cos(dir * 3.14 / 180) * length;
	double new_y = this->get_y() + -sin(dir * 3.14 / 180) * length;

	if (new_x <= WINDOW_WIDTH / 2 - MAP_WIDTH / 2 + getRadius())
	{
		new_x = getRadius() + WINDOW_WIDTH / 2 - MAP_WIDTH / 2;
		int ag = abs(180 - dir);
		if (dir <= 180)
			set_direction(ag);
		else
			set_direction(360 - ag);
	}
	if (new_y <= WINDOW_HEIGHT / 2 - MAP_HEIGHT / 2 + getRadius())
	{
		new_y = WINDOW_HEIGHT / 2 - MAP_HEIGHT / 2 + getRadius();
		int ag = abs(180 - dir);
		if (dir >= 90)
			set_direction(180 + ag);
		else
			set_direction(180 + ag);
	}
	if (new_x >= WINDOW_WIDTH / 2 + MAP_WIDTH / 2 - getRadius())
	{
		new_x = WINDOW_WIDTH / 2 + MAP_WIDTH / 2 - getRadius();
		int ag = abs(180 - dir);
		if (dir >= 180)
			set_direction(180 + (180 - ag));
		else
			set_direction(ag);
	}
	if (new_y >= WINDOW_HEIGHT / 2 + MAP_HEIGHT / 2 + getRadius())
	{
		// 공 삭제
		set_deleteBall();
	}

	set_x(new_x);
	set_y(new_y);
}

void Circle2D::Update(Rectangle2D* player)
{
	bool right = 0;
	bool updown = 1;
	int new_x = player->get_x() - this->get_x();
	if (new_x > 0)
		right = 1;
	int new_y = player->get_y() - this->get_y();
	if (new_y < 0)
		updown = 0;
	double new_z = ceil(sqrt(pow(new_x, 2) + pow(new_y, 2)));
	double new_a = acos(abs(new_x) / new_z) * 180 / 3.14;
	if (updown)
	{
		if (right)
			this->set_direction(180 - new_a);
		else
			this->set_direction(new_a);
	}
	else
	{
		if (right)
			this->set_direction(180 + new_a);
		else
			this->set_direction(360 - new_a);
	}
	set_y(player->get_y() - PLAYER_RADIUS / 2 - getRadius());
}

void Circle2D::Update(Rectangle2D block)
{
	int dir = this->get_direction();

	POINT b[4];
	b[0] = { block.get_x() - block.getWidth() / 2, block.get_y() - block.getHeight() / 2 };
	b[1] = { block.get_x() + block.getWidth() / 2, block.get_y() + block.getHeight() / 2 };
	b[2] = { block.get_x() + block.getWidth() / 2, block.get_y() - block.getHeight() / 2 };
	b[3] = { block.get_x() - block.getWidth() / 2, block.get_y() + block.getHeight() / 2 };

	double grade1 = (double)(b[0].y - b[1].y) / (b[0].x - b[1].x);
	double grade2 = (double)(b[2].y - b[3].y) / (b[2].x - b[3].x);

	double c1 = b[0].y - grade1 * b[0].x;
	double c2 = b[2].y - grade2 * b[2].x;

	bool line1 = true, line2 = true;

	int temp1 = this->get_y() - grade1 * this->get_x() - c1;
	int temp2 = this->get_y() - grade2 * this->get_x() - c2;

	if (temp1 > 0)
		line1 = false;
	if (temp2 > 0)
		line2 = false;

	if (line1 == true && line2 == true)
	{
		this->set_direction(360 - dir);
	}
	if (line1 != true && line2 != true)
	{
		this->set_direction(360 - dir);
	}
	if (line1 != true && line2 == true)
	{
		if (dir < 180)
		{
			this->set_direction(180 - dir);
		}
		else
		{
			this->set_direction(540 - dir);
		}
	}
	if (line1 == true && line2 != true)
	{
		if (dir < 180)
		{
			this->set_direction(180 - dir);
		}
		else
		{
			this->set_direction(540 - dir);
		}
	}
}

void Circle2D::Interpolate(Rectangle2D geo)
{
	int nx = (getRadius() + geo.getWidth() / 2 - abs(this->get_x() - geo.get_x()));
	int ny = (getRadius() + geo.getHeight() / 2 - abs(this->get_y() - geo.get_y()));
	double interpolate = nx > ny ? nx : ny;

	Update(interpolate);
}