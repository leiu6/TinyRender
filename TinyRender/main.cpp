#include "Screen.h"
#include "Wireframe.h"

#include <chrono>
#include <windows.h>
#include <iostream>

int main()
{
	float frame_rate = 1; // Hz

	Screen screen = Screen(100, 60);

	Wireframe cube = Wireframe(8, 12);

	cube.AddVertice(Vector(-0.5, -0.5, 0.25));
	cube.AddVertice(Vector(-0.5, -0.5, 1.25));
	cube.AddVertice(Vector(0.5, -0.5, 1.25));
	cube.AddVertice(Vector(0.5, -0.5, 0.25));

	cube.AddVertice(Vector(-0.5, 0.5, 0.25));
	cube.AddVertice(Vector(-0.5, 0.5, 1.25));
	cube.AddVertice(Vector(0.5, 0.5, 1.25));
	cube.AddVertice(Vector(0.5, 0.5, 0.25));

	cube.AddEdge(0, 1);
	cube.AddEdge(1, 2);
	cube.AddEdge(2, 3);
	cube.AddEdge(3, 0);

	cube.AddEdge(4, 5);
	cube.AddEdge(5, 6);
	cube.AddEdge(6, 7);
	cube.AddEdge(7, 4);

	cube.AddEdge(0, 4);
	cube.AddEdge(1, 5);
	cube.AddEdge(2, 6);
	cube.AddEdge(3, 7);

	// Time per frame in milliseconds
	float time_per_frame = 1 / frame_rate * 1000;
	float total_time = 1;

	while (1) {
		auto start_time = std::chrono::high_resolution_clock::now();

		// Code goes here
		screen.Clear();
		std::cout << "Frame Rate: " << 1 / total_time * 1000 << " fps\n";
		screen.DrawWireframe(cube);
		screen.Swap();
		screen.Show();

		cube.Rotate(Vector(0, 0, 0.75), Vector(1.2, 1, 0).Norm(), 0.3);

		auto stop_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_time - start_time);

		if ((time_per_frame - duration.count()) > 0)
			Sleep(time_per_frame - (DWORD)duration.count());

		auto final_time = std::chrono::high_resolution_clock::now();
		total_time = std::chrono::duration_cast<std::chrono::milliseconds>(final_time - start_time).count();
	}

	return 0;
}
