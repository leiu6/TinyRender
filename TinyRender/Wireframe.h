#pragma once

#include <vector>

#include "Vector.h"

struct Line
{
	unsigned int a;
	unsigned int b;

	Line() : a(0), b(0) {}
	Line(unsigned int a, unsigned int b) : a(a), b(b) {}
};

class Wireframe
{
private:
	std::vector<Vector> vertices;
	std::vector<Line> edges;
	char default_fill;

public:
	Wireframe();

	void AddVerticeSet(Vector start, Vector end);

	void Show() const;

	void Translate(Vector translation);
	void Rotate(Vector origin, Vector axis, float angle);

	unsigned int GetVerticeAssignmentCount() const { return vertices.size(); }
	unsigned int GetEdgeAssignmentCount() const { return edges.size(); }
	char GetDefaultFill() const { return default_fill; }
	const Line& GetEdge(unsigned int i) const { return edges[i]; }
	const Vector& GetVertice(unsigned int i) const { return vertices[i]; }
};

