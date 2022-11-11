#pragma once

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
	unsigned int _vertices_assignment_count;
	unsigned int _edges_assignment_count;

public:
	Vector* vertices;
	Line* edges;
	unsigned int num_vertices;
	unsigned int num_edges;
	char default_fill;

	Wireframe(unsigned int num_vertices, unsigned int num_edges);
	~Wireframe();

	void AddVertice(Vector vertice);
	void AddEdge(unsigned int start_indice, unsigned int end_indice);

	void Show() const;

	void Translate(Vector translation);
	void Rotate(Vector origin, Vector axis, float angle);
};

