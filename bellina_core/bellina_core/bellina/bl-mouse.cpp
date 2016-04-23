#include "stdafx.h"

#include "Xel/Xel.h"

#include "bl-listener.h"
#include "bl-util.h"
#include "bl-globals.h"
#include "bl-input.h"
#include "bl-sys.h"
#include "bl-core.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::sys;
using namespace bl::listener;
using namespace bl::input;

namespace bl {
	namespace input {
		void updateSysMouse(int mx, int my) {
			mouse_x_prev = mouse_x; mouse_y_prev = mouse_y;
			mouse_x = mx; mouse_y = my;
		}

		void call_mouse_down(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			bool bubbleUp = true;

			std::list<NodeMouseDownCallback>::const_iterator iterator;
			for (iterator = node->onMouseDown_callbacks.begin(); iterator != node->onMouseDown_callbacks.end(); ++iterator) {
				NodeMouseDownCallback cb = *iterator;
				bl::node = node;
				bubbleUp = cb(button, mx, my, bubbledFrom);
			}

			// bubble up the event!
			if (bubbleUp && node->parent) {
				bl::node = node->parent;
				call_mouse_down(node->parent, button, mx, my, node);
			}
		}

		void call_mouse_up(Node* node, Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {			
			bool bubbleUp = true;

			std::list<NodeMouseUpCallback>::const_iterator iterator;
			for (iterator = node->onMouseUp_callbacks.begin(); iterator != node->onMouseUp_callbacks.end(); ++iterator) {
				NodeMouseUpCallback cb = *iterator;
				bl::node = node;
				bubbleUp = cb(button, mx, my, bubbledFrom);
			}

			// bubble up the event!
			if (bubbleUp && node->parent) {
				bl::node = node->parent;
				call_mouse_up(node->parent, button, mx, my, node);
			}
		}

		void call_mouse_scroll(Node *node, int amount, int mx, int my, Node* bubbledFrom) {
			bool bubbleUp = true;

			std::list<NodeMouseScrollCallback>::const_iterator iterator;
			for (iterator = node->onMouseScroll_callbacks.begin(); iterator != node->onMouseScroll_callbacks.end(); ++iterator) {
				NodeMouseScrollCallback cb = *iterator;
				bl::node = node;
				bubbleUp = cb(amount, mx, my, bubbledFrom);
			}

			// bubble up the event!
			if (bubbleUp && node->parent) {
				bl::node = node->parent;
				call_mouse_scroll(node->parent, amount, mx, my, node);
			}
		}

		void call_mouse_move(Node *node, int mx, int my, Node* bubbledFrom) {
			bool bubbleUp = true;

			std::list<NodeMouseMoveCallback>::const_iterator iterator;
			for (iterator = node->onMouseMove_callbacks.begin(); iterator != node->onMouseMove_callbacks.end(); ++iterator) {
				NodeMouseMoveCallback cb = *iterator;
				bl::node = node;
				bubbleUp = cb(mx, my, bubbledFrom);
			}

			// bubble up the event!
			if (bubbleUp && node->parent) {
				bl::node = node->parent;
				call_mouse_move(node->parent, mx, my, node);
			}
		}

		void bl_onMouseMove(int mx, int my) {

			Node *node = util::getNodeAtPos(mx, my);

			MouseMoveEvent event;
			event.mx = mx;
			event.my = my;
			event.node = node;

			bl::fire("mouse move", &event);

			if (node) {
				call_mouse_move(node, mx, my, 0);
			}
		}

		/*void bl_onMouseMove_captured(int mx, int my) {
			printf("mm captured\n");

			Node *node = capture_mouse_nod;

			MouseMoveEvent event;
			event.mx = mx;
			event.my = my;
			event.node = node;

			// do not fire when mouse is captured - bl::fire("mouse move", &event);

			if (node) {
				call_mouse_move(node, mx, my, 0);
			}
		}*/

		void bl_onMouseScroll(int amount) {
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

		/*void bl_onMouseScroll_captured(int amount) {
			int mx = mouse_x;
			int my = mouse_y;

			Node* node = capture_mouse_nod;

			MouseScrollEvent event;
			event.node = node;
			event.mx = mx;
			event.my = my;
			event.amount = amount;

			// do not fire on captured mouse bl::fire("mouse scroll", &event);

			if (node) {
				call_mouse_scroll(node, amount, mx, my, 0);
			}
		}

		void bl_onMouseButton_captured(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {

			Node* node = capture_mouse_nod;

			MouseDownEvent event;
			event.node = node;
			event.mx = mx;
			event.my = my;
			event.button = button;

			// do not fire on capture

			if (node) {

				if (action == Xel::Mouse::Action::Down)
					call_mouse_down(node, button, mx, my, 0);
				else if (action == Xel::Mouse::Action::Up)
					call_mouse_up(node, button, mx, my, 0);
			}
		}*/

		void bl_onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {

			Node* node = util::getNodeAtPos(mx, my);

			MouseDownEvent event;
			event.node = node;
			event.mx = mx;
			event.my = my;
			event.button = button;

			if (action == Xel::Mouse::Action::Down)
				bl::fire("mouse down", &event);
			else if (action == Xel::Mouse::Action::Up)
				bl::fire("mouse up", &event);

			if (node) {

				if (action == Xel::Mouse::Action::Down)
					call_mouse_down(node, button, mx, my, 0);
				else if (action == Xel::Mouse::Action::Up)
					call_mouse_up(node, button, mx, my, 0);
			}
		}
	}
}

void bl::input::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {
	updateSysMouse(mx, my);

	/*if (capture_mouse_nod)
		bl_onMouseButton_captured(button, action, mx, my);
	else*/
		bl_onMouseButton(button, action, mx, my);
}

void bl::input::onMouseScroll(int amount) {
	/*if (capture_mouse_nod)
		bl_onMouseScroll_captured(amount);
	else*/
		bl_onMouseScroll(amount);
}

void bl::input::onMouseMove(int mx, int my) {
	updateSysMouse(mx, my);

	/*if (capture_mouse_nod)
		printf("on move %s\n", capture_mouse_nod->nid);
	else
		printf("no capture\n");

	if (capture_mouse_nod) 
		bl_onMouseMove_captured(mx, my);
	else */
		bl_onMouseMove(mx, my);
}

/*void bl::captureMouse() {
	capture_mouse_nod = bl::node;
}

Node* bl::getMouseOwner() {
	return capture_mouse_nod;
}*/