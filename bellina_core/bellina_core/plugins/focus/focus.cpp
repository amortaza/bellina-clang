#include "stdafx.h"

#include "bellina/bellina.h"

#include "focus.h"

using namespace bl;
using namespace bl::listener;

namespace focus {
	
	char* focusNodeId = 0;
	PluginCallback g_cb = nullptr;

	void init() {
		bl::listenLongTerm("mouse down", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (focusNodeId && strcmp(focusNodeId, event->node->nid) != 0) {
				printf("Blur!\n");
				focusNodeId = 0;
			}
		});

		bl::listenLongTerm("key down", [](void* e) {
			KeyDownEvent* event = (KeyDownEvent*)e;

			if (focusNodeId) {
				Node* node = bl::util::getNodeById(focusNodeId);

				FocusOnKeyEvent focusEvent;
				focusEvent.keyDownEvent = event;
				focusEvent.node = node;
				
				g_cb(&focusEvent);
			}			
		});
	}

	void uninit() {
		if (focusNodeId) delete[] focusNodeId;
	}

	void tick() {
	}

	void onNode(PluginCallback cb) {
		g_cb = cb;

		bl::color(200, 255, 35);

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (focusNodeId) delete[] focusNodeId;

			focusNodeId = _strdup(bl::node->nid);

			printf("focuse node id is %s\n", focusNodeId);
		});

		/*bl::onKeyDown([](unsigned long long xcode, Node* bubbledFrom) {
			if (focusNodeId && strcmp(focusNodeId, bl::node->nid) == 0) {
				printf("Receiveing key %s\n", bl::node->nid);
			}
		});*/
	}
}