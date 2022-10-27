

#include"Diol.h"
#include <iostream>
#include <string>
#include  "..\..\Table\Table\Table.h"

namespace Prog3 {

	



	void Option::print() {

		os << "MENU FOR WORK WITH Table\n";
		os << "0) Quit \n";
		os << "1) Add Item\n";
		os << "2) return Size\n";
		os << "3) return Maxsize\n";
		os << "4) find Item\n";
		os << "5) Delet Item\n";
		os << "6) Copy Table \n";
		os << "7) Move Table \n";
		os << "8) Show Table \n";
		os << "10) into stream \n";
		os << "11)cmp \n";

	}
	int Option::check() {

		int flag = -1;
		while (flag == -1) {
			os << "Enter answer: -->" << std::endl;
			if ((getNum(flag) < 0) || (flag < 0) || (flag > 13)) {
				os << "u are wrong please repeat" << std::endl;
				flag = -1;
			}
		}

		if (flag == 1) {
			return case_Add_Item();
		}
		else if (flag == 2) {
			return case_size();
		}
		else if (flag == 3) {
			return case_maxsize();
		}
		else if (flag == 4) {
			return case_find();
		}
		else if (flag == 5) {
			return case_delet();
		}
		else if (flag == 6) {
			return case_copy();
		}
		else if (flag == 7) {
			return case_move();
		}
		else if (flag == 8) {
			return case_show();
		}
		else if (flag == 9) {
			return case_create();
		}
		else if (flag == 10) {
			return case_input();
		}
		else if (flag == 11) {
			return case_plus();
		}
		else if (flag == 12) {
			return case_cmp();
		}
		else if (flag == 12) {
			return case_cmp();
		}
		else if (flag == 13) {
			return case_invert();
		}
		return flag;

	}









	bool Option::case_Add_Item(){
		int key;
		os << "Enter key >= 0 : --> ";
		int status = getNum(key);


		os << "Enter info (maxlen" <<tab.getMaxSize() << ")--> ";
		char info[10];
		is >> info;

		if (status) {
			try {
				tab.add(key,info);
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
			}
		}

		return 1;
	}

	bool Option::case_size() {
		os <<tab.getSize();
		return 1;
	}

	bool Option::case_maxsize() {
		os << tab.getMaxSize();
		return 1;
	}
	bool Option::case_find() {
		int key;
		os << "Enter key >= 0 : --> ";
		int status = getNum(key);
	

		if (status) {
			try {
				os << tab.find(key)<<std::endl;
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
			}
		}



		return 1;
	}


	bool Option::case_delet() {
		int key;
		os << "Enter key >= 0 : --> ";
		int status = getNum(key);

		os << "Enter info (maxlen " << tab.getMaxSize() << ")--> ";
		char info[10];
		is >> info;

		if (status) {
			try {
				if (!tab.delet(key, info)){
					os << "successful";
					tab = tab.reconst();
				}
			}
			catch (const std::exception& msg) {
				os << msg.what() << std::endl;
			}
		}



		return 1;
	}

	bool Option::case_show() {

		tab.show(os);
		return 1;
	}

	bool Option::case_copy() {
		tab2 = tab.copy(tab);
		tab2.show(os);
		return 1;
	

	}

	bool Option::case_move() {
		tab2 = tab.move();
		tab2.show(os);
		return 1;
	}



	bool Option::case_create() {


		os << "entr n a[i]  s[i]" <<std:: endl;
		int n;
		getNum(n);
		if (n < 1) {
		 os << "n < 0:tru again" << std:: endl;
			return 1;
		}
		int* a = new int[n];
		char** info = new char*[n];
		for (int i = 0; i < n; i++) {

			getNum(a[i]);
			info[i] = new char[10];
			is >> info[i];
		}
		Table lin(n, a, info);
		lin.show(os);
		return 1;
	}

	bool Option::case_input() {


		os << "entr key then inf" << std::endl;
		tab.input(is);
		return 1;
	}


