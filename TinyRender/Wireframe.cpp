#include "Wireframe.h"
#include "Vector.h"

#include <iostream>

Wireframe::Wireframe(unsigned int num_vertices, unsigned int num_edges)
{
	_vertices_assignment_count = 0;
	_edges_assignment_count = 0;

	this->num_vertices = num_vertices;
	this->num_edges = num_edges;
	this->vertices = new Vector[num_vertices];
	this->edges = new Line[num_edges];
	this->default_fill = '@';
}

Wireframe::~Wireframe()
{
	delete[] vertices;
	delete[] edges;
}

void Wireframe::AddVertice(Vector vertice)
{
	// If we have already added the max number of vertices don't
	// try to add another one.
	if (_vertices_assignment_count >= num_vertices) return;

	vertices[_vertices_assignment_count] = vertice;

	_vertices_assignment_count++;
}

void Wireframe::AddEdge(unsigned int start_indice, unsigned int end_indice)
{
	if (_edges_assignment_count >= num_edges) return;

	edges[_edges_assignment_count] = Line(start_indice, end_indice);

	_edges_assignment_count++;
}

void Wireframe::Show() const
{
	std::cout << "Wireframe:\n";
	std::cout << "Total allocated vertices: " << num_vertices << "\n";
	std::cout << "Total added vertices: " << _vertices_assignment_count << "\n";
	std::cout << "Total allocated edges: " << num_edges << "\n";
	std::cout << "Total added edges: " << _edges_assignment_count << "\n";
	std::cout << "\n";

	for (int i = 0; i < num_vertices; i++) {
		std::cout << "Vertice #" << i + 1 << ": ";
		vertices[i].Show();
	}
}

void Wireframe::Translate(Vector translation)
{
	for (int i = 0; i < num_vertices; i++)
		vertices[i] = vertices[i] + translation;
}

void Wireframe::Rotate(Vector origin, Vector axis, float angle)
{
	for (int i = 0; i < num_vertices; i++) {
		// Move vertice to origin
		vertices[i] = vertices[i] - origin;

		// Apply rotation
		vertices[i] = vertices[i].Rotate(axis, angle);

		// Move back to where it was
		vertices[i] = vertices[i] + origin;
	}
}
