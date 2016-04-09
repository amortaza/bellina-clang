#include "stdafx.h"

#include "bl-extern.h"

using namespace bl;
using namespace bl::util;

bool _nodeContainsPoint(Node *node, int wx, int wy) {
	return wx >= node->global_pos.x && wx <= node->global_pos.x + node->w && wy >= node->global_pos.y && wy <= node->global_pos.y + node->h;
}

Node* _getNodeAtPos(Node *parent, int wx, int wy) {
	if (!parent) return 0;

	if (!_nodeContainsPoint(parent, wx,wy)) return 0;

	std::list<Node*>::const_iterator iterator;

	Node* topmost = parent;
	for (iterator = parent->kids.begin(); iterator != parent->kids.end(); ++iterator) {
		Node *kid = *iterator;

		if (_nodeContainsPoint(kid, wx, wy)) {
			topmost = kid;
		}
	}

	// now get the topmost from topmost
	topmost = _getNodeAtPos(topmost, wx, wy);

	return topmost;
}

Node* bl::util::getNodeAtPos(int wx, int wy) {
	Node *node = _getNodeAtPos(Internal::root, wx, wy);

	if (!node) return Internal::root;
}

void _calcGlobalPositions(Node* node, int parentX, int parentY) {
	parentX = node->global_pos.x = node->x + parentX;
	parentY = node->global_pos.y = node->y + parentY;

	std::list<Node*>::const_iterator iterator;

	for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
		Node *kid = *iterator;

		_calcGlobalPositions(kid, parentX, parentY);
	}
}

void bl::util::calcGlobalPositions() {
	if (!Internal::root) return;

	_calcGlobalPositions(Internal::root, 0, 0);
}
