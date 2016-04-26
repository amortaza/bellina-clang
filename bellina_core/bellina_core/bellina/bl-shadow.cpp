#include "stdafx.h"

#include "bl-core.h"
#include "bl-node.h"
#include "bl-globals.h"
#include "bl-shadow.h"
#include "bl-util.h"

using namespace std;

namespace bl {
	namespace shadow_ {
		map<string, Node *> shadowNodes;
		Node* shadowNode;

		void setNodeFromShadow(Node* node, Node* snode) {
			node->x = snode->x;
			node->y = snode->y;

			node->dim(snode->w, snode->h);
		}
	}
}

using namespace bl;
using namespace bl::_;
using namespace bl::shadow_;

Node* bl::get_shadow() {
	return getShadowNode(current_node);
}

void bl::shadow(ShadowCallback cb) {
	shadowNode = getShadowNode(current_node);

	cb(shadowNode);

	setNodeFromShadow(current_node, shadowNode);
}

void bl::shadow_::uninit() {
	typedef map<string, Node*>::iterator it1;

	for (it1 it = shadowNodes.begin(); it != shadowNodes.end(); it++) {
		Node* node = it->second;

		delete node;
	}
}

Node* shadow_::getShadowNode(Node* node) {
	Node* snode = 0;

	string key(node->nid);

	auto e2 = shadow_::shadowNodes.find(key);
	if (e2 == shadow_::shadowNodes.end()) {
		snode = new Node(0);
		snode->x = node->x;
		snode->y = node->y;
		snode->w = node->w;
		snode->h = node->h;
		shadow_::shadowNodes[key] = snode;
	}
	else {
		snode = e2->second;
	}

	return snode;
}
