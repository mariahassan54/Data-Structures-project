#pragma once

#include <cstring>
#include <sha.h>
using namespace std;

#define ACCURACY 8 // WE are using this because the collision chance is 50% after 5 billion trial. we can change it anytime to change Proximity. currently working with QWORD


template <typename T>
int Strclen(T* str) { //Recursively finds the length of string incoming.
	/*
	* Paramters: str / string.
	* Function: Finds the length of string passed.
	* Returns: returns the string length.
	*/
	if (str[0] == '\0') {
		return 0;
	}
	return 1 + Strclen(++str);
}

template <typename T>
T* HexConvertor(T* hexValue) {
	/*
	* Paramters: hexValue / string.
	* Function: Converts Hex into binary.
	* Returns: Returns Binary.
	*/
	int hexCount = Strclen(hexValue);
	T* returnValue = new T[(4 * hexCount) + 1]; //Hex is 4 bit that's why we are multiplying 4 with number of Hex Tacter.
	int index = 0;
	for (int i = 0; i < hexCount; i++) {
		switch (hexValue[i]) {
		case '0':
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			break;
		case '1':
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			break;
		case '2':
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '0';

			break;
		case '3':
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			break;
		case '4':
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			break;
		case '5':
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			break;
		case '6':
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			break;
		case '7':
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			break;
		case '8':
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			break;
		case '9':
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			break;
		case 'A':
		case 'a':
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			break;
		case 'B':
		case 'b':
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			break;
		case 'C':
		case 'c':
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '0';
			break;
		case 'D':
		case 'd':
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			returnValue[index++] = '1';
			break;
		case 'E':
		case 'e':
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '0';
			break;
		case 'F':
		case 'f':
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			returnValue[index++] = '1';
			break;
		default:
			throw "Error/DEBUG: Impossible case detected. (HexConvertor)";
			break;
		}
	}
	returnValue[hexCount * 4] = NULL;
	return returnValue;
}


template <typename T>
unsigned long long int btoi(T* binary) {
	/*
	* Paramters: binary / string.
	* Function: Binary to int covertor.
	* Returns: Returns int.
	*/
	int binaryLength = Strclen(binary);
	unsigned long long int returnValue = 0;
	for (int i = binaryLength - 1; i >= 0; i--) {
		int multiple = (binary[i] == '0') ? 0 : 1;
		returnValue += multiple * pow(2, binaryLength - (i + 1));
	}
	return returnValue;
}





class Key {
	char* key;
	int keyLength;
public:
	Key(char* hashedKey) {
		keyLength = 41;
		key = new char[41];
		strcpy(key, hashedKey);
	}
	Key(unsigned char str[]) {
		byte hash[SHA_DIGEST_LENGTH];
		SHA1(str, Strclen(str), hash);
		keyLength = 43;
		key = new char[43];
		for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
			sprintf(&key[2 * i], "%02x", hash[i]);
		}
	}
	bool operator >(const Key& obj) {
		char* cmp = new char[ACCURACY + 1];
		cmp[ACCURACY] = NULL;
		for (int i = 0; i < ACCURACY; i++) {
			cmp[i] = this->key[i];
		}
		char* cmp1 = new char[ACCURACY + 1];
		cmp1[ACCURACY] = NULL;
		for (int i = 0; i < ACCURACY; i++) {
			cmp1[i] = obj.key[i];
		}
		char* bin1 = HexConvertor(cmp);
		char* bin2 = HexConvertor(cmp1);
		unsigned long long int value1 = btoi(bin1);
		unsigned long long int value2 = btoi(bin2);
		if (value1 > value2) {
			return true;
		}
		return false;
	}
	bool operator <(const Key& obj) {
		char* cmp = new char[ACCURACY + 1];
		cmp[ACCURACY] = NULL;
		for (int i = 0; i < ACCURACY; i++) {
			cmp[i] = this->key[i];
		}
		char* cmp1 = new char[ACCURACY + 1];
		cmp1[ACCURACY] = NULL;
		for (int i = 0; i < ACCURACY; i++) {
			cmp1[i] = obj.key[i];
		}
		char* bin1 = HexConvertor(cmp);
		char* bin2 = HexConvertor(cmp1);
		unsigned long long int value1 = btoi(bin1);
		unsigned long long int value2 = btoi(bin2);
		if (value1 < value2) {
			return true;
		}
		return false;
	}
	bool operator ==(const Key& obj) {
		return (!((*this < obj) || (*this > obj))); // If both < and > returns false;
	}
	unsigned long long int getkey8bit() {
		char* cmp = new char[ACCURACY + 1];
		cmp[ACCURACY] = NULL;
		for (int i = 0; i < ACCURACY; i++) {
			cmp[i] = this->key[i];
		}
		char* bin1 = HexConvertor(cmp);
		return btoi(bin1);
	}
	char* getKey() {
		return key;
	}
};