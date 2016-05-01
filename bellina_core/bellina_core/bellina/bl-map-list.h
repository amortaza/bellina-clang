#pragma once

template <class T>
class MapList {
public:
	map <string, list<T>* > mapOfList;
	map <intptr_t, bool> addresses;

	list<T>* getList(string key) {
		auto e2 = mapOfList.find(key);
		if (e2 == mapOfList.end()) return 0;

		return e2->second;
	}

	bool existsValue(T valuePtr) {
		intptr_t key = (intptr_t)valuePtr;

		auto e2 = addresses.find(key);
		if (e2 == addresses.end()) return false;

		return true;
	}

	void add(string key, T valuePtr) {
		list<T>* listPtr;

		auto e2 = mapOfList.find(key);
		if (e2 == mapOfList.end()) {
			listPtr = new list<T>();
			mapOfList[key] = listPtr;
		}
		else {
			listPtr = e2->second;
		}

		listPtr->push_back(valuePtr);

		intptr_t address = (intptr_t)valuePtr;
		addresses[address] = true;
	}

	int size(string key) {
		auto e2 = mapOfList.find(key);
		if (e2 == mapOfList.end()) {
			return 0;
		}

		list<T>* listPtr = e2->second;

		return listPtr->size();
	}

	void clear() {
		typedef map<string, list<T>*>::iterator it1;
		for (it1 it = mapOfList.begin(); it != mapOfList.end(); it++) {
			list<T>* listPtr = it->second;
			delete listPtr;
		}

		mapOfList.clear();
		addresses.clear();
	}

	void clear(string key) {
		auto e2 = mapOfList.find(key);

		if (e2 == mapOfList.end()) return;

		list<T>* listPtr = e2->second;

		//		printf("addresses before %i\n", addresses.size());
		list<T>::const_iterator it;
		for (it = listPtr->begin(); it != listPtr->end(); ++it) {
			T v = *it;

			intptr_t address = (intptr_t)v;

			addresses.erase(address);
		}
		//		printf("addresses after %i\n", addresses.size());

		/*list<A*>::const_iterator it;
		for (it = listPtr->begin(); it != listPtr->end(); ++it) {
		A* a = (A*) *it;

		(*a)();
		}*/

		delete listPtr;

		mapOfList.erase(key);
	}
};
