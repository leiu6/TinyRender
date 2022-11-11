#pragma once
class Vector
{
public:
	float x, y, z;

	Vector() : x(0), y(0), z(0) {}
	Vector(float x, float y, float z) : x(x), y(y), z(z) {}
	void Show() const;

	Vector operator+(const Vector& input) const;
	Vector operator-(const Vector& input) const;
	Vector Rotate(Vector axis, float angle) const;
	float Mag() const;
	Vector Norm() const;
};

