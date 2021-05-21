#pragma once

template <class T>
class FingerTable {
private:
	struct ptrNode {
		T* ptr;
		ptrNode* next;
		ptrNode* previous;
		ptrNode(T* p) {
			ptr = p;
			next = nullptr;
			previous = nullptr;
		}
	};
	ptrNode* head;
	int ptrCount;
public:
	FingerTable() {
		head = nullptr;
		ptrCount = 0;
	}
	void insertValue(T* ptr) {
		if (head == nullptr) {
			ptrNode* pointer = new ptrNode(ptr);
			head = pointer;
		}
		else {
			ptrNode* interator = head;
			while (interator->next != nullptr) {
				interator = interator->next;
			}
			ptrNode* pointer = new ptrNode(ptr);
			interator->next = pointer;
			pointer->previous = interator;
		}
		ptrCount++;
	}
	T* getPtr(unsigned int index) {
		ptrNode* ret = head;
		for (int i = 0; i < index; i++) {
			ret = ret->next;
		}
		return ret->ptr;
	}
};