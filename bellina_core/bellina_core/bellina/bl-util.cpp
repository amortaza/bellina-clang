#include "stdafx.h"

#include "bl-extern.h"

using namespace bl;
using namespace bl::util;

bool _nodeContainsPoint(Node *node, int parentWx, int parentWy, int wx, int wy) {
	return true;

}

Node* _getNodeAtPos(Node *parent, int parentWx, int parentWy, int wx, int wy) {
	if (!parent) return 0;

	if (!_nodeContainsPoint(parent, wx - parentWx, wy - parentWy,wx,wy)) return 0;

	std::list<Node*>::const_iterator iterator;

	for (iterator = parent->kids.begin(); iterator != parent->kids.end(); ++iterator) {
		Node *kid = *iterator;

		Node *node = _getNodeAtPos(kid, kid->x + parentWx, kid->y + parentWy, wx, wy);
	}
}

Node* bl::util::getNodeAtPos(int wx, int wy) {
	Node *node = _getNodeAtPos(Internal::root, 0, 0, wx, wy);

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
