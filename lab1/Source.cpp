#include <iostream>

#include "Header.h"

namespace first {

	int input(Line& arr) {
		
		
		arr.n = 0;
		
		while (arr.n < 1){
				std::cout << "Enter number of lines: --> ";
				if (getNum(arr.n) < 0)
					return WRONG_MATRIX;
				if (arr.n < 1)
					std::cout << "u must write integer number more 0,please try ag" << std::endl;
		} 

		arr.m = 0;
		
		while (arr.m < 1) {
				std::cout << "Enter number of columns: --> ";
				if (getNum(arr.m) < 0)
					return WRONG_MATRIX;
				if (arr.m < 1)
					std::cout << "u must write integer number more 0,please try ag" << std::endl;
		}






		try {
			arr.numbers = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return WRONG_MATRIX;
		}

		try {
			arr.column_indexes = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] arr.numbers;
			return WRONG_MATRIX;
		}

		try {
			arr.raw_indexes = new int[BUF_SIZE];
		}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			delete[] arr.numbers;
			delete[] arr.column_indexes;
			return WRONG_MATRIX;
		}


		int matrix_size = 0;
		int count = 0;

		arr.raw_indexes[0] = 0;
		for (int i = 0; i < arr.n; i++) {
			int tmp_size = -1;
			while(tmp_size < 0){
			
				 std::cout << "Enter number of items in line(non zero items) " << (i + 1) << " -- > ";
				
				if (getNum(tmp_size) < 0) {
					//remove(matrix);
					//return 1;
					std::cout << "Enter number of items again ,u must write int more 0" << std:: endl;
					tmp_size = -1;
				}
				if (tmp_size > arr.m) {

					std::cout << "Enter number  smoller columns " << arr.n << std::endl;
					tmp_size = -1;
				}
			} 
			if (tmp_size != 0)
				
				
			for (int j = 0; j < tmp_size; j++) {
				std::cout << "Enter item for matrix line " << (i + 1) << ":";
				int tmp_numbers = 0;
				if (getNum(tmp_numbers) < 0) {
					std::cout << "u mast write int " << std::endl;
					j--;
					continue;
				}
				if (tmp_numbers != 0) {
					arr.numbers[count] = tmp_numbers;


					int tmp_count;
					int position = -1;
					bool  f = 0;
					while (position < 0) {
							std::cout << "Enter position on column:";
							if (getNum(position) < 0) {
								//remove(matrix)
								std::cout << "u mast write int num ,more 0" << std::endl;
								position = -1;
							}
							if (position >= arr.m) {
								std::cout << "your position more that columns:" << arr.m << "write number smoller" << std::endl;
								position = -1;
							}
							//проверка что такой поз не было

							tmp_count = count;
							
							for (count = arr.raw_indexes[i]; count < tmp_count; count++) {
								if (arr.column_indexes[count] == position) {
									std::cout << "prog have this items \nhi is " << arr.numbers[count];
									std::cout << "\nu whant change?y or n (other simvol)\n";
									char a;
									std::cin >> a;
									f = 1;
									if ((a == 'y') || (a == 'Y')) {
										arr.numbers[count] = tmp_numbers;
										j--; 
										
										break;
									}
									else {
										j--;

										break;
									}
								}

							}
							//все норм	
					}
					if(f){
					count = tmp_count;
					}
					else {
					arr.column_indexes[count] = position;
					count++;}

					if (count == matrix_size) {
						matrix_size += BUF_SIZE;
						int* numbers_tmp;
						int* columns_tmp;
						try {
							numbers_tmp = new int[matrix_size];
						}
						catch (std::bad_alloc& ba) {
							std::cout << ba.what() << std::endl;
							//remove(matrix);
							return WRONG_MATRIX;
						}
						try {
							columns_tmp = new int[matrix_size];
						}
						catch (std::bad_alloc& ba) {
							std::cout << ba.what() << std::endl;
							delete[] numbers_tmp;
							//remove(matrix);
							return  WRONG_MATRIX;
						}
						memcpy(numbers_tmp, arr.numbers, (matrix_size - BUF_SIZE) * sizeof(int));
						memcpy(columns_tmp, arr.column_indexes, (matrix_size - BUF_SIZE) * sizeof(int));
						delete[] arr.numbers;
						delete[] arr.column_indexes;
						arr.numbers = numbers_tmp;
						arr.column_indexes = columns_tmp;
						delete[] numbers_tmp;
						delete[] columns_tmp;
					}
				}
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			arr.raw_indexes[i + 1] = count;

		}
		return 0;

	}

	Line  func( const Line & arr) {
		Line New;
		Line tmp;

		try {
			tmp.raw_indexes = new int[arr.n+1];}
		catch (std::bad_alloc& ba) {
			std::cout << ba.what() << std::endl;
			return arr;
		}
		try {
			tmp.column_indexes = new int[arr.raw_indexes[arr.n ]];

			
		}catch (std::bad_alloc& ba) {
			delete[] tmp.raw_indexes;
				std::cout << ba.what() << std::endl;
				return arr;
			}
			
		try {
			tmp.numbers = new int[arr.raw_indexes[arr.n]];


		}
		catch (std::bad_alloc& ba) {
			delete[] tmp.raw_indexes;
			delete[] tmp.column_indexes;
			std::cout << ba.what() << std::endl;
			return arr;
		}

		try {
			
			New.raw_indexes = new int[arr.n + 1];

		}
		catch (std::bad_alloc& ba) {
			delete[] tmp.raw_indexes;
			delete[] tmp.column_indexes;
			delete[] tmp.numbers;
			std::cout << ba.what() << std::endl;
			return arr;
		}
			
		try {


			New.numbers = new int[arr.raw_indexes[arr.n]];

		}
		catch (std::bad_alloc& ba) {
			delete[] New.raw_indexes;
			delete[] tmp.raw_indexes;
			delete[] tmp.column_indexes;
			delete[] tmp.numbers;
			std::cout << ba.what() << std::endl;
			return arr;
		}

		try {

			
			New.column_indexes = new int[arr.raw_indexes[arr.n]];

		}
		catch (std::bad_alloc& ba) {

			delete[] New.numbers;
			delete[] New.raw_indexes;
			delete[] tmp.raw_indexes;
			delete[] tmp.column_indexes;
			delete[] tmp.numbers;
			std::cout << ba.what() << std::endl;
			return arr;
		}



		
		
			
			
			
		int count = 0;
		int min = INT_MAX;
		int min_index= -1;
		int tmp_ind;
		tmp.n = arr.n;
		tmp.m = arr.m;
		New.n = arr.n;
		New.m = arr.m;
		int j = 0;
		memcpy(tmp.numbers, arr.numbers, arr.raw_indexes[arr.n  ] *sizeof(int));
		memcpy(tmp.column_indexes, arr.column_indexes, arr.raw_indexes[arr.n ] *sizeof(int));
		memcpy(tmp.raw_indexes, arr.raw_indexes,( arr.n+1) *sizeof(int));
						
		tmp.raw_indexes[0] = 0;

		for (int i = 0; i < tmp.n; i++) {

			for (count = tmp.raw_indexes[i]; count < tmp.raw_indexes[i + 1]; count++) {

				if (min > tmp.numbers[count]) {
					min = tmp.numbers[count];
					min_index = count;


				}

			}





			if ((min < 0)||( tmp.raw_indexes[i + 1]-tmp.raw_indexes[i] == tmp.n)) {

				std::cout << min_index << "=min1 \n";
				if (tmp.column_indexes[min_index] == 0) {
					for (count = tmp.raw_indexes[i]; count < tmp.raw_indexes[i + 1]; count++) {

						New.numbers[j] = tmp.numbers[count];
						New.column_indexes[j] = tmp.column_indexes[count];
						j++;

					}


				}
				else
					if (min_index != -1) {
						tmp_ind = tmp.column_indexes[min_index];


						for (count = tmp.raw_indexes[i]; count < tmp.raw_indexes[i + 1]; count++) {

							if (count == min_index) {
								New.numbers[j] = tmp.numbers[count];
								New.column_indexes[j] = 0;
								j++;

							}
							else
								if (tmp.column_indexes[count] > tmp_ind) {
									New.numbers[j] = tmp.numbers[count];
									New.column_indexes[j] = tmp.column_indexes[count] - tmp_ind;
									j++;
								}


						}




					}

			}
			else {

				count = tmp.raw_indexes[i];
				for (int k = 0; k < tmp.m; k++) {
					
					while ((tmp.column_indexes[count] != k) && count < tmp.raw_indexes[i + 1]) {

						count++;
					}


					if ((tmp.column_indexes[count] == k) && (count < tmp.raw_indexes[i + 1])) {
						count = tmp.raw_indexes[i];
						continue;
					}
					else {
						min_index = k;
						break;
					}
					
					
				}
				//std::cout<< min_index << "=min \n";
					tmp_ind = min_index;






					if (tmp_ind == 0) {
						for (count = tmp.raw_indexes[i]; count < tmp.raw_indexes[i + 1]; count++) {

							New.numbers[j] = tmp.numbers[count];
							New.column_indexes[j] = tmp.column_indexes[count];
							j++;

						}


					}
					else

					for (count = tmp.raw_indexes[i]; count < tmp.raw_indexes[i + 1]; count++) {

						
							if (tmp.column_indexes[count] > tmp_ind) {
								New.numbers[j] = tmp.numbers[count];
								New.column_indexes[j] = tmp.column_indexes[count] - tmp_ind;
								j++;
							}


					}




			



			}

			min = INT_MAX;
			min_index = -1;
			New.raw_indexes[i+1] = j;
		}





		New.raw_indexes[0] = 0;
		delete[] tmp.numbers;
		delete[] tmp.column_indexes;
		delete[] tmp.raw_indexes;
		return New;
		
	}
		



		
	
	void show(const Line & arr) {
		int count = 0;
		int tmp = 0;
		bool flag = 0;
		int tmp_j = 0;
		int count_printf = 0;
		for (int i = 0; i < arr.n; i++) {
			if (arr.raw_indexes[i + 1] == arr.raw_indexes[i]) {

				for (int j = 0; j < arr.m; j++)
					std::cout << "0 ";
				count = arr.raw_indexes[i + 1];
				count_printf = 0;
			}
			else
			for (int j = 0; j < arr.m; j++) {
				//tmp = count;
				//tmp_j = j;
				while ((arr.column_indexes[count] != j) && count < arr.raw_indexes[i + 1]) {
					
					count++;
				}


				if ((arr.column_indexes[count] == j)&& (count < arr.raw_indexes[i + 1])){
					std::cout << arr.numbers[count] << " ";
					count_printf++;
					
				}
				else
					std::cout << "0 ";


				if (count_printf < arr.raw_indexes[i + 1]) {
					count = arr.raw_indexes[i];
					
				}
				else {
					count = arr.raw_indexes[i+1];
				
				}
			}
			std::cout << std::endl;
		}

		
	}

	void output1(const Line& matrix) {
		std::cout << matrix.raw_indexes[matrix.n] << std::endl;
		for (int i = 0; i < matrix.raw_indexes[matrix.n]; i++) {
			std::cout << matrix.numbers[i] << ", ";
		}
		std::cout << std::endl;
		for (int i = 0; i < matrix.raw_indexes[matrix.n]; i++) {
			std::cout << matrix.column_indexes[i] << ", ";
		}
		std::cout << std::endl;
		for (int i = 0; i < matrix.n + 1; i++) {
			std::cout << matrix.raw_indexes[i] << ", ";
		}
		std::cout << std::endl;
		
	}





	void remove(Line & matrix) {
		delete[] matrix.numbers;
		delete[] matrix.column_indexes;
		delete[] matrix.raw_indexes;
		
	}










}