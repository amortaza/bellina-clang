#include "stdafx.h"

#include "bl-node.h"
#include "bl-extern.h"
#include "bl-ui.h"
#include "bl-sys.h"

using namespace bl;

void _call_key_down(Node *node, unsigned long long xcode, Node* bubbledFrom) {
	if (node->callback_onKeyDown != nullptr) {
		bl::node = node;
		node->callback_onKeyDown(xcode, bubbledFrom);
	}

	if (node->callback_onKeyDown_enabled_bubble) {

		// bubble up the event!
		if (node->parent) {
			bl::node = node->parent;
			_call_key_down(node->parent, xcode, node);
		}
	}
}

void bl::ui::onKeyDown(unsigned long long xcode) {
	int mx = bl::sys::mouse_x;
	int my = bl::sys::mouse_y;

	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {
		_call_key_down(bl::node, xcode, 0);
	}
}

void _call_key_up(Node *node, unsigned long long xcode, Node* bubbledFrom) {
	if (node->callback_onKeyUp != nullptr) {
		bl::node = node;
		node->callback_onKeyUp(xcode, bubbledFrom);
	}

	if (node->callback_onKeyUp_enabled_bubble) {

		// bubble up the event!
		if (node->parent) {
			bl::node = node->parent;
			_call_key_up(node->parent, xcode, node);
		}
	}
}

void bl::ui::onKeyUp(unsigned long long xcode) {
	int mx = bl::sys::mouse_x;
	int my = bl::sys::mouse_y;

	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {
		_call_key_up(bl::node, xcode, 0);
	}
}
