#include "stdafx.h"

#include "bellina/bellina.h"

#include "click.h"

using namespace bl;
using namespace bl::listener;

namespace click {
	char* plugin_name = "click";

	char* lastDownNodeId = 0;
	Xel::Mouse::Button lastDownButton;

	void freeId() {
		if (lastDownNodeId) {
			delete [] lastDownNodeId;
			lastDownNodeId = 0;
		}
	}

	void init() {
		bl::listenLongTerm("mouse-down", [] (void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId) ) {
				freeId();
			}
		});

		bl::listenLongTerm("mouse-up", [] (void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId)) {
				freeId();
			}
		});
	}

	void uninit() {
		freeId();
	}

	void on_node(char* signature, PluginCtxFactory factory) {

		bl::onMouseDown([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (lastDownNodeId) delete[] lastDownNodeId;

			lastDownNodeId = _strdup(bl::node->nid);
			lastDownButton = button;

			return true;
		});
		
		bl::onMouseUp([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			
			if (bl::util::isNode(bl::node, lastDownNodeId ) && button == lastDownButton ) {
				MouseClickEvent event;
				event.mx = mx;
				event.my = my;
				event.button = button;
				event.node = bl::node;

				//printf("mouse up getting called for signature %s\n", signature);
				bl::pluginCall(plugin_name, "default", bl::node, &event);
				bl::fire(plugin_name, &event);
			}

			freeId();

			return true;
		});
	}
}

void click::load() {
	pango::registerPlugin(
		click::plugin_name, 
		click::init, 
		nullptr,
		click::on_node,
		click::uninit);
}