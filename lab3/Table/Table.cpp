// Table.cpp : Определяет функции для статической библиотеки.
//

#include "Table.h"

namespace Prog3 {
	/*Table::Table() :size(0)  {
	
		for (int i = 0; i < SZ; i++) {

			tab[i].key = -1;
			strcpy_s(tab[i].info, " ");
			tab[i].busy = 0;

		}
	
	}*/



	Table::Table(int n , int* key, char* info[10]) :size(0) {
		if (n > SZ) {
			throw std::exception("a lot of element");
			return;
		}
		for (int i = 0; i < SZ; i++) {

			tab[i].key = -1;
			strcpy_s(tab[i].info, " ");
			tab[i].busy = 0;

		}

		for (int i = 0; i < n; i++) {
			if (strlen(info[i]) > tab[i].inf)
				throw std::exception("a lot of simbol on info");
			if (size == SZ)
				throw std::exception("Table overflow!");
			if (key[i] < 0)
				throw std::exception("Key is bad!");

			int  tmphash = hash(key[i]);
			while (tab[tmphash].busy) {
				tmphash = hash(tmphash);
			}
			++size;
			tab[tmphash].key = key[i];
			strcpy_s(tab[tmphash].info, info[i]);
			tab[tmphash].busy = 1;
			
		}
	}

	int Table::add( int key, const char* info) {
		if (size == SZ)
			throw std::exception("Table overflow!");
		if (key < 0)
			throw std::exception("Key is bad!");
		if (strlen(info) > tab[0].inf)
			throw std::exception("a lot of simbol on info");
		int  tmphash = hash(key);
		while (tab[tmphash].busy) {
			tmphash = hash(tmphash);
		}
		++size;
		tab[tmphash].key = key;
		strcpy_s(tab[tmphash].info, info);
		tab[tmphash].busy = 1;


		return 0;
	}



