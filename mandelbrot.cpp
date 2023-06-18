#include <iostream>
#include <vector>
#include "mandelbrot.h"

std::pair<float, float> get_mandelbrot_points(std::pair<float, float> n, float c1, float c2){
	std::cout << c1 << " " << c2 << " "; //Debugging if precision was changed
	return std::pair<float, float>(n.first*n.first - n.second*n.second + c1, 2*n.first*n.second + c2);
}

