#pragma once

#include <map>

using namespace std;

namespace pango {

	namespace bubble {

		namespace _ {

			template <class T>
			class MapList {
			public:
				map <string, list<T>* > mapOfList;

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
					//rintf("MapList add\n");
					listPtr->push_back(valuePtr);
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
					//rintf("MapList clear\n");
				}

				void clear(string key) {
					auto e2 = mapOfList.find(key);

					if (e2 == mapOfList.end()) return;

					list<T>* listPtr = e2->second;

					list<T>::const_iterator it;
					for (it = listPtr->begin(); it != listPtr->end(); ++it) {
						T v = *it;

						intptr_t address = (intptr_t)v;

						addresses.erase(address);
					}

					delete listPtr;

					mapOfList.erase(key);
				}
			};
		}
	}
}