	Table& Table::reconst() {
		if (size == 0)
			return *this;

		for (int i =0; i < SZ; i++) {

			if(tab[i].busy== 1){
				tab[i].busy = 0;
				add(tab[i].key, tab[i].info);

			}
		}
		return *this;
		
	}
	int Table::delet( int key, char* info) {
		if (key < 0)
			throw std::exception("Key is bad!");
		if (strlen(info) > tab[0].inf)
			throw std::exception("a lot of simbol on info");


		int  tmphash = hash(key);
		int count = 0;
		if ((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info))) {
			tab[tmphash].busy = 0; 
			tab[tmphash].key = -1;
			size--;
			
			return 0;
		}
		while (!((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info)))) {
			tmphash = hash(tmphash);
			if ((tab[tmphash].key == key)&&  (!strcmp(tab[tmphash].info,info))) {

				tab[tmphash].busy = 0;
				tab[tmphash].key = -1;
				size--;
				return 0;
			}
			count++;
			if (count > size) {
				return 1;
			}

		}
		return 1;
	}
	char* Table::find(int key) const {
		if (key < 0) 
			throw 	std::exception("key is bad!");


		int  tmphash = hash(key);
		int count = 0;

		if (tab[tmphash].key == key) {
			char* info = new char[strlen(tab[tmphash].info) + 1];
			memcpy(info, tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
			info[strlen(tab[tmphash].info)] = '\0';
			return info;
		}


		while (tab[tmphash].key != key) {

			if (tab[tmphash].key == key) {
				char* info = new char[strlen(tab[tmphash].info)];
				memcpy(info, tab[tmphash].info, strlen(tab[tmphash].info));
				info[strlen(tab[tmphash].info)] = '\0';
				return info;
			}

			tmphash = hash(tmphash);
			count++;
			if (count == SZ) {
				return nullptr;
			};
		}
		return nullptr;

	}

	char** Table::findchoosing( int key, int&n) const {

		char** info = new char*[size];
		if (key < 0)
			throw 	std::exception("key is bad!");


		int  tmphash = hash(key);
		int count = 0;
		int i = 1;

		if (tab[tmphash].key == key) {
			info[count] = new char[strlen(tab[tmphash].info) + 1];
			memcpy(info[count], tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
			info[count][strlen(tab[tmphash].info)] = '\0';
			count++;
		}


		while (i <= SZ) {

			tmphash = hash(tmphash);
			if (tab[tmphash].key == key) {
				info[count] = new char[strlen(tab[tmphash].info) + 1 ];
				memcpy(info[count], tab[tmphash].info, strlen(tab[tmphash].info)*sizeof(char));
				info[count][strlen(tab[tmphash].info)] = '\0';
				count++;
			}

			i++;
			
		}
		if (count == 0) {
			return nullptr;
				
			};
		n = count;
		return info;




	}




	std::ostream& Table::show(std::ostream& out)const  noexcept {
		if (size == 0) {
			out << "table empty";
		}
		else {
			out << "  key   |   info " << std::endl;
			for (int i = 0; i < SZ; i++){
				if (tab[i].busy == 1)
					out << tab[i].key << " | " << tab[i].info;
				out << std::endl;
			
			}
		}
		return out;
	}
	std::istream& Table::input(std::istream& is) {
		int key;
		is >> key;

		if (size == SZ)
			throw std::exception("Table overflow!");
		if (key < 0)
			throw std::exception("Key is bad!");

		int  tmphash = hash(key);
		while (tab[tmphash].busy) {
			tmphash = hash(tmphash);
		}
		++size;
		tab[tmphash].key = key;
		is >> tab[tmphash].info;
		tab[tmphash].busy = 1;


		return is;



	}
	Table & Table::copy(const Table& st)  noexcept
	{

		for (int i = 0; i < SZ; i++) {
			memcpy(tab[i].info, st.tab[i].info, strlen(st.tab[i].info) * sizeof(char));
			tab[i].key = st.tab[i].key;
			tab[i].busy = st.tab[i].busy;
		}
		this->size = size;
		return *this;
	}

	Table& Table::move() noexcept {

		//for (int i = 0; i < SZ; i++)
		//	if (tab[i].busy == 1) {

		//		memcpy(tab[i].info, tab[i].info, strlen(tab[i].info) * sizeof(char));
		//		tab[i].key = tab[i].key;
		//		tab[i].busy = 1;
		//		tab[i].busy = 0;
		//	}
		return *this;
	}


	std::ostream& operator <<(std::ostream& out, const Table& tab)
	{
		tab.show(out);
		return out;
	}

	std::istream& operator >>(std::istream& is, Table& tab )
	{
		int key;
		char *info = new char[ tab.getMaxSize()];
		is >> key;
		is >> info;
		tab.add(key,info);
		return is;
	}

	Table& Table::operator +=(const Table& tab2)
	{
		int count = this->size;
		for (int i = 0; i < tab2.SZ;i++ ) {
			if (count == this->SZ)
				return *this;
			if(tab2.tab[i].busy ==1){
				add(tab2.tab[i].key, tab2.tab[i].info);
				count++;
			};
		}

		return *this;
	}

	//Table operator +(Table tab, const Table& tab1) {
	//	
	//	tab += tab1;
	//	return tab;
	//}
	Table Table::operator +(const Table& tab1) const {
		Table tmp;
		tmp= *this;
		tmp += tab1;
	
		return tmp;

	};
    void invertBits(int& num)
	{
		int x = log2(num) + 1;
		for (int i = 0; i < x; i++)
			num = (num ^ (1 << i));

	}
	Table Table::operator ~() const{
		Table tab1;
		int key;
		for (int i = 0; i < this->SZ; i++) {
			
			if (this->tab[i].busy == 1) {
				key = this->tab[i].key;
				invertBits(key);
				tab1.add(key,this->tab[i].info);
			};
		};
		return tab1;
	}
	Table& Table::operator --() {

		for (int i = 0; i <this->SZ; i++) {

			if (this->tab[i].busy == 1) {
				this->delet(this->tab[i].key, this->tab[i].info);
				return *this;
			};
		}

		return *this;
	}
	Table Table::operator --(int k) {
		Table tab;
		tab = this->copy(*this);
		for (int i = 0; i < this->SZ; i++) {

			if (this->tab[i].busy == 1) {
				this->delet(this->tab[i].key, this->tab[i].info);
				return tab;
			};
		}
		return tab;
	}
	bool Table::operator ==(const Table& tab1) {

		for (int i = 0; i < tab1.SZ; i++) {

			if (!((tab1.tab[i].key == this->tab[i].key) && (!strcmp(tab1.tab[i].info, this->tab[i].info))))
				return false;
		}
		return true;
	}

	Table& Table::operator =(const Table& tab1) {

		for (int i = 0; i < SZ; i++){
			memcpy(this->tab[i].info, tab1.tab[i].info, (strlen(tab1.tab[i].info)+1) * sizeof(char));
		///	this->tab[i].info[strlen(tab1.tab[i].info) ] = '\0';
			this->tab[i].key = tab1.tab[i].key;
			this->tab[i].busy = tab1.tab[i].busy;
		}	
		this->size = tab1.size;
		return *this;
	}

	Item Table::operator[] (int i) const {
		/*	try {
			this->add(item->key, item->info);
		}
		catch (const std::exception& msg) {
			std::cout << msg.what() << std::endl;
		}*/
	
		Item ik;
		memcpy(&ik, &tab[i], sizeof(Item));
		return ik;		
	}
	Item& Table::operator[] (int i)  {

		return this->tab[i];
	}

	Table::operator int() {
		return size;
	}
}



//namespace Dynamic {
//
//	char* get_str(std::istream& is) {
//		int size = 80;
//
//		char* info = new char[size];
//		int count = 0;
//		char a;
//		do 
//		{
//			is >> a;
//			info[count] = a;
//			count++;
//
//			if (count == size) {
//				char* tmp = new char[size];
//				memcpy(tmp, info, strlen(info) + 1);
//				delete[]info;
//				size += 80;
//				info = new char[size];
//				memcpy(info, tmp, strlen(tmp) + 1);
//				delete[] tmp;
//
//			}
//		} while ((!std::cin.good()) ||( std::cin.peek() != '\n'));
//		
//		char* res = new char[count+1];
//		memcpy(res, info, count);
//		res[count] = '\0';
//		delete[] info;
//		return res;
//
//	}
//
//	Table::Table(int n, int* key, char**info) {
//		if (n > Quota) {
//			tab = new Item[n];
//			size = n;
//		}
//		else
//		{
//			tab = new Item[Quota];
//			size = Quota;
//		}
//		for (int i = 0; i < size; i++) {
//
//			tab[i].key = -1;
//			tab[i].info = nullptr;
//			tab[i].busy = 0;
//
//		}
//		count_busy = 0;
//		for (int i = 0; i < n; i++) {
//			
//			if (key[i] < 0)
//				throw std::exception("Key is bad!");
//
//			int  tmphash = hash(key[i]);
//			while (tab[tmphash].busy) {
//				tmphash = hash(tmphash);
//			}
//			++count_busy;
//
//			tab[tmphash].key = key[i];
//			memcpy(tab[tmphash].info, info[i], strlen(info[i]) + 1);
//			tab[tmphash].busy = 1;
//
//		}
//	}
//
//	int Table::add(int key, const char* info) {
//		if (size == count_busy) {
//			Table tmp = this->copy(*this);
//			delete [] tab;
//			size += Quota;
//			tab = new Item[size];
//			*this = tmp.copy(tmp);
//
//		}
//		if (key < 0)
//			throw std::exception("Key is bad!");
//		int  tmphash = hash(key);
//		while (tab[tmphash].busy) {
//			tmphash = hash(tmphash);
//		}
//		++count_busy;
//		tab[tmphash].key = key;
//		tab[tmphash].info = new char[strlen(info)];
//		memcpy(tab[tmphash].info, info, strlen(info) + 1);
//		tab[tmphash].busy = 1;
//
//
//		return 0;
//	}
//
//
//
//	Table& Table::reconst() {
//		if (size == 0)
//			return *this;
//
//		for (int i = 0; i < size; i++) {
//
//			if (tab[i].busy == 1) {
//				tab[i].busy = 0;
//				add(tab[i].key, tab[i].info);
//
//			}
//		}
//		return *this;
//
//	}
//	int Table::delet(int key, char* info) {
//		if (key < 0)
//			throw std::exception("Key is bad!");
//
//
//		int  tmphash = hash(key);
//		int count = 0;
//		if ((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info))) {
//			tab[tmphash].busy = 0;
//			tab[tmphash].key = -1;
//			delete[] tab[tmphash].info;
//			count_busy--;
//
//			return 0;
//		}
//		while (!((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info)))) {
//			tmphash = hash(tmphash);
//			if ((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info))) {
//
//				tab[tmphash].busy = 0;
//				delete[] tab[tmphash].info;
//				tab[tmphash].key = -1;
//				count_busy--;
//				return 0;
//			}
//			count++;
//			if (count > size) {
//				return 1;
//			}
//
//		}
//		return 1;
//	}
//	char* Table::find(int key) const {
//		if (key < 0)
//			throw 	std::exception("key is bad!");
//
//
//		int  tmphash = hash(key);
//		int count = 0;
//
//		if (tab[tmphash].key == key) {
//			char* info = new char[strlen(tab[tmphash].info) + 1];
//			memcpy(info, tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
//			info[strlen(tab[tmphash].info)] = '\0';
//			return info;
//		}
//
//
//		while (tab[tmphash].key != key) {
//
//			if (tab[tmphash].key == key) {
//				char* info = new char[strlen(tab[tmphash].info)];
//				memcpy(info, tab[tmphash].info, strlen(tab[tmphash].info));
//				info[strlen(tab[tmphash].info)] = '\0';
//				return info;
//			}
//
//			tmphash = hash(tmphash);
//			count++;
//			if (count == size) {
//				return nullptr;
//			};
//		}
//		return nullptr;
//
//	}
//
//	char** Table::findchoosing(int key, int& n) const {
//
//		char** info = new char* [size];
//		if (key < 0)
//			throw 	std::exception("key is bad!");
//
//
//		int  tmphash = hash(key);
//		int count = 0;
//		int i = 1;
//
//		if (tab[tmphash].key == key) {
//			info[count] = new char[strlen(tab[tmphash].info) + 1];
//			memcpy(info[count], tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
//			info[count][strlen(tab[tmphash].info)] = '\0';
//			count++;
//		}
//
//
//		while (i <= size) {
//
//			tmphash = hash(tmphash);
//			if (tab[tmphash].key == key) {
//				info[count] = new char[strlen(tab[tmphash].info) + 1];
//				memcpy(info[count], tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
//				info[count][strlen(tab[tmphash].info)] = '\0';
//				count++;
//			}
//
//			i++;
//
//		}
//		if (count == 0) {
//			return nullptr;
//
//		};
//		n = count;
//		return info;
//
//	}
//
//
//
//
//	std::ostream& Table::show(std::ostream& out)const  noexcept {
//		if (count_busy == 0) {
//			out << "table empty";
//		}
//		else {
//			out << "  key   |   info " << std::endl;
//			for (int i = 0; i < size; i++) {
//				if (tab[i].busy == 1)
//					out << tab[i].key << " | " << tab[i].info;
//				out << std::endl;
//
//			}
//		}
//		return out;
//	}
//	std::istream& Table::input(std::istream& is) {
//		int key;
//		
//		is>> key;
//		
//		if (key < 0)
//			throw std::exception("Key is bad!");
//
//		int  tmphash = hash(key);
//		while (tab[tmphash].busy) {
//			tmphash = hash(tmphash);
//		}
//		++size;
//		tab[tmphash].key = key;
//		tab[tmphash].info = get_str(is);
//		tab[tmphash].busy = 1;
//
//
//		return is;
//
//
//
//	}
//	Table& Table::copy(const Table& st)  noexcept
//	{
//
//		for (int i = 0; i < size; i++) {
//			if(st.tab[i].busy == 1)
//				memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) +1)* sizeof(char));
//			tab[i].key = st.tab[i].key;
//			tab[i].busy = st.tab[i].busy;
//		}
//		this->size = size;
//		this->count_busy = count_busy;
//		return *this;
//	}
//
//	Table& Table::move() noexcept {
//
//	/*	for (int i = 0; i < size; i++) {
//			if (st.tab[i].busy == 1)
//				memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
//			tab[i].key = st.tab[i].key;
//			tab[i].busy = st.tab[i].busy;
//		}
//		this->size = size;
//		this->count_busy = count_busy;*/
//		return *this;
//	}
//
//
//	std::ostream& operator <<(std::ostream& out, const Table& tab)
//	{
//		tab.show(out);
//		return out;
//	}
//
//	std::istream& operator >>(std::istream& is, Table& tab)
//	{
//		int key;
//		char* info =get_str(is);
//		is >> key;
//		tab.add(key, info);
//		return is;
//	}
//
//	Table& Table::operator +=(const Table& tab2)
//	{
//		for (int i = 0; i < tab2.size; i++) {
//			if (tab2.tab[i].busy == 1) {
//				add(tab2.tab[i].key, tab2.tab[i].info);
//				
//			};
//		}
//
//		return *this;
//	}
//
//	//Table operator +(Table tab, const Table& tab1) {
//	//	
//	//	tab += tab1;
//	//	return tab;
//	//}
//	Table Table::operator +(const Table& tab1) const {
//		Table tmp;
//		tmp = *this;
//		tmp += tab1;
//
//		return tmp;
//
//	};
//	void invertBits(int& num)
//	{
//		int x = log2(num) + 1;
//		for (int i = 0; i < x; i++)
//			num = (num ^ (1 << i));
//
//	}
//	Table Table::operator ~() const {
//		Table tab1;
//		int key;
//		for (int i = 0; i < this->size; i++) {
//
//			if (this->tab[i].busy == 1) {
//				key = this->tab[i].key;
//				invertBits(key);
//				tab1.add(key, this->tab[i].info);
//			};
//		};
//		return tab1;
//	}
//	Table& Table::operator --() {
//
//		for (int i = 0; i < this->size; i++) {
//
//			if (this->tab[i].busy == 1) {
//				this->delet(this->tab[i].key, this->tab[i].info);
//				return *this;
//			};
//		}
//
//		return *this;
//	}
//	Table Table::operator --(int k) {
//		Table tab;
//		tab = this->copy(*this);
//		for (int i = 0; i < this->size; i++) {
//
//			if (this->tab[i].busy == 1) {
//				this->delet(this->tab[i].key, this->tab[i].info);
//				return tab;
//			};
//		}
//		return tab;
//	}
//	bool Table::operator ==(const Table& tab1) {
//
//		for (int i = 0; i < tab1.size; i++) {
//
//			if (!((tab1.tab[i].key == this->tab[i].key) && (!strcmp(tab1.tab[i].info, this->tab[i].info))))
//				return false;
//		}
//		return true;
//	}
//
//	Table& Table::operator =(const Table& tab1) {
//
//		for (int i = 0; i < size; i++) {
//			if(tab1.tab[i].busy == 1){
//				this->tab[i].info = new char[(strlen(tab1.tab[i].info) + 1)];
//			memcpy(this->tab[i].info, tab1.tab[i].info, (strlen(tab1.tab[i].info) + 1) * sizeof(char));
//			}///	this->tab[i].info[strlen(tab1.tab[i].info) ] = '\0';
//			this->tab[i].key = tab1.tab[i].key;
//			this->tab[i].busy = tab1.tab[i].busy;
//		}
//		this->size = tab1.size;
//		this->count_busy = tab1.count_busy;
//		return *this;
//	}
//
//	Item Table::operator[] (int i) const {
//		/*	try {
//			this->add(item->key, item->info);
//		}
//		catch (const std::exception& msg) {
//			std::cout << msg.what() << std::endl;
//		}*/
//
//		Item ik;
//		memcpy(&ik, &tab[i], sizeof(Item));
//		return ik;
//	}
//	Item& Table::operator[] (int i) {
//
//		return this->tab[i];
//	}
//
//	Table::operator int() {
//		return size;
//	}
//
//
//
//
//
//
//
//
//}