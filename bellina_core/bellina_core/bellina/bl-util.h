#pragma once

#include <map>

using namespace std;

namespace bl { extern class Node; }

namespace bl {
	namespace util {
		void calcGlobalPositions();

		Node* getNodeAtPos(int wx, int wy);
		Node* getNodeById(char* id);

		bool isNode(Node*, char* id);

		char* nextGlobalId();

		map<string, Node*>* buildNodeLookup(list<Node*>* nodes);

		Node* getShadowNode(Node* node);
	}
}