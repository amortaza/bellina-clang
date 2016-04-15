#include "stdafx.h"

#include "Xel/Xel.h"

#include "bl-event.h"
#include "bl-util.h"
#include "bl-global.h"
#include "bl-input.h"
#include "bl-sys.h"
#include "bl-core.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::sys;
using namespace bl::event;
using namespace bl::input;

namespace bl {
	namespace input {
		void updateSysMouse(int mx, int my) {
			mouse_x_prev = mouse_x; mouse_y_prev = mouse_y;
			mouse_x = mx; mouse_y = my;
		}

		void call_mouse_down(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (node->callback_onMouseDown != nullptr) {
				bl::node = node;
				node->callback_onMouseDown(button, mx, my, bubbledFrom);
			}

			if (node->callback_onMouseDown_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_mouse_down(node->parent, button, mx, my, node);
				}
			}
		}

		void call_mouse_up(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (node->callback_onMouseUp != nullptr) {
				bl::node = node;
				node->callback_onMouseUp(button, mx, my, bubbledFrom);
			}

			if (node->callback_onMouseUp_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_mouse_up(node->parent, button, mx, my, node);
				}
			}
		}

		void call_mouse_scroll(Node *node, int amount, int mx, int my, Node* bubbledFrom) {
			if (node->callback_onMouseScroll != nullptr) {
				bl::node = node;
				node->callback_onMouseScroll(amount, mx, my, bubbledFrom);
			}

			if (node->callback_onMouseScroll_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_mouse_scroll(node->parent, amount, mx, my, node);
				}
			}
		}

		void call_mouse_move(Node *node, int mx, int my, Node* bubbledFrom) {
			if (node->callback_onMouseMove != nullptr) {
				bl::node = node;
				node->callback_onMouseMove(mx, my, bubbledFrom);
			}

			if (node->callback_onMouseMove_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_mouse_move(node->parent, mx, my, node);
				}
			}
		}

	}
}

void bl::input::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {
	updateSysMouse(mx, my);

	Node* hit = util::getNodeAtPos(mx, my);

	MouseDownEvent event;
	event.node = hit;
	event.mx = mx; 
	event.my = my; 
	event.button = button; 

	if (action == Xel::Mouse::Action::Down)
		bl::fire("mouse down", &event);
	else if (action == Xel::Mouse::Action::Up)
		bl::fire("mouse up", &event);

	if (hit) {

		if (action == Xel::Mouse::Action::Down) 
			call_mouse_down(hit, button, mx, my, 0);
		else if (action == Xel::Mouse::Action::Up) 
			call_mouse_up(hit, button, mx, my, 0);
	}
}

void bl::input::onMouseScroll(int amount) {
	int mx = mouse_x;
	int my = mouse_y;

	Node* node = util::getNodeAtPos(mx, my);

	MouseScrollEvent event;
	event.node = node;
	event.mx = mx; 
	event.my = my; 
	event.amount = amount; 

	bl::fire("mouse scroll", &event);

	if (node) {
		call_mouse_scroll(node, amount, mx, my, 0);
	}
}

void bl::input::onMouseMove(int mx, int my) {
	updateSysMouse(mx, my);

	Node *node = util::getNodeAtPos(mx, my);

	MouseMoveEvent event;
	event.node = node;
	event.mx = mx; 
	event.my = my; 	

	bl::fire("mouse scroll", &event);

	if (node) {
		call_mouse_move(node, mx, my, 0);
	}
}

