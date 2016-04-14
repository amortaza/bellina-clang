#include "stdafx.h"

#include "bellina/bellina.h"

#include "click.h"

using namespace bl;
using namespace bl::event;

namespace click {
	char* lastDownNodeId = 0;
	Xel::Mouse::Button lastDownButton;

	void freeId() {
		if (lastDownNodeId) {
			delete [] lastDownNodeId;
			lastDownNodeId = 0;
		}
	}

	void init() {
		bl::listen("mouse down", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId) ) {
				printf("lost it!\n");
				freeId();
			}
		});

		bl::listen("mouse up", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId)) {
				printf("lost it!\n");
				freeId();
			}
		});
	}

	void uninit() {
		freeId();
	}

	void tick(Node *node) {

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (lastDownNodeId) delete[] lastDownNodeId;

			lastDownNodeId = _strdup(bl::node->nid);
			lastDownButton = button;
		});

		bl::onMouseUp([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bl::util::isNode(bl::node, lastDownNodeId ) && button == lastDownButton ) {
				printf("click %s\n", bl::node->nid);
			}

			freeId();
		});
	}
}