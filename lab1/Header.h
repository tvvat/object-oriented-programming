#ifndef HEADER_H
#include <iostream>

#define HEADER_H
#define BUF_SIZE 80
#define WRONG_MATRIX 1
#define WRONG_WORK 1

namespace first {

	struct Line {
		int n;
		int m;
		int* numbers;
		int* column_indexes;
		int* raw_indexes;
		
	};

	template <class T> 
	
	int getNum( T & a )
	{
		std::cin >> a;
		if( (!std::cin.good()) || (std::cin.peek() != '\n')) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return -1;
		}
		return 1;
	}



	int input (Line& );
	Line func(const Line& );
	void show(const Line& );
	void output1(const Line &);
	void remove(Line& );

}
#endif
