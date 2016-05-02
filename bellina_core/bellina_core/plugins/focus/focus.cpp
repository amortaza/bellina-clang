#include "stdafx.h"

#include "bellina/bellina.h"

#include "focus.h"

using namespace bl;
using namespace bl::listener;

namespace focus {
	char* plugin_name = "focus";
	
	char* focusNodeId = 0;

	void freeId() {
		if (focusNodeId) {
			delete[] focusNodeId;
			focusNodeId = 0;
		}
	}

	void init() {
		/*todo bl::listenLongTerm("mouse-down", [] (void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (focusNodeId && strcmp(focusNodeId, event->node->nid) != 0) {
				// blur
				freeId();
			}
		});*/

		/*todo bl::listenLongTerm("key-down", [] (void* e) {
			KeyDownEvent* event = (KeyDownEvent*)e;

			if (focusNodeId) {
				Node* node = bl::util::getNodeById(focusNodeId);

				FocusOnKeyEvent focusEvent;
				focusEvent.keyDownEvent = event;
				focusEvent.node = node;
				
				bl::pluginCall(plugin_name, "focus", node, &focusEvent);
				bl::fire(plugin_name, &focusEvent);
			}			
		});*/
	}

	void uninit() {
		freeId();
	}

	void onNode(char* signature, PluginCtxFactory factory) {
		bl::color(200, 255, 35);

		/*todo bl::onMouseDown([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			freeId();

			focusNodeId = _strdup(bl::node->nid);

			//rintf("focus node id is %s\n", focusNodeId);

			return true;
		});*/
	}
}

void focus::load() {
	bl::pluginRegister(
		focus::plugin_name, 
		focus::init, 
		focus::onNode, 
		focus::uninit);
}