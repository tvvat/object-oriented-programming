
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cmath>
#include"..\..\Astr\Astr\Astr.h"
 // LINE_H

//MENU_H
namespace Astr1{
class Option
{
private:
	Line line;

	std::istream& is = std::cin;
	std::ostream& os = std::cout; 

	bool case_rad();
	bool case_dist();
	bool case_5();
	bool case_radcruv();
	bool case_len();
	bool case_coordin();
	bool case_coordin_dec();

public:
	void print();
	int check();
	bool fg(std::istream& a) {
		is = a;
		return 1;
	}
	template <typename T>
	int getNum(T& a) {
		is >> a;
		if (!is.good()) {

			is.clear();
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return -1;
		}

		is.clear();
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return 1;
	}

};

}

#endif



























