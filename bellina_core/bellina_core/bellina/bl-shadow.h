#pragma once

namespace bl { extern class Node; };

namespace bl {
	namespace shadow_ {
		extern map<string, Node *> shadowNodes;

		void uninit();
	}
}