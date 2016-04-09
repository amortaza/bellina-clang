#include "stdafx.h"

#include "Xel/Xel.h"
#include "bl-extern.h"
#include "bl-ui.h"
#include "bl-sys.h"

using namespace bl;
using namespace bl::Internal;
using namespace bl::sys;

void _updateSysMouse(int mx, int my) {
	mouse_x_prev = mouse_x; mouse_y_prev = mouse_y;
	mouse_x = mx; mouse_y = my;
}

void _call_mouse_down(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
	if (node->callback_onMouseDown_enabled && node->callback_onMouseDown != nullptr) {
		bl::node = node;
		node->callback_onMouseDown(button, mx, my, bubbledFrom);
	}

	if (node->callback_onMouseDown_enabled_bubble) {

		// bubble up the event!
		if (node->parent) {
			bl::node = node->parent;
			_call_mouse_down(node->parent, button, mx, my, node);
		}
	}
}

void bl::ui::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {
	_updateSysMouse(mx, my);

	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {
		if (action == Xel::Mouse::Action::Down)
			_call_mouse_down(bl::node, button, mx, my, 0);
	}
}

void bl::ui::onMouseScroll(int amount) {
}

void _call_mouse_move(Node *node, int mx, int my, Node* bubbledFrom) {
	if (node->callback_onMouseMove_enabled && node->callback_onMouseMove != nullptr) {
		bl::node = node;
		node->callback_onMouseMove(mx, my, bubbledFrom);
	}

	if (node->callback_onMouseMove_enabled_bubble) {

		// bubble up the event!
		if (node->parent) {
			bl::node = node->parent;
			_call_mouse_move(node->parent, mx, my, node);
		}
	}
}

void bl::ui::onMouseMove(int mx, int my) {
	_updateSysMouse(mx, my);

	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {
		_call_mouse_move(bl::node, mx, my, 0);
	}
}

