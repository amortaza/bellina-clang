#include "stdafx.h"

#include "bellina/bellina.h"

#include "focus.h"

using namespace bl;
using namespace bl::listener;

namespace focus {
	char* focusNodeId = 0;

	void init() {
		bl::listenLongTerm("mouse down", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

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

	void tick() {
		printf("tick focus\n");
	}

	void onNode(PluginCallback cb) {
		bl::color(200, 255, 35);

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (focusNodeId) delete[] focusNodeId;

			focusNodeId = _strdup(bl::node->nid);
		});

		/*bl::listenLongTerm("key down",)
		bl::onKeyDown([](unsigned long long xcode, Node* bubbledFrom) {
			if (focusNodeId && strcmp(focusNodeId, bl::node->nid) == 0) {
				printf("Receiveing key %s\n", bl::node->nid);
			}
		});*/
	}
}