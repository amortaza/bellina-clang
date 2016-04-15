#include "stdafx.h"

#include "bl-node.h"
#include "bl-globals.h"
#include "bl-input.h"
#include "bl-sys.h"
#include "bl-listener.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::_;
using namespace bl::input;
using namespace bl::listener;
using namespace bl::listener::_;

namespace bl {
	namespace input {

		void call_key_down(Node *node, unsigned long long xcode, Node* bubbledFrom) {
			if (node->callback_onKeyDown != nullptr) {
				bl::node = node;
				node->callback_onKeyDown(xcode, bubbledFrom);
			}

			if (node->callback_onKeyDown_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_key_down(node->parent, xcode, node);
				}
			}
		}

		void call_key_up(Node *node, unsigned long long xcode, Node* bubbledFrom) {
			if (node->callback_onKeyUp != nullptr) {
				bl::node = node;
				node->callback_onKeyUp(xcode, bubbledFrom);
			}

			if (node->callback_onKeyUp_enabled_bubble) {

				// bubble up the event!
				if (node->parent) {
					bl::node = node->parent;
					call_key_up(node->parent, xcode, node);
				}
			}
		}
	}
}

void bl::input::onKeyDown(unsigned long long xcode) {
	KeyDownEvent event;
	event.xcode = xcode;

	bl::fire("key down", &event);

	std::list<Node*>::const_iterator iterator;

	for (iterator = key_down_registry.begin(); iterator != key_down_registry.end(); ++iterator) {
		Node* node = *iterator;

		call_key_down(node, xcode, 0);
	}
}

void bl::input::onKeyUp(unsigned long long xcode) {
	KeyDownEvent event;
	event.xcode = xcode;

	bl::fire("key up", &event);

	std::list<Node*>::const_iterator iterator;

	for (iterator = key_up_registry.begin(); iterator != key_up_registry.end(); ++iterator) {
		Node* node = *iterator;

		call_key_up(node, xcode, 0);
	}
}
