#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<iostream>
#include<string>
using namespace std;

template<typename T>
struct hashentry {
	T data;
	int state;
};

template<class T>
class HashTable {

private:
	int size;
	int occupied;//total number of filled entries
	struct hashentry* p;

public:
	HashTable(int s) {

		size = s; //choosing a prime number

		p = new hashentry[s];

		for (int i = 0; i < s; i++) {
			p[i].data = 0;
			p[i].state = 0;
		}

	}

	void makeEmpty() {

		occupied = 0;
		for (int i = 0; i < size; i++) {
			p[i].data = 0;
			p[i].state = 0;
		}

	}

	unsigned int string_hash(T key, int size) {

		int x = key.length();
		unsigned int hash = 0;//indices are not negative
		for (int i = 0; i < x; i++)
			hash = 37 * hash + key[i];

		return hash % size;

	}
	bool active(int val) {
		if (val == 1)
			return true;
		else
			return false;
	}
	int findposition(const T& obj)const {

		int position = string_hash(obj), i = 0;
		while (p[position].state != 0 && p[position].data != obj.data) {

			i++;
			position += 2 * i - 1;// will get the ith probe
			if (position >= size)
				position = position - size;
		}
		return position;

	}

T* find(const T &obj){

		int position = findposition(obj);
		if (active(position))
			return p[position].data;
		else
			return nullptr;		

	}

int newprime(int n) {
	int i = n/2;
	int to_return = n;
	while(!isPrime(n) {
		if (n % i == 0)
			n++;
		i--;
	}

	
	return n;
}

void rehash() {

	hashentry* newtable = new hashentry[2*size];

	for (int i = 0; i < 2*size; i++) {
		newtable[i].data = 0;
		newtable[i].state = 0;
	}
	for (int i = 0; i < size; i++) {

		if (p[i].state == 1) {

			newtable.insert(p[i].data);
		}
	}


}

void insert(const T& obj) {

		int current = findpos(obj);
		if (active(current))
			cout << "Duplicate vales cannot be inserted" << endl;
		p[current].state = 1;//is active
		occupied++;
		if (occupied > size / 2)
			rehash();

	}

};

#endif
