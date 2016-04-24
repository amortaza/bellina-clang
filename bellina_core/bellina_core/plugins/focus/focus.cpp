#include "stdafx.h"

#include "bellina/bellina.h"

#include "focus.h"

using namespace bl;
using namespace bl::listener;

namespace focus {
	char* plugin_name = "focus";
	
	char* focusNodeId = 0;

	void init() {
		bl::listenLongTerm("mouse down", [](void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (focusNodeId && strcmp(focusNodeId, event->node->nid) != 0) {
				//rintf("Blur!\n");
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
				
				bl::pluginCall(plugin_name, node, &focusEvent);
			}			
		});
	}

	void uninit() {
		if (focusNodeId) delete[] focusNodeId;
	}

	void tickOnAfterCoreRender() {
	}

	void onNode(PluginCallback cb) {
		bl::color(200, 255, 35);

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (focusNodeId) delete[] focusNodeId;

			focusNodeId = _strdup(bl::node->nid);

			//rintf("focus node id is %s\n", focusNodeId);

			return true;
		});
	}
}