	bool Option::case_plus() {

		os << "entr n a[i]  s[i]" << std::endl;
		int n;
		getNum(n);
		if (n < 1) {
			os << "n < 0:tru again" << std::endl;
			return 1;
		}
		int* a = new int[n];
		char** info = new char* [n];
		for (int i = 0; i < n; i++) {

			getNum(a[i]);
			info[i] = new char[10];
			is >> info[i];
		}
		Table t(n, a, info);

		os << "entr n a[i]  s[i]" << std::endl;
		int m;
		getNum(m);
		if (m < 1) {
			os << "n < 0:tru again" << std::endl;
			return 1;
		}
		int* b = new int[m];
		char** s = new char* [m];
		for (int i = 0; i < m; i++) {

			getNum(b[i]);
			s[i] = new char[10];
			is >> s[i];
		}
		
		Table t2(m, b, s);
		t += t2;
		t.show(os);
		std::cout << "------" << std::endl;
		t2.show(os);
		Table t3(n,a,info);
		Table t4;
		t4 = t3 + t2;
		t4.show(os);
		std::cout << "------" << std::endl;
		t3.show(os);
		std::cout << "------" << std::endl;
		t2.show(os);

		return 1;
	}

	bool Option::case_cmp() {

		os << "entr n a[i]  s[i]" << std::endl;
		int n;
		getNum(n);
		if (n < 1) {
			os << "n < 0:tru again" << std::endl;
			return 1;
		}
		int* a = new int[n];
		char** info = new char* [n];
		for (int i = 0; i < n; i++) {

			getNum(a[i]);
			info[i] = new char[10];
			is >> info[i];
		}
		Table t(n, a, info);

		os << "entr n a[i]  s[i]" << std::endl;
		int m;
		getNum(m);
		if (m < 1) {
			os << "n < 0:tru again" << std::endl;
			return 1;
		}
		int* b = new int[m];
		char** s = new char* [m];
		for (int i = 0; i < m; i++) {

			getNum(b[i]);
			s[i] = new char[10];
			is >> s[i];
		}

		Table t2(m, b, s);
		if (t2 == t) { os << "full"; }
		else
		os <<" bad";




		return 1;
	}

	bool Option::case_invert() {

		os << "entr n a[i]  s[i]" << std::endl;
		int m;
		getNum(m);
		if (m < 1) {
			os << "n < 0:tru again" << std::endl;
			return 1;
		}
		int* b = new int[m];
		char** s = new char* [m];
		for (int i = 0; i < m; i++) {

			getNum(b[i]);
			s[i] = new char[10];
			is >> s[i];
		}

		Table t2(m, b, s);
		~t2;
		
		t2.show(std::cout);


	}




}









