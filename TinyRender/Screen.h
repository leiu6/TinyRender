#pragma once

#include "Coord.h"
#include "Vector.h"
#include "Wireframe.h"

class Screen
{
private:
	char* fb;
	char* bb;
	unsigned int width;
	unsigned int height;
	unsigned int size;
	char default_fill;
	float focal_length;

	Coord ProjectToScreen(Vector vector) const;
	Coord FromNormalizedToScreen(Coord normalized) const;
	void DrawLineBresenham(Coord start, Coord end, char fill);
	char* GrabFrontBufferRow(unsigned int row) const;

public:
	Screen(unsigned int width, unsigned int height);
	~Screen();

	void Clear();
	void Swap();
	void Write(Coord position, char pixel);
	void Show() const;
	void DrawWireframe(const Wireframe& wireframe);

	void SetFocalLength(float focal_length) { this->focal_length = focal_length; }
};

