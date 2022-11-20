#include "Wireframe.h"
#include "Vector.h"

#include <iostream>
#include <vector>

Wireframe::Wireframe()
{
	default_fill = '#';
}

void Wireframe::AddVerticeSet(Vector start, Vector end)
{
	// Detect if items are in vertices
	if (!std::count(vertices.begin(), vertices.end(), start))
		vertices.push_back(start);

	if (!std::count(vertices.begin(), vertices.end(), end))
		vertices.push_back(end);

	// Create the edge
	int start_indice = std::find(vertices.begin(), vertices.end(), start) - vertices.begin();
	int end_indice = std::find(vertices.begin(), vertices.end(), end) - vertices.begin();
	edges.push_back(Line(start_indice, end_indice));
}

void Wireframe::Show() const
{
	std::cout << "Wireframe:\n";
	std::cout << "Total added vertices: " << vertices.size() << "\n";
	std::cout << "Total added edges: " << edges.size() << "\n";
	std::cout << "\n";

	for (int i = 0; i < vertices.size(); i++) {
		std::cout << "Vertice #" << i + 1 << ": ";
		vertices[i].Show();
	}
}

void Wireframe::Translate(Vector translation)
{
	for (int i = 0; i < vertices.size(); i++)
		vertices[i] = vertices[i] + translation;
}

void Wireframe::Rotate(Vector origin, Vector axis, float angle)
{
	for (int i = 0; i < vertices.size(); i++) {
		// Move vertice to origin
		vertices[i] = vertices[i] - origin;

		// Apply rotation
		vertices[i] = vertices[i].Rotate(axis, angle);

		// Move back to where it was
		vertices[i] = vertices[i] + origin;
	}
}


/* PRIVATE */
