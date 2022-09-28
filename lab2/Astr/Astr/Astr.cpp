// Astr.cpp : Определяет функции для статической библиотеки.
//

#include <iostream>
#include <cmath>
#include "Astr.h"

namespace Astr1 {


	void Line::set_radius(double input_radius) {
		if (input_radius < 0) {
			throw std::exception("Bad radius");

		}
		else
			radius = input_radius;
	}
	double Line::distance(double t) const {
		return 3 * radius * sin(t) * sin(t) / 2;
	}
	double Line::area() const {
		return  3 * PI * radius * radius / 8;

	}

	double Line::curvature(double t) const {
		return	(3 * radius * sin(2 * t)) / 2;
	}

	void Line::coordinates(double t)const {

		std::cout << "x =" << radius * (sin(t)) * (sin(t)) * (sin(t)) << std::endl;

		std::cout << "y =" << radius * (cos(t)) * (cos(t)) * (cos(t)) << std::endl;
	}


	double Line::coordinates_dec(double x)const {

		return pow(radius, 1.5) - pow(x, 1.5);
	}



	Line::Line(double input_radius) {
		if (input_radius < 0) {
			throw std::exception("invalid radius");
		}
		else radius = input_radius;
	}
}
