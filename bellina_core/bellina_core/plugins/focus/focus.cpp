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
		bl::listenLongTerm("mouse-down", [] (void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (!bl::util::isNode(event->node, focusNodeId)) {
				// blur
				freeId();
			}
		});

		bl::listenLongTerm("key-down", [] (void* e) {
			KeyDownEvent* event = (KeyDownEvent*)e;

			if (focusNodeId) {
				Node* node = bl::util::getNodeById(focusNodeId);

				FocusOnKeyEvent focusEvent;
				focusEvent.keyDownEvent = event;
				focusEvent.node = node;
				
				bl::pluginCall(plugin_name, "default", "default", node, &focusEvent);
				bl::fire(plugin_name, &focusEvent);
			}			
		});
	}

	void uninit() {
		freeId();
	}

	void on_node(char* signature, PluginCtxFactory factory) {

		bl::onMouseDown([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			freeId();

			focusNodeId = _strdup(bl::node->nid);

			return true;
		});
	}
}

void focus::load() {
	pango::registerPlugin(
		focus::plugin_name, 
		focus::init, 
		nullptr,
		focus::on_node,
		focus::uninit);
}