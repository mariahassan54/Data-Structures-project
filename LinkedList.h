#pragma once

#include <sha.h>
#include "FingerTable.h"
#include "key.h"
#include "AVL.h"
#include <iostream>
#include <fstream>
using namespace std;



template <class T>
class Ring {
	template <typename Type>
	struct Machine {
		Type nodeID;
		Machine* next;
		Machine* previous;
		Key* key;
		FingerTable<Machine>* FT;
		node* avlHead;
		fstream obj;
		Machine(Type ID) {
			nodeID = ID;
			next = nullptr;
			previous = nullptr;
			avlHead = new node;
			FT = new FingerTable<Machine>;
			key = nullptr;
		}
	};
	AVL* handler;
	Machine<T>* head;
	int nodeCount;
	const unsigned long long int space;
public:
	Ring(unsigned long long int maxSpace) : space(maxSpace) {
		handler = new AVL();
		head = nullptr;
		nodeCount = 0;
	}
	bool insertMachine() {
		cout << "please enter the manual ID: ";
		unsigned char input[16];
		cin >> input;
		Key* keys = new Key(input);
		unsigned long long int value = keys->getkey8bit();
		long long ID = value % space;
		cout << ID << endl;
		if (head == nullptr) {
			Machine<T>* machine = new Machine<T>(ID);
			machine->key = keys;
			machine->next = machine;
			machine->previous = machine;
			head = machine;
		}
		else {
			if (head->nodeID > ID) {
				Machine<T>* machine = new Machine<T>(ID);
				machine->key = keys;
				Machine<T>* temp = head;
				Machine<T>* prev = head->previous;
				prev->next = machine;
				machine->previous = prev;
				machine->next = temp;
				temp->previous = machine;
				head = machine;
				nodeCount++;
				updateFinger();
				return true;
			}
			Machine<T>* current = head;
			Machine<T>* prev = head;
			do {
				prev = current;
				current = current->next;
			} while (current->nodeID < ID && current != head);
			Machine<T>* machine = new Machine<T>(ID);
			machine->key = keys;
			machine->previous = prev;
			machine->next = current;
			prev->next = machine;
			current->previous = machine;
		}
		nodeCount++;
		cout << nodeCount << endl;
		updateFinger();
		return true;
	}
	Machine<T>* getSucc(long long int ID) {
		Machine<T>* interator = head;
		Machine<T>* returnVal = nullptr;
		do {
			if (interator->nodeID > ID) {
				return interator;
			}
			else {
				interator = interator->next;
			}
		} while (interator != head);
		return head;
	}
	bool updateFinger() {
		Machine<T>* interator = head;
		do {
			for (long long int i = 1; i <= nodeCount; i++) {
				long long int val = (interator->nodeID + (long long int)pow(2, i - 1)) % space;
				Machine<T>* corr = getSucc(val);
				interator->FT->insertValue(corr);
			}
			interator = interator->next;
		} while (interator != head);
		return true;
	}
	bool removeMachine() {
		cout << "please enter the machine to remove (ID): ";
		unsigned char input[16];
		cin >> input;
		Key* keys = new Key(input);
		unsigned long long int value = keys->getkey8bit();
		long long ID = value % space;
		cout << ID << endl;
		if (head == nullptr) {
			cout << "No machine exist." << endl;
			return false;
		}
		else {
			if (head->nodeID == ID) {
				Machine<T>* toDel = head;
				Machine<T>* current = head->next;
				head->previous->next = current;
				current->previous = head->previous;
				head = current;
				delete toDel;
				updateFinger();
			}
			else {
				Machine<T>* current = head;
				Machine<T>* prev = head;
				do {
					prev = current;
					current = current->next;
				} while (current->nodeID != ID && current != head);
				if (current == head) {
					cout << "Machine Not Found." << endl;
					return false;
				}
				prev->next = current->next;
				Machine<T>* toDel = current;
				prev->next->previous = prev;
				delete toDel;
				updateFinger();
			}
		}
		nodeCount--;
		updateFinger();
		return true;
	}
	void printList() {
		Machine<T>* interator = head;
		cout << endl;
		do {
			cout << interator->nodeID << endl;
			interator = interator->next;
		} while (interator != head);
	}
	bool printFinger() {
		cout << "Please enter the machine you want to connect from: " << endl;
		unsigned char input[16];
		cin >> input;
		Key* keys = new Key(input);
		unsigned long long int value = keys->getkey8bit();
		long long ID = value % space;
		Machine<T>* interator = head;
		if (head->nodeID == ID) {
			cout << "Machine Found... Connection established." << endl;
		}
		else {
			do {
				interator = interator->next;
			} while (interator->nodeID != ID && interator != head);
			if (interator == head) {
				cout << "Machine not found for corresponding IP addres, please try agian." << endl;
				return false;
			}
			else {
				cout << "Machine Found... Connection established." << endl;
			}
		}
		updateFinger();
		for (int i = 0; i < nodeCount; i++) {
			cout << "for " << i << " Machine ID: ";
			Machine<T>* temp = interator->FT->getPtr(i);
			cout << temp->nodeID << endl;
		}
	}
	bool insertData() {
		cout << "Please enter the machine you want to connect from: " << endl;
		unsigned char input[16];
		cin >> input;
		Key* keys = new Key(input);
		unsigned long long int value = keys->getkey8bit();
		long long ID = value % space;
		Machine<T>* interator = head;
		if (head->nodeID == ID) {
			cout << "Machine Found... Connection established." << endl;
		}
		else {
			do {
				interator = interator->next;
			} while (interator->nodeID != ID && interator != head);
			if (interator == head) {
				cout << "Machine not found for corresponding IP addres, please try agian." << endl;
				return false;
			}
			else {
				cout << "Machine Found... Connection established." << endl;
			}
		}
		cout << "please enter the the data you want to insert: " << endl;
		cout << "please enter the key: ";
		unsigned char input2[100];
		cin >> input2;
		Key* key1 = new Key(input);
		unsigned long long int val = key1->getkey8bit();
		long long ID1 = val % space;
		cout << "Please enter the the value to save corresponding the following key: " << endl;
		string strValue;
		cin >> strValue;
		cout << "The key ID: " << ID1 << endl;


	}

	Machine<T>* getHead() {
		return head;
	}
};