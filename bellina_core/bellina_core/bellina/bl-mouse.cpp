#include "stdafx.h"

#include "Xel/Xel.h"

#include "bl-event.h"
#include "bl-util.h"
#include "bl-extern.h"
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

		void call_mouse_click(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (node->callback_onClick != nullptr) {
				bl::node = node;
				node->callback_onClick(button, mx, my, bubbledFrom);
			}

			if (node->callback_onClick_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_mouse_click(node->parent, button, mx, my, node);
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

		if (action == Xel::Mouse::Action::Down) {
			last_mouse_down_node_id = _strdup(hit->nid);
			last_mouse_down_button = button;
			call_mouse_down(hit, button, mx, my, 0);

			//printf("down %s\n", last_mouse_down_node_id);
		}
		else if (action == Xel::Mouse::Action::Up) {
			//printf("up %s\n", hit->nid);

			call_mouse_up(hit, button, mx, my, 0);

			if (hit->nid && last_mouse_down_node_id && strcmp(hit->nid, last_mouse_down_node_id) == 0 && button == last_mouse_down_button) {
				call_mouse_click(hit, button, mx, my, 0);
			}

			if (last_mouse_down_node_id) {
				delete[] last_mouse_down_node_id;
				last_mouse_down_node_id = 0;
			}
		}
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

