#pragma once

class Coord
{
public:
	float x, y;

	Coord() : x(0), y(0) {}
	Coord(float x, float y) : x(x), y(y) {}
	void Show() const;
};

