#include "stdafx.h"

#include "bl-extern.h"
#include "bl-ui.h"

using namespace bl;
using namespace bl::Internal;

void _call_mouse_move(Node *node, int mx, int my) {
	if (node->callback_onMouseMove_enabled && node->callback_onMouseMove != nullptr) {
		node->callback_onMouseMove(mx, my);
	}

	// bubble up the event!
	Node *parent = node->parent;

	while (parent) {
		bl::node = parent;
		_call_mouse_move(parent, mx, my);
		parent = parent->parent;
	}

	bl::node = node;
}

void bl::ui::onMouseMove(int mx, int my) {
	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {		
		_call_mouse_move(bl::node, mx, my);
	}
}

void bl::ui::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int x, int y) {
}

void bl::ui::onMouseScroll(int amount) {
}

void bl::ui::onKeyDown(unsigned long long xcode) {
}

void bl::ui::onKeyUp(unsigned long long xcode) {
}

void bl::ui::onResize(int w, int h) {
	glViewport(0, 0, w, h);

	printf("Set glViewport\n");
}