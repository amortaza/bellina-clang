#pragma once

namespace bl { extern class Node; }

namespace bl {
	namespace util {
		void calcGlobalPositions();

		Node* getNodeAtPos(int wx, int wy);
	}
}