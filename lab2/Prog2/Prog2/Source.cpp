#include <iostream>
#include <cmath>
#include "header.h"

#include"..\..\Astr\Astr\Astr.h"
#include <math.h>
#define _USE_MATH_DEFINES
namespace Astr1 {
	void Option::print() {

		std::cout << "MENU FOR WORK WITH ASTROIDA\n";
		std::cout << "Current radius: " << line.get_radius() << std::endl;
		std::cout << "0) Quit \n";
		std::cout << "1) Set radius\n";
		std::cout << "2) Count distance\n";
		std::cout << "3) Count length\n";
		std::cout << "4) Count radius of curvature\n";
		std::cout << "5) Count area\n";
		std::cout << "6) Coordinate t \n";
		std::cout << "7) Coordinate x \n";

	}
	int Option::check() {

		int flag = -1;
		while (flag == -1) {
			std::cout << "Enter answer: -->" << std::endl;
			if ((getNum(flag) < 0) || (flag < 0) || (flag > 6)) {
				std::cout << "u are wrong please repeat" << std::endl;
				flag = -1;
			}
		}

		if (flag == 1) {
			return case_rad();
		}
		else if (flag == 2) {
			return case_dist();
		}
		else if (flag == 3) {
			return case_len();
		}
		else if (flag == 4) {
			return case_radcruv();
		}
		else if (flag == 5) {
			return case_5();
		}
		else if (flag == 6) {
			return case_coordin();
		}
		else if (flag == 7) {
			return case_coordin_dec();
		}

		return flag;

	}

	bool Option::case_rad() {
		double input_radius;
		os << "Enter radius [ >= 0 ]: --> ";
		int status = getNum(input_radius);
		if (status) {
			try {
				line.set_radius(input_radius);
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
			}
		}

		return 1;
	}


	bool Option::case_dist() {
		double  t;
		os << "Enter tangle [ >= 0 ]: --> " << std::endl;
		int status = getNum(t);
		if (status)
			std::cout << line.distance(t) << std::endl;

		return 1;
	}



	double Line::length() const {
		return 6.0 * radius;

	}

	bool Option::case_len() {

		os << line.length();

		return 1;
	}




	bool Option::case_5() {

		std::cout << line.area() << std::endl;

		return 1;
	}


	bool Option::case_radcruv() {
		double t;

		os << "Enter tangle [ >= 0 ]: --> " << std::endl;
		int status1 = getNum(t);

		if (status1) std::cout << line.curvature(t) << std::endl;

		return 1;
	}


	bool Option::case_coordin() {
		double t;

		os << "Enter tangle [ >= 0 ]: --> " << std::endl;
		int status1 = getNum(t);

		if (status1)
			line.coordinates(t);

		return 1;
	}

	bool Option::case_coordin_dec() {
		double x;

		int status1 = getNum(x);

		if (status1)
			os << line.coordinates_dec(x);

		return 1;
	}

}
