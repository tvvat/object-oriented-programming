//

#include "tabledin.h"
#include <algorithm>
#include<algorithm>



namespace Dynamic {
	Table::Table(const Table& st)noexcept :size(st.size), count_busy(st.count_busy)
	{
		std::cout << "Table copy work" << std::endl;
		this->tab = new Item[st.size];

		for (int i = 0; i < size; i++) {
			if (st.tab[i].busy == 1) {
				tab[i].info = new char[strlen(st.tab[i].info) + 1];
				memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
			}
			else
				tab[i].info = nullptr;
			tab[i].key = st.tab[i].key;
			tab[i].busy = st.tab[i].busy;
		}
		this->size = size;
		this->count_busy = count_busy;


	}

	Table::Table(Table&& st)noexcept :size(st.size), count_busy(st.count_busy)
	{
		std::cout << "Table  move work" << std::endl;
		this->tab = st.tab;
		st.tab = nullptr;
	}

	Table& Table::operator =(Table&& st) {
		std::cout << "=  move work" << std::endl;

		this->tab = st.tab;
		st.tab = nullptr;

		return *this;
	}







	char* get_str(std::istream& is) {
		int size = 80;

		char* info = new char[size];
		int count = 0;
		char a;
		do
		{
			is >> a;
			info[count] = a;
			count++;

			if (count == size) {
				char* tmp = new char[size];
				memcpy(tmp, info, strlen(info) + 1);
				delete[]info;
				size += 80;
				info = new char[size];
				memcpy(info, tmp, strlen(tmp) + 1);
				delete[] tmp;

			}
		} while ((!std::cin.good()) || (std::cin.peek() != '\n'));

		char* res = new char[count + 1];
		memcpy(res, info, count);
		res[count] = '\0';
		delete[] info;
		return res;

	}

	Table::Table(int n, int* key, char** info) {
		tab = nullptr;
		if (n > Quota) 
			size = n;
		else
			size = Quota;

		tab = new Item[size];

		for (int i = 0; i < size; i++) {

			tab[i].key = -1;
			tab[i].info = nullptr;
			tab[i].busy = 0;

		}

		count_busy = 0;
		for (int i = 0; i < n; i++) {

			if (key[i] < 0)
				throw std::exception("Key is bad!");

			int  tmphash = hash(key[i]);
			while (tab[tmphash].busy) {
				tmphash = hash(tmphash);
			}
			++count_busy;

			tab[tmphash].key = key[i];
			tab[tmphash].info = new char[strlen(info[i])+1];
			memcpy(tab[tmphash].info, info[i], strlen(info[i]) + 1);
			tab[tmphash].busy = 1;

		}
	}

	Table:: ~Table() {
	
		



	}




	int Table::add(int key, const char* info) {
		if (key < 0)
			throw std::exception("Key is bad!");
		if (size == count_busy) {
			
			
			size += Quota;

			Table to;
			delete [] to.tab;
			to.tab = new Item[size]; 
			for (int i = 0; i < size; i++) {
				to.tab[i].busy = 0;
				to.tab[i].info = nullptr;
			}
			for(int i = 0;i<size-Quota;i++){
				
				to.add(this->tab[i].key, this->tab[i].info);
			}
			to.size = size;
			to.count_busy = count_busy;
			*this = to;
		}
		
		int  tmphash = hash(key);
		
		while (tab[tmphash].busy) {
			
			tmphash = hash(tmphash);
		}
		++count_busy;
		tab[tmphash].key = key; 
		if (tab[tmphash].info != nullptr) {
			delete[] tab[tmphash].info;
			tab[tmphash].info = nullptr;
		}
		tab[tmphash].info = new char[strlen(info)+1]; 
		memcpy(tab[tmphash].info, info, strlen(info) + 1); 
		tab[tmphash].busy = 1;


		return 0;
	}



