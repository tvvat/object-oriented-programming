
#pragma once

#include <iostream>
#include  "..\..\Table\Table\Table.h"







namespace Prog3 {
	class Option
	{
	private:
		
		std::istream& is = std::cin;
		std::ostream& os = std::cout;
		Table tab ;
		Table tab2;
		Table tab3;
		bool case_Add_Item();
		bool case_size();
		bool case_maxsize();
		bool case_find();
		bool case_delet();
		bool case_copy();
		bool case_move();
		bool case_show();
		bool case_create();
		bool case_input();
		bool case_plus();
		bool case_cmp();
		bool case_invert();
	public:
		std::istream& choose(std::istream& a= std::cin) {
			return a;
		}
		void print();
		int check();
		
	};



	template <typename T>
	int getNum(T& a)
	{
		std::cin >> a;
		if ((!std::cin.good()) || (std::cin.peek() != '\n')) {

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			return -1;
		}
		return 1;
	}




}
//namespace Dynamic {
//
//
//	class Option
//	{
//	private:
//
//		std::istream& is = std::cin;
//		std::ostream& os = std::cout;
//		Table tab;
//		Table tab2;
//		Table tab3;
//		bool case_Add_Item();
//		bool case_size();
//		bool case_maxsize();
//		bool case_find();
//		bool case_delet();
//		bool case_copy();
//		bool case_move();
//		bool case_show();
//		bool case_create();
//		bool case_input();
//		bool case_plus();
//		bool case_cmp();
//		bool case_invert();
//	public:
//		std::istream& choose(std::istream& a = std::cin) {
//			return a;
//		}
//		void print();
//		int check();
//
//	};
//
//
//
//	template <typename T>
//	int getNum(T& a)
//	{
//		std::cin >> a;
//		if ((!std::cin.good()) || (std::cin.peek() != '\n')) {
//
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//			return -1;
//		}
//		return 1;
//	}
//
//
//	
//
//
//
//
//
//
//
//
//}


