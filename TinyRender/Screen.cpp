#include "Screen.h"
#include "Coord.h"
#include "Vector.h"
#include "Wireframe.h"

#include <cmath>
#include <iostream>
#include <string>

#define LOG(str) std::cout << str << "\n";

Coord Screen::ProjectToScreen(Vector vector) const
{
	float x_proj = (vector.x * focal_length) / (focal_length + vector.z);
	float y_proj = (vector.y * focal_length) / (focal_length + vector.z);

	return Coord(x_proj, y_proj);
}

Coord Screen::FromNormalizedToScreen(Coord normalized) const
{
	float x_screen = std::roundf((normalized.x / 2 + 0.5) * (width - 1));
	float y_screen = std::roundf((-normalized.y / 2 + 0.5) * (height - 1));

	return Coord(x_screen, y_screen);
}

void Screen::DrawLineBresenham(Coord start, Coord end, char fill)
{
	// Uses Bresenham's method to draw a line
	//
	// Code from: https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

	float y0 = start.y;
	float y1 = end.y;
	float x0 = start.x;
	float x1 = end.x;

	float dx = std::abs(x1 - x0);
	float sx = x0 < x1 ? 1 : -1;
	float dy = -std::abs(y1 - y0);
	float sy = y0 < y1 ? 1 : -1;
	float error = dx + dy;

	while (1) {
		bb[(int)(width * y0 + x0)] = fill;

		if (x0 == x1 && y0 == y1) break;

		float e2 = 2 * error;

		if (e2 >= dy) {
			if (x0 == x1) break;
			error += dy;
			x0 += sx;
		}

		if (e2 <= dx) {
			if (y0 == y1) break;
			error += dx;
			y0 += sy;
		}
	}
}

Screen::Screen(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	this->size = width * height;
	this->default_fill = ' ';
	this->focal_length = 2;
	this->fb = new char[size];
	this->bb = new char[size];
}

Screen::~Screen()
{
	delete[] fb;
	delete[] bb;
}

void Screen::Clear()
{
	system("cls");

	for (int i = 0; i < size; i++)
		bb[i] = default_fill;
}

void Screen::Swap()
{
	for (int i = 0; i < size; i++)
		fb[i] = bb[i];
}

void Screen::Write(Coord position, char pixel)
{
	position = FromNormalizedToScreen(position);

	if (position.x > width - 1) return;
	if (position.y > height - 1) return;

	bb[(int)(width * position.y + position.x)] = pixel;
}

void Screen::Show() const
{
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			std::cout << fb[(int)(width * row + col)];
		}

		std::cout << "\n";
	}
}

void Screen::DrawWireframe(const Wireframe& wireframe)
{
	// That way we only have to complete the projection calculations once
	Coord* projected = new Coord[wireframe.num_vertices];

	for (int i = 0; i < wireframe.num_vertices; i++) {
		projected[i] = ProjectToScreen(wireframe.vertices[i]);
		projected[i] = FromNormalizedToScreen(projected[i]);

		Write(projected[i], wireframe.default_fill);
	}

	for (int i = 0; i < wireframe.num_edges; i++)
		DrawLineBresenham(projected[wireframe.edges[i].a], projected[wireframe.edges[i].b], wireframe.default_fill);

	delete[] projected;
}