	Table& Table::reconst() {
		if (size == 0)
			return *this;

		for (int i = 0; i < size; i++) {

			if (tab[i].busy == 1) {
				tab[i].busy = 0;
				add(tab[i].key, tab[i].info);

			}
		}
		return *this;

	}
	int Table::delet(int key, char* info) {
		if (key < 0)
			throw std::exception("Key is bad!");


		int  tmphash = hash(key);
		int count = 0;
		if ((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info))) {
			tab[tmphash].busy = 0;
			tab[tmphash].key = -1;
			delete[] tab[tmphash].info;
			tab[tmphash].info = nullptr;
			count_busy--;

			return 0;
		}
		while (!((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info)))) {
			tmphash = hash(tmphash);
			if ((tab[tmphash].key == key) && (!strcmp(tab[tmphash].info, info))) {

				tab[tmphash].busy = 0;
				delete[] tab[tmphash].info; 
				tab[tmphash].info = nullptr;
				tab[tmphash].key = -1;
				count_busy--;
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
			if (count == size) {
				return nullptr;
			};
		}
		return nullptr;

	}

	char** Table::findchoosing(int key, int& n) const {

		char** info = new char* [size];
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


		while (i <= size) {

			tmphash = hash(tmphash);
			if (tab[tmphash].key == key) {
				info[count] = new char[strlen(tab[tmphash].info) + 1];
				memcpy(info[count], tab[tmphash].info, strlen(tab[tmphash].info) * sizeof(char));
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
		if (count_busy == 0) {
			out << "table empty";
		}
		else {
			out << "  key   |   info " << std::endl;
			for (int i = 0; i < size; i++) {
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

		if (key < 0)
			throw std::exception("Key is bad!");

		int  tmphash = hash(key);
		while (tab[tmphash].busy) {
			tmphash = hash(tmphash);
		}
		++size;
		tab[tmphash].key = key;
		tab[tmphash].info = get_str(is);
		tab[tmphash].busy = 1;


		return is;



	}
	Table& Table::copy(const Table& st)  noexcept
	{

		for (int i = 0; i < st.size; i++) {
			if (st.tab[i].busy == 1){
				tab[i].info = new char[strlen(st.tab[i].info) + 1];
				memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
			}
			tab[i].key = st.tab[i].key;
			tab[i].busy = st.tab[i].busy;
		}
		this->size = size;
		this->count_busy = count_busy;
		return *this;
	}

	Table& Table::move() noexcept {

		/*	for (int i = 0; i < size; i++) {
				if (st.tab[i].busy == 1)
					memcpy(tab[i].info, st.tab[i].info, (strlen(st.tab[i].info) + 1) * sizeof(char));
				tab[i].key = st.tab[i].key;
				tab[i].busy = st.tab[i].busy;
			}
			this->size = size;
			this->count_busy = count_busy;*/
		return *this;
	}


	std::ostream& operator <<(std::ostream& out, const Table& tab)
	{
		tab.show(out);
		return out;
	}

	std::istream& operator >>(std::istream& is, Table& tab)
	{
		int key;
		char* info = get_str(is);
		is >> key;
		tab.add(key, info);
		return is;
	}

	Table& Table::operator +=(const Table& tab2)
	{
		for (int i = 0; i < tab2.size; i++) {
			if (tab2.tab[i].busy == 1) {
				add(tab2.tab[i].key, tab2.tab[i].info);

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
		tmp = *this;
		tmp += tab1;

		return tmp;

	};
	void invertBits(int& num)
	{
		int x = (log2(num) + 1)/1;
		for (int i = 0; i < x; i++)
			num = (num ^ (1 << i));

	}
	Table Table::operator ~() const {
		Table tab1;
		int key;
		for (int i = 0; i < this->size; i++) {

			if (this->tab[i].busy == 1) {
				key = this->tab[i].key;
				invertBits(key);
				tab1.add(key, this->tab[i].info);
			};
		};
		return tab1;
	}
	Table& Table::operator --() {

		for (int i = 0; i < this->size; i++) {

			if (this->tab[i].busy == 1) {
				tab[i].busy = 0;
				delete[] tab[i].info;
				tab[i].info = nullptr;
				tab[i].key = -1;
				count_busy--;
				return *this;
			};
		}

		return *this;
	}
	Table Table::operator --(int k) {
		Table tab;
		tab = this->copy(*this);
		for (int i = 0; i < this->size; i++) {

			if (this->tab[i].busy == 1) {
				tab[i].busy = 0;
				delete[] tab[i].info;
				tab[i].info = nullptr;
				tab[i].key = -1;
				count_busy--;
				return tab;
			};
		}
		return tab;
	}
	bool Table::operator ==(const Table& tab1) {
		int sizemin;
		if (tab1.size < size)
			 sizemin = tab1.size;
		else
			 sizemin = size;
		for (int i = 0; i < sizemin; i++) {
			if (tab1.tab[i].busy != this->tab[i].busy)
				return false;
			if ((tab1.tab[i].busy)&&(this->tab[i].busy))
			if (!((tab1.tab[i].key == this->tab[i].key) && (!strcmp(tab1.tab[i].info, this->tab[i].info))))
				return false;
		}
		return true;
	}

	Table& Table::operator =(const Table& tab1) {
		std::cout << "=  copy work" << std::endl;
		for (int i = 0; i < size; i++) {
			if (this->tab[i].busy == 1)
					delete[] this->tab[i].info;
			if (tab1.tab[i].busy == 1) {
				this->tab[i].info = new char[(strlen(tab1.tab[i].info) + 1)];
				memcpy(this->tab[i].info, tab1.tab[i].info, (strlen(tab1.tab[i].info) + 1) * sizeof(char));
			}
			else
			{
				this->tab[i].info = nullptr;
			}
			this->tab[i].key = tab1.tab[i].key;
			this->tab[i].busy = tab1.tab[i].busy;
		}
		this->size = tab1.size;
		this->count_busy = tab1.count_busy;
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
	Item& Table::operator[] (int i) {

		return this->tab[i];
	}

	Table::operator int() {
		return size;
	}








}

