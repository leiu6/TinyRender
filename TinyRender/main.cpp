#include "Screen.h"
#include "Wireframe.h"
#include "WireframePrimitives.h"

#include <chrono>
#include <windows.h>
#include <iostream>

int main()
{
	float frame_rate = 5; // Hz

	Screen screen = Screen(100, 50);

	Wireframe cube = Wireframe();

	Vector corner_a = Vector(-0.5, -0.5, 0.25);
	Vector corner_b = Vector(-0.5, -0.5, 1.25);
	Vector corner_c = Vector(0.5, -0.5, 1.25);
	Vector corner_d = Vector(0.5, -0.5, 0.25);

	Vector corner_e = Vector(-0.5, 0.5, 0.25);
	Vector corner_f = Vector(-0.5, 0.5, 1.25);
	Vector corner_g = Vector(0.5, 0.5, 1.25);
	Vector corner_h = Vector(0.5, 0.5, 0.25);

	cube.AddVerticeSet(corner_a, corner_b);
	cube.AddVerticeSet(corner_b, corner_c);
	cube.AddVerticeSet(corner_c, corner_d);
	cube.AddVerticeSet(corner_d, corner_a);

	cube.AddVerticeSet(corner_e, corner_f);
	cube.AddVerticeSet(corner_f, corner_g);
	cube.AddVerticeSet(corner_g, corner_h);
	cube.AddVerticeSet(corner_h, corner_e);

	cube.AddVerticeSet(corner_a, corner_e);
	cube.AddVerticeSet(corner_b, corner_f);
	cube.AddVerticeSet(corner_c, corner_g);
	cube.AddVerticeSet(corner_d, corner_h);

	// Time per frame in milliseconds
	float time_per_frame = 1 / frame_rate * 1000;
	float total_time = 1;


	float angular_speed = 0.0017; // rad/s

	while (1) {
		auto start_time = std::chrono::high_resolution_clock::now();

		// Code goes here
		screen.Clear();
		std::cout << "Frame Rate: " << 1 / total_time * 1000 << " fps\n";
		screen.DrawWireframe(cube);
		screen.Swap();
		screen.Show();

		cube.Rotate(Vector(0, 0, 0.75), Vector(1.2, 1, 0).Norm(), angular_speed * time_per_frame);

		auto stop_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

		if ((time_per_frame - duration.count()) > 0)
			Sleep(time_per_frame - (DWORD)duration.count());

		auto final_time = std::chrono::high_resolution_clock::now();
		total_time = std::chrono::duration_cast<std::chrono::milliseconds>(final_time - start_time).count();
	}

	return 0;
}
