#pragma once
#include <iostream>
#include <string>

namespace Dynamic {
	char* get_str(std::istream&);
	struct Item {
		int key;
		int busy;
		char* info;
	};
	class Table {
	private:

		static const int Quota = 10; // 
		int size;
		int count_busy;
		Item* tab;

		int hash(const int key) const {
			return (key + 137) % size;
		};
	public:

		Table(const Table&)noexcept;
		Table(Table&&)noexcept;

		explicit Table(int n = 0, int* key = nullptr, char** info = nullptr);

		int add(int, const char*);
		int delet(int, char*);
		char* find(int) const;
		char** findchoosing(int, int&) const;
		Table& reconst();
		std::istream& input(std::istream&);
		std::ostream& show(std::ostream&)const noexcept;

		Table& copy(const Table& st) noexcept;
		Table& move() noexcept;

		int getSize() const noexcept { return count_busy; }
		int getMaxSize() const noexcept { return size; }

		friend std::ostream& operator <<(std::ostream&, const Table&);
		friend std::istream& operator >>(std::istream&, Table&);
		//friend Table operator +(Table , const Table&);
		Table operator +(const Table&) const;
		Table& operator +=(const Table&);
		Table& operator =(const Table&);
		Table& operator =(Table&& );

		Table operator ~()const;
		Table& operator --();
		Table operator --(int);

		bool operator ==(const Table&);

		//int a = (int)t;
		operator int();
		// a[i]= b
		//b=a[i]
		Item operator[] (int)const;
		Item& operator[] (int);
		~Table();
	};

}