#pragma once

namespace bl { extern class ShadowNode; };

namespace bl {
	namespace shadow_ {
		extern map<string, ShadowNode*> shadowNodes;

		ShadowNode* getShadowNode(Node* node);

		void uninit();
	}
}