//
//namespace Dynamic {
//
//
//
//
//	void Option::print() {
//
//		os << "MENU FOR WORK WITH Table\n";
//		os << "0) Quit \n";
//		os << "1) Add Item\n";
//		os << "2) return Size\n";
//		os << "3) return Maxsize\n";
//		os << "4) find Item\n";
//		os << "5) Delet Item\n";
//		os << "6) Copy Table \n";
//		os << "7) Move Table \n";
//		os << "8) Show Table \n";
//		os << "10) into stream \n";
//		os << "11)cmp \n";
//
//	}
//	int Option::check() {
//
//		int flag = -1;
//		while (flag == -1) {
//			os << "Enter answer: -->" << std::endl;
//			if ((getNum(flag) < 0) || (flag < 0) || (flag > 13)) {
//				os << "u are wrong please repeat" << std::endl;
//				flag = -1;
//			}
//		}
//
//		if (flag == 1) {
//			return case_Add_Item();
//		}
//		else if (flag == 2) {
//			return case_size();
//		}
//		else if (flag == 3) {
//			return case_maxsize();
//		}
//		else if (flag == 4) {
//			return case_find();
//		}
//		else if (flag == 5) {
//			return case_delet();
//		}
//		else if (flag == 6) {
//			return case_copy();
//		}
//		else if (flag == 7) {
//			return case_move();
//		}
//		else if (flag == 8) {
//			return case_show();
//		}
//		else if (flag == 9) {
//			return case_create();
//		}
//		else if (flag == 10) {
//			return case_input();
//		}
//		else if (flag == 11) {
//			return case_plus();
//		}
//		else if (flag == 12) {
//			return case_cmp();
//		}
//		else if (flag == 12) {
//			return case_cmp();
//		}
//		else if (flag == 13) {
//			return case_invert();
//		}
//		return flag;
//
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
//	bool Option::case_Add_Item() {
//		int key;
//		os << "Enter key >= 0 : --> ";
//		int status = getNum(key);
//
//
//		os << "Enter info (maxlen" << tab.getMaxSize() << ")--> ";
//		char *info = get_str(is);
//		
//
//		if (status) {
//			try {
//				tab.add(key, info);
//			}
//			catch (const std::exception& msg) {
//				os << msg.what() << std::endl;
//			}
//		}
//
//		return 1;
//	}
//
//	bool Option::case_size() {
//		os << tab.getSize();
//		return 1;
//	}
//
//	bool Option::case_maxsize() {
//		os << tab.getMaxSize();
//		return 1;
//	}
//	bool Option::case_find() {
//		int key;
//		os << "Enter key >= 0 : --> ";
//		int status = getNum(key);
//
//
//		if (status) {
//			try {
//				os << tab.find(key) << std::endl;
//			}
//			catch (const std::exception& msg) {
//				os << msg.what() << std::endl;
//			}
//		}
//
//
//
//		return 1;
//	}
//
//
//	bool Option::case_delet() {
//		int key;
//		os << "Enter key >= 0 : --> ";
//		int status = getNum(key);
//
//		os << "Enter info (maxlen " << tab.getMaxSize() << ")--> ";
//		char *info= get_str(is);
//	
//
//		if (status) {
//			try {
//				if (!tab.delet(key, info)) {
//					os << "successful";
//					tab = tab.reconst();
//				}
//			}
//			catch (const std::exception& msg) {
//				os << msg.what() << std::endl;
//			}
//		}
//
//
//
//		return 1;
//	}
//
//	bool Option::case_show() {
//
//		tab.show(os);
//		return 1;
//	}
//
//	bool Option::case_copy() {
//		tab2 = tab.copy(tab);
//		tab2.show(os);
//		return 1;
//
//
//	}
//
//	bool Option::case_move() {
//		tab2 = tab.move();
//		tab2.show(os);
//		return 1;
//	}
//
//
//
//	bool Option::case_create() {
//
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int n;
//		getNum(n);
//		if (n < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* a = new int[n];
//		char** info = new char* [n];
//		for (int i = 0; i < n; i++) {
//
//			getNum(a[i]);
//			info[i] = get_str(is);
//		}
//		Table lin(n, a, info);
//		lin.show(os);
//		return 1;
//	}
//
//	bool Option::case_input() {
//
//
//		os << "entr key then inf" << std::endl;
//		tab.input(is);
//		return 1;
//	}
//
//
//	bool Option::case_plus() {
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int n;
//		getNum(n);
//		if (n < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* a = new int[n];
//		char** info = new char* [n];
//		for (int i = 0; i < n; i++) {
//
//			getNum(a[i]);
//			info[i] = new char[10];
//			is >> info[i];
//		}
//		Table t(n, a, info);
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int m;
//		getNum(m);
//		if (m < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* b = new int[m];
//		char** s = new char* [m];
//		for (int i = 0; i < m; i++) {
//
//			getNum(b[i]);
//			s[i] = get_str(is);
//			
//		}
//
//		Table t2(m, b, s);
//		t += t2;
//		t.show(os);
//		std::cout << "------" << std::endl;
//		t2.show(os);
//		Table t3(n, a, info);
//		Table t4;
//		t4 = t3 + t2;
//		t4.show(os);
//		std::cout << "------" << std::endl;
//		t3.show(os);
//		std::cout << "------" << std::endl;
//		t2.show(os);
//
//		return 1;
//	}
//
//	bool Option::case_cmp() {
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int n;
//		getNum(n);
//		if (n < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* a = new int[n];
//		char** info = new char* [n];
//		for (int i = 0; i < n; i++) {
//
//			getNum(a[i]);
//			info[i] = get_str(is);
//		}
//		Table t(n, a, info);
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int m;
//		getNum(m);
//		if (m < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* b = new int[m];
//		char** s = new char* [m];
//		for (int i = 0; i < m; i++) {
//
//			getNum(b[i]);
//			s[i] = get_str(is);
//			
//		}
//
//		Table t2(m, b, s);
//		if (t2 == t) { os << "full"; }
//		else
//			os << " bad";
//
//
//
//
//		return 1;
//	}
//
//	bool Option::case_invert() {
//
//		os << "entr n a[i]  s[i]" << std::endl;
//		int m;
//		getNum(m);
//		if (m < 1) {
//			os << "n < 0:tru again" << std::endl;
//			return 1;
//		}
//		int* b = new int[m];
//		char** s = new char* [m];
//		for (int i = 0; i < m; i++) {
//
//			getNum(b[i]);
//			s[i] = get_str(is);
//		}
//
//		Table t2(m, b, s);
//		~t2;
//
//		t2.show(std::cout);
//
//
//	}
//
//
//
//}