#include "stdafx.h"

#include "bellina/bl-extern.h"
#include "bellina/bl-core.h"

#include "focus.h"

using namespace bl;

namespace focus {
	char* focusNodeId = 0;

	void init() {
		bl::listen("mouse down", [](void* data) {
			UiEvent* event = (UiEvent*)data;

			if (focusNodeId && strcmp(focusNodeId, event->node->nid) != 0) {
				printf("Blur!\n");
				focusNodeId = 0;
			}
			//printf("yo was called %i\n", a->age);
		});
	}

	void uninit() {
		if (focusNodeId) delete[] focusNodeId;
	}

	void tick(Node *node) {
		bl::color(200, 255, 35);

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (focusNodeId) delete[] focusNodeId;

			focusNodeId = _strdup(bl::node->nid);
		});

		bl::onKeyDown([](unsigned long long xcode, Node* bubbledFrom) {
			if (focusNodeId && strcmp(focusNodeId, bl::node->nid) == 0) {
				printf("Receiveing key %s\n", bl::node->nid);
			}
		});
	}
}