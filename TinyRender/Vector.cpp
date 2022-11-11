#include "Vector.h"

#include <iostream>
#include <cmath>

void Vector::Show() const
{
	std::cout << "Vector <" << x << ", " << y << ", " << z << ">\n";
}

Vector Vector::operator+(const Vector& input) const
{
	return Vector(
		x + input.x,
		y + input.y,
		z + input.z
	);
}

Vector Vector::operator-(const Vector& input) const
{
	return Vector(
		x - input.x,
		y - input.y,
		z - input.z
	);
}

Vector Vector::Rotate(Vector axis, float angle) const
{
	float ux = axis.x;
	float uy = axis.y;
	float uz = axis.z;
	float cos = std::cosf(angle);
	float sin = std::sinf(angle);

	float x_prime, y_prime, z_prime;

	x_prime = (cos + ux * ux * (1 - cos)) * x
		+ (ux * uy * (1 - cos) - uz * sin) * y
		+ (ux * uz * (1 - cos) + uy * sin) * z;

	y_prime = (uy * ux * (1 - cos) + uz * sin) * x
		+ (cos + uy * uy * (1 - cos)) * y
		+ (uy * uz * (1 - cos) - ux * sin) * z;

	z_prime = (uz * ux * (1 - cos) - uy * sin) * x
		+ (uz * uy * (1 - cos) + ux * sin) * y
		+ (cos + uz * uz * (1 - cos)) * z;

	return Vector(
		x_prime,
		y_prime,
		z_prime
	);
}

float Vector::Mag() const
{
	return std::sqrtf(x*x + y*y + z*z);
}

Vector Vector::Norm() const
{
	float length = this->Mag();

	return Vector(
		x / length,
		y / length,
		z / length
	);
}
