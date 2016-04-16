#pragma once

namespace bl { extern class Node; }

namespace bl {
	namespace util {
		void calcGlobalPositions();

		Node* getNodeAtPos(int wx, int wy);
		Node* getNodeById(char* id);

		bool isNode(Node*, char* id);
	}
}