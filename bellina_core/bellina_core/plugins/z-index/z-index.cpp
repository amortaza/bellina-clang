#include "stdafx.h"

#include "bellina/bellina.h"

#include "z-index.h"

using namespace std;
using namespace bl;
using namespace bl::listener;

using namespace z_index;

namespace z_index {
	char* plugin_name = "z-index";

	map<string, list<string>*> kidsByParent;

	void init() {}
	void onNode(PluginCallback cb) {}

	void uninit();
	void tickBeforeEnd();

	list<string>* getOrdering(Node*parent) {
		string key(parent->nid);

		auto e2 = kidsByParent.find(key);
		if (e2 == kidsByParent.end()) {
			printf("creating %s\n",parent->nid);
			list<string>* l = new list<string>();
			kidsByParent[key] = l;

			return l;
		}
		else {
			return e2->second;
		}
	}
}

void z_index::uninit() {
	typedef map<string, list<string>*>::iterator it1;
	for (it1 it = kidsByParent.begin(); it != kidsByParent.end(); it++) {
		list<string>* ordering = it->second;

		delete ordering;
	}

	kidsByParent.clear();
}

void z_index::tickBeforeEnd() {
	Node* p = _::current_node;
	
	getOrdering(p);
}
