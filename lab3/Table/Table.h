#pragma once

#include <iostream>
#include <string>


namespace Prog3 {
	struct Item {
		static const int inf = 10;
		int key;
		int busy;
		char info[inf];
	};
	class Table {
	private:
		
		static const int SZ = 10; // 
		int size;
		Item tab[SZ];
		
		int hash(const int key) const {
			return (key + 137) % SZ;
		};
	public:
	

		explicit Table(int n = 0, int* key = nullptr, char* info[10] = nullptr);

		int add( int,const char*);
		int delet(int, char*);
		char* find( int ) const;
		char** findchoosing(int ,int &) const;
		Table& reconst();
		std::istream& input(std::istream& );
		std::ostream& show(std::ostream& )const noexcept ;
		
		Table& copy(const Table& st) noexcept;
		Table& move() noexcept;

		int getSize() const noexcept{ return size; }
		int getMaxSize() const noexcept{ return SZ; }

		friend std::ostream& operator <<(std::ostream&, const Table&);
		friend std::istream& operator >>(std::istream&, Table&);
		//friend Table operator +(Table , const Table&);
		Table operator +(const Table&) const;
		Table& operator +=(const Table&);
		Table& operator =(const Table&);
		
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
	};
}
//namespace Dynamic {
//	char* get_str(std::istream& );
//	struct Item {
//		int key;
//		int busy;
//		char *info;
//	};
//	class Table {
//	private:
//
//		static const int Quota = 10; // 
//		int size;
//		int count_busy;
//		Item *tab;
//
//		int hash(const int key) const {
//			return (key + 137) % size;
//		};
//	public:
//	/*	
//		Table (const Table& st) :size(st.size), count_busy(st.count_busy)
//		{
//			this->tab = new Item[st.size];
//			for (int i = 0; i < size; i++) {
//				if (st.tab[i].busy == 1) {
//					tab[i].info = new char[strlen(st.tab[i].info) + 1];
//					memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
//				}
//				tab[i].key = st.tab[i].key;
//				tab[i].busy = st.tab[i].busy;
//			}
//			this->size = size;
//			this->count_busy = count_busy;
//			
//		
//		}
//	
//		Table (Table&& st) :size(st.size), count_busy(st.count_busy)
//		{
//			this->tab = new Item[st.size];
//			for (int i = 0; i < size; i++) {
//				if (st.tab[i].busy == 1) {
//					tab[i].info = new char[strlen(st.tab[i].info) + 1];
//					memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
//				}
//				tab[i].key = st.tab[i].key;
//				tab[i].busy = st.tab[i].busy;
//			}
//			st.tab = nullptr;
//		}*/
//
//		explicit Table(int n = 0, int* key = nullptr, char** info= nullptr);
//
//		int add(int, const char*);
//		int delet(int, char*);
//		char* find(int) const;
//		char** findchoosing(int, int&) const;
//		Table& reconst();
//		std::istream& input(std::istream&);
//		std::ostream& show(std::ostream&)const noexcept;
//
//		Table& copy(const Table& st) noexcept;
//		Table& move() noexcept;
//
//		int getSize() const noexcept { return count_busy; }
//		int getMaxSize() const noexcept { return size; }
//
//		friend std::ostream& operator <<(std::ostream&, const Table&);
//		friend std::istream& operator >>(std::istream&, Table&);
//		//friend Table operator +(Table , const Table&);
//		Table operator +(const Table&) const;
//		Table& operator +=(const Table&);
//		Table& operator =(const Table&);
//
//		Table operator ~()const;
//		Table& operator --();
//		Table operator --(int);
//
//		bool operator ==(const Table&);
//
//		//int a = (int)t;
//		operator int();
//		// a[i]= b
//		//b=a[i]
//		Item operator[] (int)const;
//		Item& operator[] (int);
//	};
//
//}
