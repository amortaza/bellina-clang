#include "stdafx.h"

#include "bl-util.h"
#include "bl-globals.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::util;

namespace bl {
	namespace util {
		bool nodeContainsPoint(Node *node, int wx, int wy) {
			return wx >= node->global_pos.x && wx <= node->global_pos.x + node->w && wy >= node->global_pos.y && wy <= node->global_pos.y + node->h;
		}

		Node* getNodeAtPos(Node *parent, int wx, int wy) {
			if (!parent) return 0;

			if (!nodeContainsPoint(parent, wx, wy)) return 0;

			std::list<Node*>::const_iterator iterator;

			Node* topmost = parent;
			for (iterator = parent->kids.begin(); iterator != parent->kids.end(); ++iterator) {
				Node *kid = *iterator;

				if (nodeContainsPoint(kid, wx, wy)) {
					topmost = kid;
				}
			}

			// now get the topmost from topmost
			if (topmost != parent)
				topmost = getNodeAtPos(topmost, wx, wy);

			return topmost;
		}

		void calcGlobalPositions(Node* node, int parentX, int parentY) {
			parentX = node->global_pos.x = node->x + parentX;
			parentY = node->global_pos.y = node->y + parentY;

			std::list<Node*>::const_iterator iterator;

			for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
				Node *kid = *iterator;

				calcGlobalPositions(kid, parentX, parentY);
			}
		}
	}
}

bool util::isNode(Node *node, char* id) {
	return node && node->nid && id && strcmp(node->nid, id) == 0;
}

Node* util::getNodeById(char* id) {
	std::string key(id);

	auto e2 = nodeById.find(key);

	if (e2 == nodeById.end()) return 0;

	return e2->second;
}

Node* util::getNodeAtPos(int wx, int wy) {
	Node *node = getNodeAtPos(root_node, wx, wy);

	if (!node) return root_node;
}

void util::calcGlobalPositions() {
	if (!root_node) return;

	calcGlobalPositions(root_node, 0, 0);
}
